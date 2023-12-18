/*
 * Copyright (C) 2009 - 2019 Xilinx, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 */

#include <stdio.h>
#include "sc035hgs.h"
#include "dma_intr.h"
#include "sys_intr.h"
#include "open_image.h"
#include "vofa_plus.h"
#include "xparameters.h"

#include "netif/xadapter.h"
#include "xil_io.h"
#include "platform.h"
#include "platform_config.h"
#if defined (__arm__) || defined(__aarch64__)
#include "xil_printf.h"
#endif

#include "lwip/tcp.h"
#include "xil_cache.h"

#if LWIP_IPV6==1
#include "lwip/ip.h"
#else
#if LWIP_DHCP==1
#include "lwip/dhcp.h"
#endif
#endif

/* defined by each RAW mode application */
void print_app_header();
int start_application();
int transfer_data();
void tcp_fasttmr(void);
void tcp_slowtmr(void);
void sc035hgs_print_hello_message();

/* missing declaration in lwIP */
void lwip_init();

#if LWIP_IPV6==0
#if LWIP_DHCP==1
extern volatile int dhcp_timoutcntr;
err_t dhcp_start(struct netif *netif);
#endif
#endif

extern volatile int TcpFastTmrFlag;
extern volatile int TcpSlowTmrFlag;
static struct netif server_netif;
struct netif *echo_netif;

#if LWIP_IPV6==1
void print_ip6(char *msg, ip_addr_t *ip)
{
	print(msg);
	xil_printf(" %x:%x:%x:%x:%x:%x:%x:%x\n\r",
			IP6_ADDR_BLOCK1(&ip->u_addr.ip6),
			IP6_ADDR_BLOCK2(&ip->u_addr.ip6),
			IP6_ADDR_BLOCK3(&ip->u_addr.ip6),
			IP6_ADDR_BLOCK4(&ip->u_addr.ip6),
			IP6_ADDR_BLOCK5(&ip->u_addr.ip6),
			IP6_ADDR_BLOCK6(&ip->u_addr.ip6),
			IP6_ADDR_BLOCK7(&ip->u_addr.ip6),
			IP6_ADDR_BLOCK8(&ip->u_addr.ip6));

}
#else
void
print_ip(char *msg, ip_addr_t *ip)
{
	print(msg);
	xil_printf("%d.%d.%d.%d\n", ip4_addr1(ip), ip4_addr2(ip),
			ip4_addr3(ip), ip4_addr4(ip));
}

void
print_ip_settings(ip_addr_t *ip, ip_addr_t *mask, ip_addr_t *gw)
{
	print_ip("[INFO] Board IP is ", ip);
	print_ip("[INFO] Netmask is ", mask);
	print_ip("[INFO] Gateway is ", gw);
}
#endif

#if defined (__arm__) && !defined (ARMR5)
#if XPAR_GIGE_PCS_PMA_SGMII_CORE_PRESENT == 1 || XPAR_GIGE_PCS_PMA_1000BASEX_CORE_PRESENT == 1
int ProgramSi5324(void);
int ProgramSfpPhy(void);
#endif
#endif

#ifdef XPS_BOARD_ZCU102
#ifdef XPAR_XIICPS_0_DEVICE_ID
int IicPhyReset(void);
#endif
#endif

/* 缓冲区相关设置 */
#define CAMERA_IGNORE_FRAME_NUMS    10                                      // 摄像头稳定所需帧数（初始化后一段时间内输出不稳定）

u8 EthTransmitCache[FRAME_SIZE + 1];

struct tcp_pcb* client = NULL;

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

void init_system();
void init_camera();
void init_axis_transmit();
void set_axis_transmit(int start);
void wait_camera_ready();

int main()
{
	sc035hgs_print_hello_message();

	init_system();

#if LWIP_IPV6==0
	ip_addr_t ipaddr, netmask, gw;

#endif
	/* the mac address of the board. this should be unique per board */
	unsigned char mac_ethernet_address[] =
	{ 0x00, 0x0a, 0x35, 0x00, 0x01, 0x02 };
	Xil_Out32(0x41230000,3);
	echo_netif = &server_netif;
#if defined (__arm__) && !defined (ARMR5)
#if XPAR_GIGE_PCS_PMA_SGMII_CORE_PRESENT == 1 || XPAR_GIGE_PCS_PMA_1000BASEX_CORE_PRESENT == 1
	ProgramSi5324();
	ProgramSfpPhy();
#endif
#endif

/* Define this board specific macro in order perform PHY reset on ZCU102 */
#ifdef XPS_BOARD_ZCU102
	if(IicPhyReset()) {
		xil_printf("Error performing PHY reset \n\r");
		return -1;
	}
#endif

#if LWIP_IPV6==0
#if LWIP_DHCP==1
    ipaddr.addr = 0;
	gw.addr = 0;
	netmask.addr = 0;
#else
	/* initialize IP addresses to be used */
	IP4_ADDR(&ipaddr,  192, 168,   1, 10);
	IP4_ADDR(&netmask, 255, 255, 255,  0);
	IP4_ADDR(&gw,      192, 168,   1,  1);
#endif
#endif

	lwip_init();

#if (LWIP_IPV6 == 0)
	/* Add network interface to the netif_list, and set it as default */
	if (!xemac_add(echo_netif, &ipaddr, &netmask,
						&gw, mac_ethernet_address,
						PLATFORM_EMAC_BASEADDR)) {
		xil_printf("Error adding N/W interface\n\r");
		return -1;
	}
#else
	/* Add network interface to the netif_list, and set it as default */
	if (!xemac_add(echo_netif, NULL, NULL, NULL, mac_ethernet_address,
						PLATFORM_EMAC_BASEADDR)) {
		xil_printf("Error adding N/W interface\n\r");
		return -1;
	}
	echo_netif->ip6_autoconfig_enabled = 1;

	netif_create_ip6_linklocal_address(echo_netif, 1);
	netif_ip6_addr_set_state(echo_netif, 0, IP6_ADDR_VALID);

	print_ip6("\n\rBoard IPv6 address ", &echo_netif->ip6_addr[0].u_addr.ip6);

#endif
	netif_set_default(echo_netif);

	/* now enable interrupts */
	platform_enable_interrupts();

	/* specify that the network if is up */
	netif_set_up(echo_netif);

#if (LWIP_IPV6 == 0)
#if (LWIP_DHCP==1)
	/* Create a new DHCP client for this interface.
	 * Note: you must call dhcp_fine_tmr() and dhcp_coarse_tmr() at
	 * the predefined regular intervals after starting the client.
	 */
	dhcp_start(echo_netif);
	dhcp_timoutcntr = 24;

	while(((echo_netif->ip_addr.addr) == 0) && (dhcp_timoutcntr > 0))
		xemacif_input(echo_netif);

	if (dhcp_timoutcntr <= 0) {
		if ((echo_netif->ip_addr.addr) == 0) {
			xil_printf("DHCP Timeout\r\n");
			IP4_ADDR(&(echo_netif->ip_addr),  192, 168,   1, 10);
			IP4_ADDR(&(echo_netif->netmask), 255, 255, 255,  0);
			IP4_ADDR(&(echo_netif->gw),      192, 168,   1,  1);
		}
	}

	ipaddr.addr = echo_netif->ip_addr.addr;
	gw.addr = echo_netif->gw.addr;
	netmask.addr = echo_netif->netmask.addr;
#endif

	print_ip_settings(&ipaddr, &netmask, &gw);

#endif
	/* start the application (web server, rxtest, txtest, etc..) */
	start_application();

	/* receive and process packets */
	while (1) {
		if (TcpFastTmrFlag) {
			tcp_fasttmr();
			TcpFastTmrFlag = 0;
		}
		if (TcpSlowTmrFlag) {
			tcp_slowtmr();
			TcpSlowTmrFlag = 0;
		}
		xemacif_input(echo_netif);
		transfer_data();
	}

	/* never reached */
	cleanup_platform();

	return 0;
}


/**
 * @brief:系统初始化函数
 * @return *
 */
void init_system()
{
	init_platform();

    // 初始化 AXIS 数据转换模块
    init_axis_transmit();

    // 初始化摄像头
    init_camera();

    /* DMA */
    DMA_Intr_Init(&AxiDma, 0);
	Init_Intr_System(&Intc);
	Setup_Intr_Exception(&Intc);
	DMA_Setup_Intr_System(&Intc, &AxiDma, RX_INTR_ID);
	DMA_Intr_Enable(&Intc, &AxiDma);

    /* 帧缓冲区 */
	RxBufferPtrReceiveIndex  = 0;
	RxBufferPtrLastReceiveIndex = 0;
	RxBufferPtrTransmitIndex = 0;
    for(int i = 0; i < RX_BUFFER_NUMS + 1; i++)
    {
    	RxBufferFrameStartAddrPtr[i] = 0;
    	RxBufferPtr[i] = RX_BUFFER_BASE + RX_BUFFER_SIZE * i;
    }

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


/**
 * @brief SC035HGS 控制台欢迎信息
 * @return *
*/
void sc035hgs_print_hello_message()
{
    char hello_message[][200] = {
        "  ______    ______    ______    ______   _______   __    __   ______    ______",
        "\n /      \\  /      \\  /      \\  /      \\ /       | /  |  /  | /      \\  /      \\",
        "\n/$$$$$$  |/$$$$$$  |/$$$$$$  |/$$$$$$  |$$$$$$$/  $$ |  $$ |/$$$$$$  |/$$$$$$  |",
        "\n$$ \\__$$/ $$ |  $$/ $$$  \\$$ |$$ ___$$ |$$ |____  $$ |__$$ |$$ | _$$/ $$ \\__$$/",
        "\n$$      \\ $$ |      $$$$  $$ |  /   $$< $$      \\ $$    $$ |$$ |/    |$$      \\",
        "\n $$$$$$  |$$ |   __ $$ $$ $$ | _$$$$$  |$$$$$$$  |$$$$$$$$ |$$ |$$$$ | $$$$$$  |",
        "\n/  \\__$$ |$$ \\__/  |$$ \\$$$$ |/  \\__$$ |/  \\__$$ |$$ |  $$ |$$ \\__$$ |/  \\__$$ |",
        "\n$$    $$/ $$    $$/ $$   $$$/ $$    $$/ $$    $$/ $$ |  $$ |$$    $$/ $$    $$/",
        "\n $$$$$$/   $$$$$$/   $$$$$$/   $$$$$$/   $$$$$$/  $$/   $$/  $$$$$$/   $$$$$$/\n\n"
    };

    for(uint8_t i = 0; i < sizeof(hello_message) / sizeof(hello_message[0]); i++)
    {
        xil_printf(hello_message[i]);
    }
}
