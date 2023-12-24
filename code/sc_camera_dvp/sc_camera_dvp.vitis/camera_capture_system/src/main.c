#include <stdio.h>
#include <string.h>
#include "FreeRTOS.h"
#include "xparameters.h"
#include "netif/xadapter.h"
#include "lwip/sockets.h"
#include "netif/xadapter.h"
#include "lwipopts.h"
#include "xil_printf.h"
#include "xil_printf.h"
#include "sc035hgs.h"
#include "dma_intr.h"
#include "open_image.h"
#include "vofa_plus.h"
#include "global.h"

/* 相关外设 ID */
#define DEVICE_DMA			        XPAR_AXIDMA_0_DEVICE_ID                 // DMA
#define DEVICE_IICS                 XPAR_I2CS_DEVICE_ID                     // IIC（AXI GPIO 模拟）
#define DEVICE_BUFW_FS				XPAR_BUFW_FS_DEVICE_ID                  // AXISBUFW 传输使能（高电平有效）
#define DEVICE_BUFW_RSTN			XPAR_BUFW_RSTN_DEVICE_ID                // AXISBUFW 复位（低电平有效）
#define DEVICE_CAMERA_PWDN			XPAR_CAMERA_PWDN_DEVICE_ID              // SC035HGS 休眠控制（正常工作时应拉高）
#define DEVICE_CAMERA_VSYNC			XPAR_CAMERA_VSYNC_DEVICE_ID             // SC035HGS 输出场同步信号
#define DEVICE_XCLK_LOCKED			XPAR_XCLK_LOCKED_DEVICE_ID              // SC035HGS 输入时钟锁定监测（高电平代表锁定）
#define DEVICE_PHY_RETN				XPAR_PHY_RSTN_DEVICE_ID                 // PHY 复位控制（低电平有效）
#define PLATFORM_EMAC_BASEADDR 		XPAR_XEMACPS_0_BASEADDR

/* DMA 中断号 */
#define DMA_RX_INTR_ID			    XPAR_FABRIC_AXI_DMA_0_S2MM_INTROUT_INTR

/* FreeRTOS */
#define THREAD_PRIORITY             DEFAULT_THREAD_PRIO                     // 任务优先级
#define THREAD_STACKSIZE 			2048                                    // 任务堆栈大小

/* 缓冲区相关设置 */
#define CAMERA_IGNORE_FRAME_NUMS    10                                      // 摄像头稳定所需帧数（初始化后一段时间内输出不稳定）

/* TCP Server */
#define TCP_SERVER_PORT             7

/* 外设句柄 */
camera_t camera;                                        

/* GPIO & 全局中断句柄 */
XGpio gpio_bufw_fs;
XGpio gpio_bufw_rstn;
XGpio gpio_camera_pwdn;
XGpio gpio_camera_xclk_locked;
XGpio gpio_camera_vsync;
XGpio gpio_phy_rstn;

// https://www.codeprj.com/blog/a4dd341.html
extern XAxiDma AxiDma;
extern XScuGic xInterruptController;

/* DMA 缓冲区 */
extern s32 RxCount;
extern s32 RxIndex;
extern s32 TxIndex;
extern s32 RxLastIndex;
extern u32 RxBufferPtr[RX_BUFFER_NUMS];
extern u32 RxBufferFrameAddr[RX_BUFFER_NUMS];
extern u32 EthTxBufferPtr;

extern SemaphoreHandle_t FrameBufferSyncSemaphore;

s32 client;
struct netif server_netif;

/* 函数声明 */
void lwip_init();
void main_thread(void *p);

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
void camera_init()
{
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
void axisbufw_init()
{
	XGpio_Initialize(&gpio_bufw_rstn, DEVICE_BUFW_RSTN);
    XGpio_Initialize(&gpio_bufw_fs, DEVICE_BUFW_FS);
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
 * @brief 上位机传输线程
 * @param p 客户端句柄
 * @return *
*/
void upper_communicate_thread(void *p)
{
	BaseType_t err;

	while(1)
	{
		if(FrameBufferSyncSemaphore == NULL)
		{
			continue;
		}

		// 等待帧同步信号量释放
		err = xSemaphoreTakeFromISR(FrameBufferSyncSemaphore, NULL);
		if(err != pdTRUE)
		{
			continue;
		}

		/* 更新缓冲区索引 */
		TxIndex = RxLastIndex;
		if(RxBufferFrameAddr[TxIndex] == RX_BUFFER_INVALID_ADDR)
		{
			continue;
		}
		Xil_DCacheInvalidateRange(RxBufferPtr[TxIndex], RX_BUFFER_SIZE);
		xil_printf("[INFO] Sending frame %d to upper\n", TxIndex);

		/* 发送帧数据 */
		write(client, "image:0,307200,640,480,24\n", 26);
		write(client, (u8*)(RxBufferPtr[TxIndex] + RxBufferFrameAddr[TxIndex]), FRAME_SIZE);
		write(client, "\n", 1);
	}
	close(client);

	vTaskDelete(NULL);
}

/**
 * @brief 信号量测试线程
 * @param p
 * @return *
*/
void semaphore_test_thread(void *p)
{
	BaseType_t err;
	
	while(1)
	{
		// 等待帧同步信号量释放
		err = xSemaphoreTakeFromISR(FrameBufferSyncSemaphore, NULL);
		if(err != pdTRUE)
		{
			continue;
		}

		/* 更新缓冲区索引 */
		TxIndex = RxLastIndex;
		if(RxBufferFrameAddr[TxIndex] == RX_BUFFER_INVALID_ADDR)
		{
			continue;
		}
		xil_printf("[ERROR] Wakeup semaphore thread, current TxIndex is  %d\n", TxIndex);
	}

	vTaskDelete(NULL);
}

/**
 * @brief 上位机连接线程
 * @return *
*/
void upper_connect_thread(void *p)
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
	while(1)
    {
        client = lwip_accept(socket, (struct sockaddr *)&remote, (socklen_t *)&size);
		if (client > 0)
        {
			sys_thread_new("upper_transmit_thread", upper_communicate_thread, (void*)&client, THREAD_STACKSIZE, THREAD_PRIORITY); break;
		}
	}
	vTaskSuspend(NULL);
}


/**
 * @brief 网络线程
 * @param p *
 * @return *
*/
void network_thread(void *p)
{
	ip_addr_t ipaddr, netmask, gw;

	lwip_init();

	// 初始化 IP & MASK & GATWALL
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
	sys_thread_new("upper_transmit_thread", upper_connect_thread, 0, THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);

	vTaskDelete(NULL);
}

/**
 * @brief:系统初始化函数
 * @param p
 * @return *
 */
void system_init()
{
	// AXISBUFW
	axisbufw_init();

	// SC035HGS
	camera_init();

	// 创建二值信号量用以同步中断
	FrameBufferSyncSemaphore = xSemaphoreCreateBinary();
	if(FrameBufferSyncSemaphore == NULL)
	{
		xil_printf("[ERROR] Failed to create FrameBufferSyncSemaphore\n");
		return;
	}

	/* DMA */
    // https://github.com/fuseon/zynq_freertos_interrupt/blob/master/freertos_hello_world.c
	XDMA_Init(&AxiDma, DEVICE_DMA);
	XDMA_Intr_Init(&xInterruptController, &AxiDma, DMA_RX_INTR_ID);
	XDMA_Intr_Enable(&AxiDma);

	/* 帧缓冲区 */
    RxCount = 0;
    RxIndex = 0;
    RxLastIndex = -1;
    TxIndex = -1;
	for(int i = 0; i < RX_BUFFER_NUMS; i++)
	{
		RxBufferPtr[i] = RX_BUFFER_BASE + i * RX_BUFFER_SIZE;
        RxBufferFrameAddr[i] = RX_BUFFER_INVALID_ADDR;
	}
    EthTxBufferPtr = RX_BUFFER_BASE + RX_BUFFER_NUMS * RX_BUFFER_SIZE;

	// 结束 BUFW 复位
	XGpio_DiscreteWrite(&gpio_bufw_rstn, 1, 0x1);

	// 等待上位机连接
	xil_printf("[INFO] Waiting for upper...\n");
	while(client <= 0)
	{

	}
	xil_printf("[INFO] Upper is connected, ready to start DMA\n");
	
	// 使能 AXISBUFW 数据流转模块
	while(XGpio_DiscreteRead(&gpio_camera_vsync, 1) == 0x0);
	set_axisbufw_transmit(1);

	// 启动首次 DMA 传输
	XAxiDma_SimpleTransfer(&AxiDma, (u32)RxBufferPtr[RxIndex], RX_BUFFER_SIZE, XAXIDMA_DEVICE_TO_DMA);
}


void system_init_thread(void *p)
{
	system_init();
	vTaskDelete(NULL);
}


/**
 * @brief 主线程
 * @return
 */
void main_thread(void *p)
{
	sys_thread_new("network_thread", network_thread, NULL, THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);
	sys_thread_new("system_init_thread", system_init_thread, NULL, THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);

	vTaskDelete(NULL);
}
