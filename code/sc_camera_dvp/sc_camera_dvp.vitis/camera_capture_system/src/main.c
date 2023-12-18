#include <stdio.h>
#include "xparameters.h"
#include "netif/xadapter.h"
#include "platform_config.h"
#include "xil_printf.h"
#include "sc035hgs.h"
#include "dma_intr.h"
#include "open_image.h"
#include "vofa_plus.h"
#include "global.h"

/* 任务堆栈大小 */
#define THREAD_STACKSIZE 			2048

/* 相关外设 ID */
#define DEVICE_IICS                 XPAR_I2CS_DEVICE_ID
#define DEVICE_BUFW_FS				XPAR_BUFW_FS_DEVICE_ID
#define DEVICE_BUFW_RSTN			XPAR_BUFW_RSTN_DEVICE_ID
#define DEVICE_CAMERA_PWDN			XPAR_CAMERA_PWDN_DEVICE_ID
#define DEVICE_CAMERA_HREF			XPAR_CAMERA_HREF_DEVICE_ID
#define DEVICE_CAMERA_VSYNC			XPAR_CAMERA_VSYNC_DEVICE_ID
#define DEVICE_XCLK_LOCKED			XPAR_XCLK_LOCKED_DEVICE_ID
#define DEVICE_PHY_RETN				XPAR_PHY_RSTN_DEVICE_ID

/* 缓冲区相关设置 */
#define CAMERA_IGNORE_FRAME_NUMS    10                                      // 摄像头稳定所需帧数（初始化后一段时间内输出不稳定）

/* 摄像头句柄 */
camera_t camera;

/* GPIO & 全局中断句柄 */
XGpio gpio_bufw_fs;
XGpio gpio_bufw_rstn;
XGpio gpio_camera_pwdn;
XGpio gpio_camera_xclk_locked;
XGpio gpio_camera_vsync;
XGpio gpio_camera_href;
XGpio gpio_phy_rstn;

// TODO DMA 进程与 TCP 无法同时运行，DMA 一开 ping 不通
// https://www.codeprj.com/blog/a4dd341.html
extern XAxiDma AxiDma;
extern XScuGic xInterruptController;

extern u32 RxBufferReceiveCount;
extern u32 RxBufferPtrReceiveIndex;
extern u32 RxBufferPtrTransmitIndex;
extern u32 RxBufferPtrLastReceiveIndex;
extern u32 RxBufferPtr[RX_BUFFER_NUMS];
extern u32 RxBufferFrameStartAddrPtr[RX_BUFFER_NUMS];
extern u32 EthTransmitCachePtr;

void main_thread(void *p);
void system_init();
void upper_transmit_thread(void *p);

void lwip_init();
void init_camera();
void wait_camera_ready();
void init_axis_transmit();
void set_axis_transmit(int start);

int main()
{
	sys_thread_new("main_thread", (void(*)(void*))main_thread, 0, THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);
	vTaskStartScheduler();
	while(1);
	return 0;
}

void network_thread(void *p)
{
	struct netif server_netif;
	ip_addr_t ipaddr, netmask, gw;
	unsigned char mac_ethernet_address[] = { 0x00, 0x0a, 0x35, 0x00, 0x01, 0x02 };

	// 初始化 LWIP
	lwip_init();

	// 初始化 IP & MASK & GATWALL
	IP4_ADDR(&ipaddr, 192, 168, 1, 10);
	IP4_ADDR(&netmask, 255, 255, 255, 0);
	IP4_ADDR(&gw, 192, 168, 1, 1);

	// 添加网络接口
	if(!xemac_add(&server_netif, &ipaddr, &netmask, &gw, mac_ethernet_address, PLATFORM_EMAC_BASEADDR))
	{
		xil_printf("[ERROR] Failed to add N/W interface\n");
		return;
	}
    netif_set_default(&server_netif);
    netif_set_up(&server_netif);

    // 创建上位机传输线程
	sys_thread_new("xemacif_input_thread", (void(*)(void*))xemacif_input_thread, &server_netif, THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);
	sys_thread_new("upper_transmit_thread", upper_transmit_thread, 0, THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);

	vTaskDelete(NULL);
}

/**
 * @brief 主线程
 * @return
 */
void main_thread(void *p)
{
	// 网络配置
    sys_thread_new("network_thread", network_thread, NULL, THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);

    // 系统初始化
	system_init();

    vTaskDelete(NULL);
}


/**
 * @brief:系统初始化函数
 * @param p
 * @return *
 */
void system_init()
{
	// 初始化 AXIS 数据转换模块
	init_axis_transmit();

	// 初始化摄像头
	init_camera();

	/* DMA */
	DMA_Intr_Init(&AxiDma, 0);
	DMA_Setup_Intr_System(&xInterruptController, &AxiDma, RX_INTR_ID);
	DMA_Intr_Enable(&xInterruptController, &AxiDma);

	/* 帧缓冲区 */
	RxBufferReceiveCount = 0;
	RxBufferPtrReceiveIndex  = 0;
	RxBufferPtrLastReceiveIndex = -1;
	RxBufferPtrTransmitIndex = -1;
	for(int i = 0; i < RX_BUFFER_NUMS; i++)
	{
		RxBufferFrameStartAddrPtr[i] = 0;
		RxBufferPtr[i] = RX_BUFFER_BASE + RX_BUFFER_SIZE * i;
	}
	EthTransmitCachePtr = RX_BUFFER_BASE + RX_BUFFER_SIZE * RX_BUFFER_NUMS;

	// 结束 BUFW 复位
	XGpio_DiscreteWrite(&gpio_bufw_rstn, 1, 0x1);

	// 等待摄像头输出稳定
	wait_camera_ready();

	// 使能 AXIS 模块
	set_axis_transmit(1);

	// 启动首次 DMA 传输
	XAxiDma_SimpleTransfer(&AxiDma, (u32)RxBufferPtr[RxBufferPtrReceiveIndex], (u32)(RX_BUFFER_SIZE), XAXIDMA_DEVICE_TO_DMA);
}


/**
 * @brief 初始化摄像头
 * @return *
*/
void init_camera()
{
    xil_printf("[INFO] Start to init camera...\n");

    // 初始化休眠输出引脚
    XGpio_Initialize(&gpio_camera_pwdn, DEVICE_CAMERA_PWDN);
    XGpio_SetDataDirection(&gpio_camera_pwdn, 1, 0x0);
    XGpio_DiscreteWrite(&gpio_camera_pwdn, 1, 0x0);

    // 初始化时钟输入锁定引脚
    XGpio_Initialize(&gpio_camera_xclk_locked, DEVICE_XCLK_LOCKED);
	XGpio_SetDataDirection(&gpio_camera_xclk_locked, 1, 0x1);

    // 等待摄像头输入时钟锁定
    while(XGpio_DiscreteRead(&gpio_camera_xclk_locked, 1) == 0);

    // 初始化场信号输入引脚
    XGpio_Initialize(&gpio_camera_vsync, DEVICE_CAMERA_VSYNC);
	XGpio_SetDataDirection(&gpio_camera_vsync, 1, 0x1);

    // 拉高 PWDN 引脚启用摄像头
    XGpio_DiscreteWrite(&gpio_camera_pwdn, 1, 0x1);

    // 拉高 PWDN 后至少等待 4ms 才能访问寄存器
    usleep(20 * 1000);

    // 初始化摄像头寄存器
    camera.i2c_device_id = DEVICE_IICS;
    if(sc035hgs_init(&camera) != XST_SUCCESS)
    {
    	xil_printf("[ERROR] Success to init sc035hgs\n");
    	return;
    }
    xil_printf("[SUCCESS] Init camera done\n");
}

/**
 * @brief 初始化 AXIS 数据传输模块
 * @return *
*/
void init_axis_transmit()
{
	// 复位
	XGpio_Initialize(&gpio_bufw_rstn, DEVICE_BUFW_RSTN);
	XGpio_SetDataDirection(&gpio_bufw_rstn, 1, 0x0);
	XGpio_DiscreteWrite(&gpio_bufw_rstn, 1, 0x0);

	// 传输控制
    XGpio_Initialize(&gpio_bufw_fs, DEVICE_BUFW_FS);
    XGpio_SetDataDirection(&gpio_bufw_fs, 1, 0x0);
    XGpio_DiscreteWrite(&gpio_bufw_fs, 1, 0x0);
}

/**
 * @brief 使能 AXIS 数据传输
 * @param start AXIS_TRANSMIT_ENABLE/AXIS_TRANSMIT_DISABLE
 * @return *
*/
void set_axis_transmit(int start)
{
    if(start)
    {
        XGpio_DiscreteWrite(&gpio_bufw_fs, 1, 0x1);
    }
    else
    {
        XGpio_DiscreteWrite(&gpio_bufw_fs, 1, 0x0);
    }
}

/**
 * @brief 等待摄像头准备好
 * @return *
*/
void wait_camera_ready()
{
    uint16_t frame_count = 0;
    while(frame_count < CAMERA_IGNORE_FRAME_NUMS)
    {
        xil_printf("[INFO] Ignore camera output %u/%u frame, \n", frame_count, CAMERA_IGNORE_FRAME_NUMS);
        while(XGpio_DiscreteRead(&gpio_camera_vsync, 1) == 0x0);
        while(XGpio_DiscreteRead(&gpio_camera_vsync, 1) == 0x1);
        frame_count++;
    }
}
