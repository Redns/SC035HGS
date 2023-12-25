#include <stdio.h>
#include <string.h>
#include "FreeRTOS.h"
#include "xparameters.h"
#include "netif/xadapter.h"
#include "lwip/sockets.h"
#include "netif/xadapter.h"
#include "lwipopts.h"
#include "xil_printf.h"
#include "sc035hgs.h"
#include "dma.h"

/* 帧属性 */
#define FRAME_WIDTH                 640                                     // 帧宽度
#define FRAME_HEIGHT                480                                     // 帧高度
#define FRAME_SIZE					(FRAME_WIDTH * FRAME_HEIGHT)            // 帧尺寸（字节）

/* 接收缓冲区 */
#define RX_BUFFER_ADDR              0x01000000                              // 基地址
#define RX_BUFFER_SIZE		        0x00080000                              // 大小（单位：字节，默认 512 KB）

/* 相关外设 ID */
#define DEVICE_DMA			        XPAR_AXIDMA_0_DEVICE_ID                 // DMA
#define DEVICE_IICS                 XPAR_I2CS_DEVICE_ID                     // IIC（AXI GPIO 模拟）
#define DEVICE_BUFW_FS				XPAR_BUFW_FS_DEVICE_ID                  // AXISBUFW 传输使能（高电平有效）
#define DEVICE_BUFW_RSTN			XPAR_BUFW_RSTN_DEVICE_ID                // AXISBUFW 复位（低电平有效）
#define DEVICE_CAMERA_PWDN			XPAR_CAMERA_PWDN_DEVICE_ID              // SC035HGS 休眠控制（正常工作时应拉高）
#define DEVICE_CAMERA_VSYNC			XPAR_CAMERA_VSYNC_DEVICE_ID             // SC035HGS 输出场同步信号
#define DEVICE_XCLK_LOCKED			XPAR_XCLK_LOCKED_DEVICE_ID              // SC035HGS 输入时钟锁定监测（高电平代表锁定）
#define DEVICE_PHY_RETN				XPAR_PHY_RSTN_DEVICE_ID                 // PHY 复位控制（低电平有效）

/* FreeRTOS */
#define THREAD_PRIORITY             DEFAULT_THREAD_PRIO                     // 任务优先级
#define THREAD_STACKSIZE 			1024                                    // 任务堆栈大小

/* 缓冲区相关设置 */
#define CAMERA_IGNORE_FRAME_NUMS    10                                      // 摄像头稳定所需帧数（初始化后一段时间内输出不稳定）

/* LWIP */
#define TCP_SERVER_PORT             7         								// TCP 服务器端口号
#define PLATFORM_EMAC_BASEADDR 		XPAR_XEMACPS_0_BASEADDR                 

/* 外设句柄 */
XAxiDma dma;

XGpio gpio_bufw_fs;
XGpio gpio_bufw_rstn;
XGpio gpio_camera_pwdn;
XGpio gpio_camera_xclk_locked;
XGpio gpio_camera_vsync;
XGpio gpio_phy_rstn;

/* TCP Handlers */
s32 client;
struct netif server_netif;

/* 函数声明 */
void lwip_init();
void main_thread();

int main()
{
	sys_thread_new("main_thread", (void(*)(void*))main_thread, 0, THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);
	vTaskStartScheduler();
	while(1);
	return 0;
}


/**
 * @brief 初始化摄像头
 * @return *
*/
void SC035HGS_Init()
{
	camera_t camera;   

    xil_printf("[INFO] Start to init camera...\n");

    // 初始化相关引脚
    XGpio_Initialize(&gpio_camera_pwdn, DEVICE_CAMERA_PWDN);
    XGpio_Initialize(&gpio_camera_vsync, DEVICE_CAMERA_VSYNC);
    XGpio_Initialize(&gpio_camera_xclk_locked, DEVICE_XCLK_LOCKED);

    // 等待摄像头输入时钟锁定
    while(XGpio_DiscreteRead(&gpio_camera_xclk_locked, 1) == 0);

    // 拉高 PWDN 引脚启用摄像头
    // 拉高 PWDN 后至少等待 4ms 才能访问寄存器
    XGpio_DiscreteWrite(&gpio_camera_pwdn, 1, 0x1);
    usleep(20 * 1000);

    // 初始化摄像头寄存器
    camera.i2c_device_id = DEVICE_IICS;
    if(sc035hgs_init(&camera) != XST_SUCCESS)
    {
    	xil_printf("[ERROR] Failed to init sc035hgs\n");
    	return;
    }
    xil_printf("[SUCCESS] Success to init sc035hgs\n");

    // 等待摄像头输出稳定
    uint16_t frame_count = 0;
    while(frame_count < CAMERA_IGNORE_FRAME_NUMS)
    {
        xil_printf("[INFO] Ignore camera output %u/%u frame, \n", frame_count, CAMERA_IGNORE_FRAME_NUMS);
        while(XGpio_DiscreteRead(&gpio_camera_vsync, 1) == 0x0);
        while(XGpio_DiscreteRead(&gpio_camera_vsync, 1) == 0x1);
        frame_count++;
    }
}

/**
 * @brief 初始化 AXISBUFW 数据传输模块
 * @return *
*/
void Axisbufw_Init()
{
	XGpio_Initialize(&gpio_bufw_rstn, DEVICE_BUFW_RSTN);
    XGpio_Initialize(&gpio_bufw_fs, DEVICE_BUFW_FS);

	// 结束 BUFW 复位
	XGpio_DiscreteWrite(&gpio_bufw_rstn, 1, 0x1);
}

/**
 * @brief 使能 AXIS 数据传输
 * @param enable AXIS_TRANSMIT_ENABLE/AXIS_TRANSMIT_DISABLE
 * @return *
*/
void set_axisbufw_transmit(int enable)
{
    if(enable)
    {
        XGpio_DiscreteWrite(&gpio_bufw_fs, 1, 0x1);
    }
    else
    {
        XGpio_DiscreteWrite(&gpio_bufw_fs, 1, 0x0);
    }
}

/**
 * @brief 上位机连接线程
 * @return *
*/
void upper_communicate_thread()
{
	struct sockaddr_in address, remote;

    // 创建套接字
    s32 socket = lwip_socket(AF_INET, SOCK_STREAM, 0);
	if (socket < 0)
    {
        xil_printf("[ERROR] Failed to create socket\n");
        return;
    }

    // 初始化服务器地址
    memset(&address, 0, sizeof(address));

	address.sin_family = AF_INET;
	address.sin_port = htons(TCP_SERVER_PORT);
	address.sin_addr.s_addr = INADDR_ANY;

    // 绑定套接字信息
	if(lwip_bind(socket, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        xil_printf("[ERROR] Failed to bind socket\n");
        return;
    }

    // 监听套接字
	lwip_listen(socket, 0);

    // 等待客户端连接
	s32 size = sizeof(remote);
	if((client = lwip_accept(socket, (struct sockaddr *)&remote, (socklen_t *)&size)) <= 0)
	{
		return;
	}

	// 等待帧起始信号
	while(XGpio_DiscreteRead(&gpio_camera_vsync, 1) == 0x0);
	set_axisbufw_transmit(1);

	XAxiDma_SingleReceive(&dma, (INTPTR)RX_BUFFER_ADDR, RX_BUFFER_SIZE);
	Xil_DCacheInvalidateRange((INTPTR)RX_BUFFER_ADDR, RX_BUFFER_SIZE);
	write(client, "image:0,307200,640,480,24\n", 26);
	write(client, (u8*)RX_BUFFER_ADDR, FRAME_SIZE);
	write(client, "\n", 1);

	// while(1)
	// {
	// 	// 启动首次 DMA 传输
	// 	XAxiDma_SingleReceive(&dma, (INTPTR)RX_BUFFER_ADDR, RX_BUFFER_SIZE);

	// 	// 检查当前缓冲区是否包含完整帧图像
	// 	// RxCount++;
	// 	// SurplusFrameSize = (RX_BUFFER_SIZE * RxCount) % FRAME_SIZE; 
	// 	// if(SurplusFrameSize > RX_BUFFER_SIZE - FRAME_SIZE)
	// 	// {
	// 	// 	XAxiDma_SimpleTransfer(&AxiDma, (INTPTR)RX_BUFFER_ADDR, RX_BUFFER_SIZE, XAXIDMA_DEVICE_TO_DMA); return;
	// 	// }
	// 	// FrameAddrOffset = RX_BUFFER_SIZE - (SurplusFrameSize + FRAME_SIZE);

	// 	Xil_DCacheInvalidateRange((INTPTR)RX_BUFFER_ADDR, RX_BUFFER_SIZE);
		
	// 	/* 发送帧数据 */
	// 	// write(client, "image:0,307200,640,480,24\n", 26);
	// 	// write(client, (u8*)RX_BUFFER_ADDR, FRAME_SIZE);
	// 	// write(client, "\n", 1);
	// 	xil_printf("[INFO] DMA RX DONE, first byte is %d\n", ((u8*)RX_BUFFER_ADDR)[0]);
	// }
	close(client);
	vTaskDelete(NULL);
}

/**
 * @brief 主线程
 * @return
 */
void main_thread()
{
	ip_addr_t ipaddr, netmask, gw;

	SC035HGS_Init();
	Axisbufw_Init();
	XAxiDma_Init(&dma, DEVICE_DMA);

	lwip_init();

	IP4_ADDR(&ipaddr, 192, 168, 1, 10);
	IP4_ADDR(&netmask, 255, 255, 255, 0);
	IP4_ADDR(&gw, 192, 168, 1, 1);

	// 添加网络接口
    unsigned char mac_ethernet_address[] = { 0x00, 0x0a, 0x35, 0x00, 0x01, 0x02 };
	if(!xemac_add(&server_netif, &ipaddr, &netmask, &gw, mac_ethernet_address, PLATFORM_EMAC_BASEADDR))
	{
		xil_printf("[ERROR] Failed to add N/W interface\n");
		return;
	}
    netif_set_default(&server_netif);
    netif_set_up(&server_netif);

    // 创建上位机传输线程
	sys_thread_new("xemacif_input_thread", (void(*)(void*))xemacif_input_thread, &server_netif, THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);
	sys_thread_new("upper_communicate_thread", upper_communicate_thread, 0, THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);

	vTaskDelete(NULL);
}
