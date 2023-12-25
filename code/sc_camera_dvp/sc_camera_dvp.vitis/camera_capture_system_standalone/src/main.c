#include <stdio.h>
#include "xparameters.h"
#include "netif/xadapter.h"
#include "platform.h"
#include "platform_config.h"
#include "xil_printf.h"
#include "lwip/tcp.h"
#include "xil_cache.h"
#include "xil_types.h"
#include "xstatus.h"
#include "xaxidma.h"
#include "xgpio.h"
#include "sc035hgs.h"
#include "dma.h"
#include "intr.h"

/* 帧属性 */
#define FRAME_WIDTH                 640                                     // 帧宽度
#define FRAME_HEIGHT                480                                     // 帧高度
#define FRAME_SIZE					(FRAME_WIDTH * FRAME_HEIGHT)            // 帧尺寸（字节）
#define FRAME_BUFFER_BASE           0x00080000                              // 基地址
#define FRAME_BUFFER_NUMS			3	

u32 TxIndex;
u32 RxIndex;
u32 RxLastIndex;
u32 FrameBufferPtr[FRAME_BUFFER_NUMS];

extern u8 RxDone;

/* 相关外设 ID */
#define DEVICE_DMA			        XPAR_AXIDMA_0_DEVICE_ID                 // DMA
#define DEVICE_IICS                 XPAR_I2CS_DEVICE_ID                     // IIC（AXI GPIO 模拟）
#define DEVICE_BUFW_FS				XPAR_BUFW_FS_DEVICE_ID                  // AXISBUFW 传输使能（高电平有效）
#define DEVICE_BUFW_RSTN			XPAR_BUFW_RSTN_DEVICE_ID                // AXISBUFW 复位（低电平有效）
#define DEVICE_CAMERA_PWDN			XPAR_CAMERA_PWDN_DEVICE_ID              // SC035HGS 休眠控制（正常工作时应拉高）
#define DEVICE_CAMERA_VSYNC			XPAR_CAMERA_VSYNC_DEVICE_ID             // SC035HGS 输出场同步信号
#define DEVICE_XCLK_LOCKED			XPAR_XCLK_LOCKED_DEVICE_ID              // SC035HGS 输入时钟锁定监测（高电平代表锁定）
#define DEVICE_PHY_RETN				XPAR_PHY_RSTN_DEVICE_ID                 // PHY 复位控制（低电平有效）
#define DEVICE_LED_STATE			XPAR_LED_STATE_DEVICE_ID				// 状态指示灯

#define DMA_RX_INTR_ID				XPAR_FABRIC_AXI_DMA_0_S2MM_INTROUT_INTR

/* 外设句柄 */
XAxiDma axiDma;
XScuGic scuGic;

XGpio gpio_bufw_fs;
XGpio gpio_bufw_rstn;
XGpio gpio_camera_pwdn;
XGpio gpio_camera_xclk_locked;
XGpio gpio_camera_vsync;
XGpio gpio_phy_rstn;
XGpio gpio_led_state;

static s32 eth_init();
static s32 tcp_server_init();
static err_t accept_callback(void *arg, struct tcp_pcb *newpcb, err_t err);

struct netif *echo_netif;
static struct netif server_netif;
struct tcp_pcb *client = NULL;

void lwip_init();
void system_init();
s32 network_init();
s32 camera_init();
void axisbufw_init();
void dma_init();
void set_axisbufw_transmit(int enable);

int main()
{
	init_platform();

	system_init();
	network_init();
	
	XAxiDma_SimpleTransfer(&axiDma, (u32)FrameBufferPtr[RxIndex], (u32)FRAME_SIZE, XAXIDMA_DEVICE_TO_DMA);
	while(XGpio_DiscreteRead(&gpio_camera_vsync, 1) == 0);
	set_axisbufw_transmit(1);
	while(1) 
	{
		if(RxDone)
		{
			RxDone = 0;
			
			RxLastIndex = RxIndex;
			do
			{
				RxIndex = (RxIndex + 1) % FRAME_BUFFER_NUMS;
			} while(RxIndex == TxIndex);

			xil_printf("Rx-RxLast-Tx is %d-%d-%d\n", RxIndex, RxLastIndex, TxIndex);

			XAxiDma_SimpleTransfer(&axiDma, (u32)FrameBufferPtr[0], (u32)FRAME_SIZE, XAXIDMA_DEVICE_TO_DMA);
		}
		xemacif_input(&server_netif);
	}

	return 0;
}

void system_init()
{
	camera_init();
	axisbufw_init();
	dma_init();
}

s32 network_init()
{
	//init_platform();

	// 初始化网口
	if(eth_init() != XST_SUCCESS)
	{
		xil_printf("[ERROR] Failed to init eth\n");
		return XST_FAILURE;
	} 

	// 初始化 TCP 服务器
	if(tcp_server_init() != XST_SUCCESS)
	{
		xil_printf("[ERROR] Failed to init tcp server\n");
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}

/**
 * @brief 初始化摄像头
 * @return 
*/
s32 camera_init()
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

	return XST_SUCCESS;
}

/**
 * @brief 初始化 AXISBUFW 数据传输模块
 * @return *
*/
void axisbufw_init()
{
	XGpio_Initialize(&gpio_bufw_rstn, DEVICE_BUFW_RSTN);
    XGpio_Initialize(&gpio_bufw_fs, DEVICE_BUFW_FS);

	// 结束 BUFW 复位
	XGpio_DiscreteWrite(&gpio_bufw_rstn, 1, 0x1);
}

/**
 * @brief 初始化 DMA
 * @return *
*/
void dma_init()
{
	Intr_Init(&scuGic);
	Intr_Exception_Setup(&scuGic);
	XAxiDma_Init(&axiDma, DEVICE_DMA);
	XAxiDma_Intr_Enable(&axiDma);
	XAxiDma_Intr_Setup(&scuGic, &axiDma, DMA_RX_INTR_ID);

	for(u8 i = 0; i < FRAME_BUFFER_NUMS; i++)
	{
		FrameBufferPtr[i] = FRAME_BUFFER_BASE + FRAME_SIZE * i;
	}
}

/**
 * @brief 使能 AXIS 数据传输
 * @param enable AXIS_TRANSMIT_ENABLE/AXIS_TRANSMIT_DISABLE
 * @return *
*/
void set_axisbufw_transmit(int enable)
{
	XGpio_DiscreteWrite(&gpio_bufw_fs, 1, enable ? 0x1 : 0x0);
}

static s32 eth_init()
{
	lwip_init();

	// 初始化 IP 地址
	ip_addr_t ip, netmask, gw;
	IP4_ADDR(&ip,  		192, 168,   1, 10);
	IP4_ADDR(&netmask, 	255, 255, 255,  0);
	IP4_ADDR(&gw,      	192, 168,   1,  1);

	// 添加网络接口
	u8 mac_ethernet_address[] = { 0x00, 0x0a, 0x35, 0x00, 0x01, 0x02 };
	if(!xemac_add(&server_netif, &ip, &netmask, &gw, mac_ethernet_address, XPAR_XEMACPS_0_BASEADDR)) 
	{
		xil_printf("[ERROR] Failed to add mac interface\n");
		return XST_FAILURE;
	}
	netif_set_default(&server_netif);
	netif_set_up(&server_netif);

	// 使能中断
	platform_enable_interrupts();

	return XST_SUCCESS;
}

static s32 tcp_server_init()
{
	// 创建 TCP PCB 句柄
	struct tcp_pcb *pcb = tcp_new_ip_type(IPADDR_TYPE_ANY);
	if(!pcb) 
	{
		xil_printf("[ERROR] Error creating PCB, out of Memory\n");
		return XST_FAILURE;
	}

	// 绑定端口号
	if(tcp_bind(pcb, IP_ANY_TYPE, 7) != ERR_OK) 
	{
		xil_printf("[ERROR] Unable to bind tcp port\n");
		return XST_FAILURE;
	}
	tcp_arg(pcb, NULL);

	// 监听客户端连接
	pcb = tcp_listen(pcb);
	if(!pcb) 
	{
		xil_printf("[ERROR] Out of memory while tcp_listen\n");
		return XST_FAILURE;
	}

	// 设置连接回调函数
	tcp_accept(pcb, accept_callback);

	return XST_SUCCESS;
}

static err_t accept_callback(void *arg, struct tcp_pcb *newpcb, err_t err)
{
	if(newpcb == NULL)
	{
		xil_printf("[ERROR] Failed to accept new client connection, input pcb is null\n");
		return ERR_ABRT;
	}

	client = newpcb;

	return ERR_OK;
}
