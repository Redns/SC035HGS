#include <stdio.h>
#include "xgpio.h"
#include "xparameters.h"
#include "netif/xadapter.h"
#include "platform.h"
#include "platform_config.h"
#include "lwipopts.h"
#include "xil_printf.h"
#include "sleep.h"
#include "lwip/priv/tcp_priv.h"
#include "lwip/init.h"
#include "lwip/inet.h"
#include "sc035hgs.h"
#include "dma_intr.h"
#include "sys_intr.h"

#if LWIP_IPV6==1
#include "lwip/ip6_addr.h"
#include "lwip/ip6.h"
#else

#if LWIP_DHCP==1
#include "lwip/dhcp.h"
extern volatile int dhcp_timoutcntr;
#endif

#define DEFAULT_IP_ADDRESS	"192.168.1.10"
#define DEFAULT_IP_MASK		"255.255.255.0"
#define DEFAULT_GW_ADDRESS	"192.168.1.1"
#endif /* LWIP_IPV6 */

extern volatile int TcpFastTmrFlag;
extern volatile int TcpSlowTmrFlag;

void platform_enable_interrupts(void);
void start_application(void);
void transfer_data(void);
void print_app_header(void);

#if defined (__arm__) && !defined (ARMR5)
#if XPAR_GIGE_PCS_PMA_SGMII_CORE_PRESENT == 1 || \
		 XPAR_GIGE_PCS_PMA_1000BASEX_CORE_PRESENT == 1
int ProgramSi5324(void);
int ProgramSfpPhy(void);
#endif
#endif

#ifdef XPS_BOARD_ZCU102
#ifdef XPAR_XIICPS_0_DEVICE_ID
int IicPhyReset(void);
#endif
#endif

struct netif server_netif;

#if LWIP_IPV6==1
static void print_ipv6(char *msg, ip_addr_t *ip)
{
	print(msg);
	xil_printf(" %s\n\r", inet6_ntoa(*ip));
}
#else
static void print_ip(char *msg, ip_addr_t *ip)
{
	print(msg);
	xil_printf("%d.%d.%d.%d\r\n", ip4_addr1(ip), ip4_addr2(ip),
			ip4_addr3(ip), ip4_addr4(ip));
}

static void print_ip_settings(ip_addr_t *ip, ip_addr_t *mask, ip_addr_t *gw)
{
	print_ip("Board IP:       ", ip);
	print_ip("Netmask :       ", mask);
	print_ip("Gateway :       ", gw);
}

static void assign_default_ip(ip_addr_t *ip, ip_addr_t *mask, ip_addr_t *gw)
{
	int err;

	xil_printf("Configuring default IP %s \r\n", DEFAULT_IP_ADDRESS);

	err = inet_aton(DEFAULT_IP_ADDRESS, ip);
	if (!err)
		xil_printf("Invalid default IP address: %d\r\n", err);

	err = inet_aton(DEFAULT_IP_MASK, mask);
	if (!err)
		xil_printf("Invalid default IP MASK: %d\r\n", err);

	err = inet_aton(DEFAULT_GW_ADDRESS, gw);
	if (!err)
		xil_printf("Invalid default gateway address: %d\r\n", err);
}
#endif /* LWIP_IPV6 */

/* ��������С���� */
#define FRAME_CACHE_SIZE            640 * 480                               // ֡��������С����λ���ֽڣ�
#define FRAME_CACHE_NUMS            3                                       // ֡����������
#define TCP_TRANS_CHCHE_SIZE        4096                                    // TCP ���仺������С����λ���ֽڣ�

/* IP ������� */
#define DEFAULT_IP_ADDRESS	        "192.168.1.10"                          // ���� IP
#define DEFAULT_IP_MASK		        "255.255.255.0"                         // ����
#define DEFAULT_GW_ADDRESS	        "192.168.1.1"                           // ����
#define TCP_SERVER_IP_ADDRESS       "192.168.1.100"                         // TCP ������ IP
#define TCP_CONN_PORT               1896                                    // TCP ���Ӷ˿ں�

/* AXIS ����ʹ�ܱ�־ */
#define AXIS_TRANSMIT_ENABLE        1                                       // ʹ��
#define AXIS_TRANSMIT_DISABLE       0                                       // ����

/* ������� ID */
#define IIC_CAMERA                  XPAR_CAMERA_IIC_DEVICE_ID               // SC035HGS AXI_IIC
#define GPIO_CAMERA_PWDN            XPAR_CAMERA_PWDN_DEVICE_ID              // SC035HGS ���߿��ƣ���������������Ϊ�͵�ƽ��
#define GPIO_CAMERA_RESET           XPAR_CAMERA_RESET_DEVICE_ID             // SC035HGS Ӳ����λ���͵�ƽ��Ч��
#define GPIO_CAMERA_VSYNC           XPAR_CAMERA_VSYNC_DEVICE_ID             // SC035HGS DVP �����ͬ���ź�
#define GPIO_ETH_PHY_RESET          XPAR_PHY_RESET_DEVICE_ID                // ETH ��λ���ߵ�ƽ��Ч��
#define GPIO_AXIS_TRANSMIT_ENABLE   XPAR_AXIS_TRANSMIT_ENABLE_DEVICE_ID     // AXIS ����ת��ʹ�ܣ��ߵ�ƽ��Ч��

/* ���ݻ����� */
u32 FrameCachePtrReceiveIndex;                                              // ���ջ�������
u32 FrameCachePtrTransmitIndex;                                             // ���ͻ�������
u32 FrameCachePtrLastReceiveIndex;                                          // ��һ�����ջ�������
u32 FrameCachePtr[FRAME_CACHE_NUMS];                                        // ֡������

/* ������ */
XScuGic Intc;
XAxiDma AxiDma;

camera_t camera;

XGpio gpio_camera_pwdn;
XGpio gpio_camera_rstn;
XGpio gpio_camera_vsync;
XGpio gpio_eth_phy_rstn;
XGpio gpio_axis_transmit_rstn;
XGpio gpio_axis_transmit_enable;

extern volatile int Error;
extern volatile int RxDone;

void delay_ms(uint8_t ms)
{
	usleep(ms * 1000);
}


/**
 * @brief:ϵͳ��ʼ������
 * @return *
 */
void init_sys()
{
    // ��ʼ�� GPIO
    init_gpio();
    // ��ʼ������ͷ
    xil_printf("aa");
    camera.delay = delay_ms;
    camera.axi_device_id = IIC_CAMERA;
    sc035hgs_init(&camera);
    xil_printf("[Camera chip id] %u", camera.chip_id);
    // ��ʼ�� DMA
    DMA_Intr_Init(&AxiDma, 0);
	Init_Intr_System(&Intc);
	Setup_Intr_Exception(&Intc);
	DMA_Setup_Intr_System(&Intc, &AxiDma, RX_INTR_ID);
	DMA_Intr_Enable(&Intc, &AxiDma);
    // ��ʼ��֡������
    FrameCachePtrReceiveIndex  = 0;
    FrameCachePtrLastReceiveIndex = 0;
    FrameCachePtrTransmitIndex = 0;
    for(int i = 0; i < FRAME_CACHE_NUMS; i++)
    {
        FrameCachePtr[i] = RX_BUFFER_BASE + FRAME_CACHE_NUMS * i;
    }
}


void init_camera()
{
    xil_printf("[INFO] Init camera sc035hgs...\n");

    // ��ʼ�������������
    XGpio_Initialize(&gpio_camera_pwdn, GPIO_CAMERA_PWDN);
    XGpio_SetDataDirection(&gpio_camera_pwdn, 1, 0x0);
    XGpio_DiscreteWrite(&gpio_camera_pwdn, 1, 0x1);
    // ��ʼ����λ�������
    XGpio_Initialize(&gpio_camera_rstn, GPIO_CAMERA_RESET);
	XGpio_SetDataDirection(&gpio_camera_rstn, 1, 0x0);
    XGpio_DiscreteWrite(&gpio_camera_rstn, 1, 0x0);
    // ��ʼ�����ź���������
    XGpio_Initialize(&gpio_camera_vsync, GPIO_CAMERA_VSYNC);
	XGpio_SetDataDirection(&gpio_camera_vsync, 1, 0x1);
    // �ϵ�ʱ��
    usleep(6 * 1000);
    XGpio_DiscreteWrite(&gpio_camera_pwdn, 1, 0x0);
    usleep(2 * 1000);
    XGpio_DiscreteWrite(&gpio_camera_rstn, 1, 0x1);
    usleep(21 * 1000);

    xil_printf("[SUCCESS] Camera sc035hgs init done\n");
    xil_printf("[INFO] Get sc035hgs's chip id...\n");

    camera.delay = delay_ms;
    camera.axi_device_id = IIC_CAMERA;
    sc035hgs_init(&camera);

    xil_printf("[SUCCESS] Success to get chip id %u\n", camera.chip_id);
}


void init_gpio()
{
    // ��ʼ�� SC035HGS ���߿��� GPIO
    // TODO ���ֲ������������ֲ�ָ����������Ӧ���ߣ�
    XGpio_Initialize(&gpio_camera_pwdn, GPIO_CAMERA_PWDN);
	XGpio_SetDataDirection(&gpio_camera_pwdn, 1, 0x0);
    XGpio_DiscreteWrite(&gpio_camera_pwdn, 1, 0x0);
    // ��ʼ�� SC035HGS ��λ GPIO
    XGpio_Initialize(&gpio_camera_rstn, GPIO_CAMERA_RESET);
	XGpio_SetDataDirection(&gpio_camera_rstn, 1, 0x0);
    XGpio_DiscreteWrite(&gpio_camera_rstn, 1, 0x1);
    // TODO ��ʼ�����źż�� GPIO
    XGpio_Initialize(&gpio_camera_vsync, GPIO_CAMERA_VSYNC);
	XGpio_SetDataDirection(&gpio_camera_vsync, 1, 0x1);
    // ��ʼ�� AXIS ������� GPIO
    XGpio_Initialize(&gpio_axis_transmit_enable, GPIO_AXIS_TRANSMIT_ENABLE);
	XGpio_SetDataDirection(&gpio_axis_transmit_enable, 1, 0x0);
    XGpio_DiscreteWrite(&gpio_axis_transmit_enable, 1, 0x0);
    // ��λ��̫�� PHY
    XGpio_Initialize(&gpio_eth_phy_rstn, GPIO_ETH_PHY_RESET);
	XGpio_SetDataDirection(&gpio_eth_phy_rstn, 1, 0x0);
    XGpio_DiscreteWrite(&gpio_eth_phy_rstn, 1, 0x1);
    delay_ms(10);
    XGpio_DiscreteWrite(&gpio_eth_phy_rstn, 1, 0x0);
}


void set_axis_transmit(int start)
{
    if(start)
    {
        XGpio_DiscreteWrite(&gpio_axis_transmit_enable, 1, 0x1);
    }
    else
    {
        XGpio_DiscreteWrite(&gpio_axis_transmit_enable, 1, 0x0);
    }
}


void dma_transmit_thread(void* p)
{
    // ���� DMA ����
    set_axis_transmit(AXIS_TRANSMIT_ENABLE);
    XAxiDma_SimpleTransfer(&AxiDma, (u32)FrameCachePtr[FrameCachePtrReceiveIndex], (u32)(FRAME_CACHE_SIZE), XAXIDMA_DEVICE_TO_DMA);
    while(1)
    {
        if(RxDone)
        {
            // ��ս����жϱ�־λ
            RxDone = 0;
            // ȷ�� Cache �е����ݾ��� DDR ��
            Xil_DCacheInvalidateRange((u32)FrameCachePtr[FrameCachePtrReceiveIndex], FRAME_CACHE_SIZE);
            //
            FrameCachePtrLastReceiveIndex = FrameCachePtrReceiveIndex;
            FrameCachePtrReceiveIndex = (FrameCachePtrReceiveIndex + 1) % FRAME_CACHE_NUMS;
            if(FrameCachePtrReceiveIndex == FrameCachePtrTransmitIndex)
            {
                FrameCachePtrReceiveIndex = (FrameCachePtrReceiveIndex + 1) % FRAME_CACHE_NUMS;
            }
            // ������һ�� DMA ����
            XAxiDma_SimpleTransfer(&AxiDma, (u32)FrameCachePtr[FrameCachePtrReceiveIndex], (u32)(FRAME_CACHE_SIZE), XAXIDMA_DEVICE_TO_DMA);
        }
    }
}


int main(void)
{
	init_camera();
	while(1)
	{

	}
	return 0;
//	struct netif *netif;
//
//	/* the mac address of the board. this should be unique per board */
//	unsigned char mac_ethernet_address[] = {
//		0x00, 0x0a, 0x35, 0x00, 0x01, 0x02 };
//
//	netif = &server_netif;
//#if defined (__arm__) && !defined (ARMR5)
//#if XPAR_GIGE_PCS_PMA_SGMII_CORE_PRESENT == 1 || \
//		XPAR_GIGE_PCS_PMA_1000BASEX_CORE_PRESENT == 1
//	ProgramSi5324();
//	ProgramSfpPhy();
//#endif
//#endif
//
//	/* Define this board specific macro in order perform PHY reset
//	 * on ZCU102
//	 */
//#ifdef XPS_BOARD_ZCU102
//	IicPhyReset();
//#endif
//
//	init_platform();
//
//	xil_printf("\r\n\r\n");
//	xil_printf("-----lwIP RAW Mode TCP Client Application-----\r\n");
//
//	/* initialize lwIP */
//	lwip_init();
//
//	/* Add network interface to the netif_list, and set it as default */
//	if (!xemac_add(netif, NULL, NULL, NULL, mac_ethernet_address,
//				PLATFORM_EMAC_BASEADDR)) {
//		xil_printf("Error adding N/W interface\r\n");
//		return -1;
//	}
//
//#if LWIP_IPV6==1
//	netif->ip6_autoconfig_enabled = 1;
//	netif_create_ip6_linklocal_address(netif, 1);
//	netif_ip6_addr_set_state(netif, 0, IP6_ADDR_VALID);
//	print_ipv6("\n\rlink local IPv6 address is:",&netif->ip6_addr[0]);
//#endif /* LWIP_IPV6 */
//	netif_set_default(netif);
//
//	/* now enable interrupts */
//	platform_enable_interrupts();
//
//	/* specify that the network if is up */
//	netif_set_up(netif);
//
//#if (LWIP_IPV6==0)
//#if (LWIP_DHCP==1)
//	/* Create a new DHCP client for this interface.
//	 * Note: you must call dhcp_fine_tmr() and dhcp_coarse_tmr() at
//	 * the predefined regular intervals after starting the client.
//	 */
//	dhcp_start(netif);
//	dhcp_timoutcntr = 24;
//	while (((netif->ip_addr.addr) == 0) && (dhcp_timoutcntr > 0))
//		xemacif_input(netif);
//
//	if (dhcp_timoutcntr <= 0) {
//		if ((netif->ip_addr.addr) == 0) {
//			xil_printf("ERROR: DHCP request timed out\r\n");
//			assign_default_ip(&(netif->ip_addr),
//					&(netif->netmask), &(netif->gw));
//		}
//	}
//
//	/* print IP address, netmask and gateway */
//#else
//	assign_default_ip(&(netif->ip_addr), &(netif->netmask), &(netif->gw));
//#endif
//	print_ip_settings(&(netif->ip_addr), &(netif->netmask), &(netif->gw));
//#endif /* LWIP_IPV6 */
//	xil_printf("\r\n");
//
//	/* print app header */
//	print_app_header();
//
//	/* start the application*/
//	start_application();
//	xil_printf("\r\n");
//
//	while (1) {
//		if (TcpFastTmrFlag) {
//			tcp_fasttmr();
//			TcpFastTmrFlag = 0;
//		}
//		if (TcpSlowTmrFlag) {
//			tcp_slowtmr();
//			TcpSlowTmrFlag = 0;
//		}
//		xemacif_input(netif);
//		transfer_data();
//	}
//
//	/* never reached */
//	cleanup_platform();
//
//	return 0;
}
