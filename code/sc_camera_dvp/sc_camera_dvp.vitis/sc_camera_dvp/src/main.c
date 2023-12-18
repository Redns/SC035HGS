#include "xgpio.h"
#include "xparameters.h"
#include "platform.h"
#include "platform_config.h"
#include "xil_printf.h"
#include "sleep.h"
#include "sc035hgs.h"
#include "dma_intr.h"
#include "sys_intr.h"
#include "open_image.h"
#include "vofa_plus.h"
#include "netif/xadapter.h"
#include "lwipopts.h"
#include "lwip/priv/tcp_priv.h"
#include "lwip/init.h"
#include "lwip/inet.h"

/* 缓冲区相关设置 */
#define CAMERA_IGNORE_FRAME_NUMS    10                                      // 摄像头稳定所需帧数（初始化后一段时间内输出不稳定）

u8 EthTransmitCache[FRAME_SIZE + 1];

/* IP 相关设置 */
u16 port = 12121;
u8 ethernet_ip_address[] = { 192, 168, 1, 10 };
u8 ethernet_ip_mask[] = { 255, 255, 255, 0 };
u8 ethernet_gw_address[] = { 192, 168, 1, 1 };
u8 mac_ethernet_address[] = { 0x00, 0x0a, 0x35, 0x00, 0x01, 0x02 };

struct tcp_pcb* client = NULL;

extern volatile int dhcp_timoutcntr;
err_t dhcp_start(struct netif *netif);

extern volatile int TcpFastTmrFlag;
extern volatile int TcpSlowTmrFlag;
static struct netif server_netif;
struct netif *echo_netif;

/* 相关外设 ID */
#define DEVICE_IICS                 XPAR_I2CS_DEVICE_ID						// SC035HGS IIC 配置
#define DEVICE_BUFW_FS				XPAR_BUFW_FS_DEVICE_ID
#define DEVICE_BUFW_RSTN			XPAR_BUFW_RSTN_DEVICE_ID
#define DEVICE_CAMERA_PWDN			XPAR_CAMERA_PWDN_DEVICE_ID
#define DEVICE_CAMERA_HREF			XPAR_CAMERA_HREF_DEVICE_ID
#define DEVICE_CAMERA_VSYNC			XPAR_CAMERA_VSYNC_DEVICE_ID
#define DEVICE_XCLK_LOCKED			XPAR_XCLK_LOCKED_DEVICE_ID
#define DEVICE_PHY_RETN				XPAR_PHY_RSTN_DEVICE_ID

extern XScuGic Intc;
extern XAxiDma AxiDma;

extern u32 RxBufferPtrReceiveIndex;                                              // 接收缓存索引
extern u32 RxBufferPtrTransmitIndex;                                             // 发送缓存索引
extern u32 RxBufferPtrLastReceiveIndex;                                          // 上一个接收缓存索引
extern u32 RxBufferPtr[RX_BUFFER_NUMS];                                    // 帧缓冲区（RAW, RAW...、RAW, RGB）
extern u32 RxBufferFrameStartAddrPtr[RX_BUFFER_NUMS];

/* 外设句柄 */
camera_t camera;
XGpio gpio_bufw_fs;
XGpio gpio_bufw_rstn;
XGpio gpio_camera_pwdn;
XGpio gpio_camera_xclk_locked;
XGpio gpio_camera_vsync;
XGpio gpio_camera_href;
XGpio gpio_phy_rstn;

s32 eth_init();
void init_system();
void init_camera();
void init_axis_transmit();
void set_axis_transmit(int start);
void wait_camera_ready();

int main(void)
{
    init_system();

    u8 cnt = 0;
    u8 data[FRAME_SIZE];

	while(1)
	{
		if(TcpFastTmrFlag)
		{
			tcp_fasttmr();
			TcpFastTmrFlag = 0;
		}
		if(TcpSlowTmrFlag)
		{
			tcp_slowtmr();
			TcpSlowTmrFlag = 0;
		}
		xemacif_input(echo_netif);

		// for(int i = 0; i < FRAME_SIZE; i++)
		// {
		// 	data[i] = i + cnt;
		// }
		// cnt++;
		// tcp_write(client, "image:0,14,4,4,24\n", 18, 1);
		// tcp_write(client, data, 16, 1);

//		if((client != NULL) && (RxBufferPtrTransmitIndex != RxBufferPtrLastReceiveIndex))
//		{
//			xil_printf("[INFO] Sending %d frame...\n", RxBufferPtrTransmitIndex);
//
//			            //memset(EthTransmitCache, '\n', sizeof(EthTransmitCache));
//
//			            // 将 Bayer 转换为灰度图像
//			            RxBufferPtrTransmitIndex = RxBufferPtrLastReceiveIndex;
//						//bayer2grayscale(ptr_converter((u8*)RxBufferPtr[RxBufferPtrTransmitIndex], FRAME_WIDTH, FRAME_HEIGHT), &EthTransmitCache, FRAME_WIDTH, FRAME_HEIGHT);
//
//						// 发送前导帧
//			//			char *image_front_frame = generate_image_front_frame(0, FRAME_SIZE, FRAME_WIDTH, FRAME_HEIGHT, Format_Grayscalec8);
//			//			tcp_write(client, image_front_frame, strlen(image_front_frame), 1);
//			            char *image_front_frame = generate_image_front_frame(0, 64, 8, 8, Format_Grayscalec8);
//			            			tcp_write(client, image_front_frame, strlen(image_front_frame), 1);
//
//						// 图片数据发送
//						//tcp_write(client, EthTransmitCache, 65, 1);
//		}
	}
    cleanup_platform();

    return 0;
}


err_t accept_callback(void *arg, struct tcp_pcb *newpcb, err_t err)
{
	if(!newpcb)
	{
		xil_printf("[ERROR] Failed to connect client\n");
		return ERR_CONN;
	}

	client = newpcb;
	xil_printf("[INFO] Success to connect client\n");

	return ERR_OK;
}


s32 eth_init()
{
	ip_addr_t ipaddr, netmask, gw;

	// 复位 PHY 芯片
	Xil_Out32(0x41230000,3);

	echo_netif = &server_netif;

	// 初始化平台
	init_platform();

	// DHCP
	ipaddr.addr = 0;
	gw.addr = 0;
	netmask.addr = 0;

	// 初始化 LWIP
	lwip_init();

	// 添加网络接口
	if(!xemac_add(echo_netif, &ipaddr, &netmask, &gw, mac_ethernet_address, PLATFORM_EMAC_BASEADDR))
	{
		xil_printf("[ERROR] Failed to add eth interface\n");
		return XST_FAILURE;
	}
	netif_set_default(echo_netif);

	// 使能中断
	platform_enable_interrupts();

	// 启用网络接口
	netif_set_up(echo_netif);

	// 初始化 IP 地址
	IP4_ADDR(&ipaddr,  ethernet_ip_address[0], ethernet_ip_address[1], ethernet_ip_address[2], ethernet_ip_address[3]);
	IP4_ADDR(&netmask, ethernet_ip_mask[0], ethernet_ip_mask[1], ethernet_ip_mask[2], ethernet_ip_mask[3]);
	IP4_ADDR(&gw, ethernet_gw_address[0], ethernet_gw_address[1], ethernet_gw_address[2], ethernet_gw_address[3]);

	ipaddr.addr = echo_netif->ip_addr.addr;
	gw.addr = echo_netif->gw.addr;
	netmask.addr = echo_netif->netmask.addr;

	// 创建 TCP 服务
	struct tcp_pcb *pcb = tcp_new_ip_type(IPADDR_TYPE_ANY);
	if(!pcb)
	{
		xil_printf("[ERROR] Failed to create tcp server pcb, out of memory\n");
		return XST_FAILURE;
	}

	// 绑定端口号
	if(tcp_bind(pcb, IP_ANY_TYPE, port) != ERR_OK)
	{
		xil_printf("[ERROR] Failed to bind port %d\n", port);
		return XST_FAILURE;
	}
	tcp_arg(pcb, NULL);

	// 监听链接
	pcb = tcp_listen(pcb);
	if(!pcb)
	{
		xil_printf("[ERROR] Out of memory while tcp_listen\n");
		return XST_FAILURE;
	}

	// 链接回调函数
	tcp_accept(pcb, accept_callback);

	xil_printf("[INFO] Success to init lwip server\n");
	return XST_SUCCESS;
}


/**
 * @brief:系统初始化函数
 * @return *
 */
void init_system()
{
//    // 初始化 AXIS 数据转换模块
//    init_axis_transmit();
//
//    // 初始化摄像头
//    init_camera();
//
//    /* DMA */
//    DMA_Intr_Init(&AxiDma, 0);
//	Init_Intr_System(&Intc);
//	Setup_Intr_Exception(&Intc);
//	DMA_Setup_Intr_System(&Intc, &AxiDma, RX_INTR_ID);
//	DMA_Intr_Enable(&Intc, &AxiDma);
//
//    /* 帧缓冲区 */
//	RxBufferPtrReceiveIndex  = 0;
//	RxBufferPtrLastReceiveIndex = 0;
//	RxBufferPtrTransmitIndex = 0;
//    for(int i = 0; i < RX_BUFFER_NUMS + 1; i++)
//    {
//    	RxBufferFrameStartAddrPtr[i] = 0;
//    	RxBufferPtr[i] = RX_BUFFER_BASE + RX_BUFFER_SIZE * i;
//    }
//
//    // 结束 BUFW 复位
//    XGpio_DiscreteWrite(&gpio_bufw_rstn, 1, 0x1);
//
//    // 等待摄像头输出稳定
//	wait_camera_ready();
//
//    // 使能 AXIS 模块
//    set_axis_transmit(1);
//
//    // 启动首次 DMA 传输
//    XAxiDma_SimpleTransfer(&AxiDma, (u32)RxBufferPtr[RxBufferPtrReceiveIndex], (u32)(RX_BUFFER_SIZE), XAXIDMA_DEVICE_TO_DMA);

    // 初始化网络传输
	eth_init();
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
    sc035hgs_init(&camera);

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
