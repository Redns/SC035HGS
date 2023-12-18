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

/* ������������� */
#define CAMERA_IGNORE_FRAME_NUMS    10                                      // ����ͷ�ȶ�����֡������ʼ����һ��ʱ����������ȶ���

u8 EthTransmitCache[FRAME_SIZE + 1];

/* IP ������� */
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

/* ������� ID */
#define DEVICE_IICS                 XPAR_I2CS_DEVICE_ID						// SC035HGS IIC ����
#define DEVICE_BUFW_FS				XPAR_BUFW_FS_DEVICE_ID
#define DEVICE_BUFW_RSTN			XPAR_BUFW_RSTN_DEVICE_ID
#define DEVICE_CAMERA_PWDN			XPAR_CAMERA_PWDN_DEVICE_ID
#define DEVICE_CAMERA_HREF			XPAR_CAMERA_HREF_DEVICE_ID
#define DEVICE_CAMERA_VSYNC			XPAR_CAMERA_VSYNC_DEVICE_ID
#define DEVICE_XCLK_LOCKED			XPAR_XCLK_LOCKED_DEVICE_ID
#define DEVICE_PHY_RETN				XPAR_PHY_RSTN_DEVICE_ID

extern XScuGic Intc;
extern XAxiDma AxiDma;

extern u32 RxBufferPtrReceiveIndex;                                              // ���ջ�������
extern u32 RxBufferPtrTransmitIndex;                                             // ���ͻ�������
extern u32 RxBufferPtrLastReceiveIndex;                                          // ��һ�����ջ�������
extern u32 RxBufferPtr[RX_BUFFER_NUMS];                                    // ֡��������RAW, RAW...��RAW, RGB��
extern u32 RxBufferFrameStartAddrPtr[RX_BUFFER_NUMS];

/* ������ */
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
//			            // �� Bayer ת��Ϊ�Ҷ�ͼ��
//			            RxBufferPtrTransmitIndex = RxBufferPtrLastReceiveIndex;
//						//bayer2grayscale(ptr_converter((u8*)RxBufferPtr[RxBufferPtrTransmitIndex], FRAME_WIDTH, FRAME_HEIGHT), &EthTransmitCache, FRAME_WIDTH, FRAME_HEIGHT);
//
//						// ����ǰ��֡
//			//			char *image_front_frame = generate_image_front_frame(0, FRAME_SIZE, FRAME_WIDTH, FRAME_HEIGHT, Format_Grayscalec8);
//			//			tcp_write(client, image_front_frame, strlen(image_front_frame), 1);
//			            char *image_front_frame = generate_image_front_frame(0, 64, 8, 8, Format_Grayscalec8);
//			            			tcp_write(client, image_front_frame, strlen(image_front_frame), 1);
//
//						// ͼƬ���ݷ���
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

	// ��λ PHY оƬ
	Xil_Out32(0x41230000,3);

	echo_netif = &server_netif;

	// ��ʼ��ƽ̨
	init_platform();

	// DHCP
	ipaddr.addr = 0;
	gw.addr = 0;
	netmask.addr = 0;

	// ��ʼ�� LWIP
	lwip_init();

	// �������ӿ�
	if(!xemac_add(echo_netif, &ipaddr, &netmask, &gw, mac_ethernet_address, PLATFORM_EMAC_BASEADDR))
	{
		xil_printf("[ERROR] Failed to add eth interface\n");
		return XST_FAILURE;
	}
	netif_set_default(echo_netif);

	// ʹ���ж�
	platform_enable_interrupts();

	// ��������ӿ�
	netif_set_up(echo_netif);

	// ��ʼ�� IP ��ַ
	IP4_ADDR(&ipaddr,  ethernet_ip_address[0], ethernet_ip_address[1], ethernet_ip_address[2], ethernet_ip_address[3]);
	IP4_ADDR(&netmask, ethernet_ip_mask[0], ethernet_ip_mask[1], ethernet_ip_mask[2], ethernet_ip_mask[3]);
	IP4_ADDR(&gw, ethernet_gw_address[0], ethernet_gw_address[1], ethernet_gw_address[2], ethernet_gw_address[3]);

	ipaddr.addr = echo_netif->ip_addr.addr;
	gw.addr = echo_netif->gw.addr;
	netmask.addr = echo_netif->netmask.addr;

	// ���� TCP ����
	struct tcp_pcb *pcb = tcp_new_ip_type(IPADDR_TYPE_ANY);
	if(!pcb)
	{
		xil_printf("[ERROR] Failed to create tcp server pcb, out of memory\n");
		return XST_FAILURE;
	}

	// �󶨶˿ں�
	if(tcp_bind(pcb, IP_ANY_TYPE, port) != ERR_OK)
	{
		xil_printf("[ERROR] Failed to bind port %d\n", port);
		return XST_FAILURE;
	}
	tcp_arg(pcb, NULL);

	// ��������
	pcb = tcp_listen(pcb);
	if(!pcb)
	{
		xil_printf("[ERROR] Out of memory while tcp_listen\n");
		return XST_FAILURE;
	}

	// ���ӻص�����
	tcp_accept(pcb, accept_callback);

	xil_printf("[INFO] Success to init lwip server\n");
	return XST_SUCCESS;
}


/**
 * @brief:ϵͳ��ʼ������
 * @return *
 */
void init_system()
{
//    // ��ʼ�� AXIS ����ת��ģ��
//    init_axis_transmit();
//
//    // ��ʼ������ͷ
//    init_camera();
//
//    /* DMA */
//    DMA_Intr_Init(&AxiDma, 0);
//	Init_Intr_System(&Intc);
//	Setup_Intr_Exception(&Intc);
//	DMA_Setup_Intr_System(&Intc, &AxiDma, RX_INTR_ID);
//	DMA_Intr_Enable(&Intc, &AxiDma);
//
//    /* ֡������ */
//	RxBufferPtrReceiveIndex  = 0;
//	RxBufferPtrLastReceiveIndex = 0;
//	RxBufferPtrTransmitIndex = 0;
//    for(int i = 0; i < RX_BUFFER_NUMS + 1; i++)
//    {
//    	RxBufferFrameStartAddrPtr[i] = 0;
//    	RxBufferPtr[i] = RX_BUFFER_BASE + RX_BUFFER_SIZE * i;
//    }
//
//    // ���� BUFW ��λ
//    XGpio_DiscreteWrite(&gpio_bufw_rstn, 1, 0x1);
//
//    // �ȴ�����ͷ����ȶ�
//	wait_camera_ready();
//
//    // ʹ�� AXIS ģ��
//    set_axis_transmit(1);
//
//    // �����״� DMA ����
//    XAxiDma_SimpleTransfer(&AxiDma, (u32)RxBufferPtr[RxBufferPtrReceiveIndex], (u32)(RX_BUFFER_SIZE), XAXIDMA_DEVICE_TO_DMA);

    // ��ʼ�����紫��
	eth_init();
}


/**
 * @brief ��ʼ������ͷ
 * @return *
*/
void init_camera()
{
    xil_printf("[INFO] Start to init camera...\n");

    // ��ʼ�������������
    XGpio_Initialize(&gpio_camera_pwdn, DEVICE_CAMERA_PWDN);
    XGpio_SetDataDirection(&gpio_camera_pwdn, 1, 0x0);
    XGpio_DiscreteWrite(&gpio_camera_pwdn, 1, 0x0);
    // ��ʼ��ʱ��������������
    XGpio_Initialize(&gpio_camera_xclk_locked, DEVICE_XCLK_LOCKED);
	XGpio_SetDataDirection(&gpio_camera_xclk_locked, 1, 0x1);
    // �ȴ�����ͷ����ʱ������
    while(XGpio_DiscreteRead(&gpio_camera_xclk_locked, 1) == 0);
    // ��ʼ�����ź���������
    XGpio_Initialize(&gpio_camera_vsync, DEVICE_CAMERA_VSYNC);
	XGpio_SetDataDirection(&gpio_camera_vsync, 1, 0x1);
    // ���� PWDN ������������ͷ
    XGpio_DiscreteWrite(&gpio_camera_pwdn, 1, 0x1);
    // ���� PWDN �����ٵȴ� 4ms ���ܷ��ʼĴ���
    usleep(20 * 1000);

    // ��ʼ������ͷ�Ĵ���
    camera.i2c_device_id = DEVICE_IICS;
    sc035hgs_init(&camera);

    xil_printf("[SUCCESS] Init camera done\n");
}


/**
 * @brief ��ʼ�� AXIS ���ݴ���ģ��
 * @return *
*/
void init_axis_transmit()
{
	// ��λ
	XGpio_Initialize(&gpio_bufw_rstn, DEVICE_BUFW_RSTN);
	XGpio_SetDataDirection(&gpio_bufw_rstn, 1, 0x0);
	XGpio_DiscreteWrite(&gpio_bufw_rstn, 1, 0x0);

	// �������
    XGpio_Initialize(&gpio_bufw_fs, DEVICE_BUFW_FS);
    XGpio_SetDataDirection(&gpio_bufw_fs, 1, 0x0);
    XGpio_DiscreteWrite(&gpio_bufw_fs, 1, 0x0);
}


/**
 * @brief ʹ�� AXIS ���ݴ���
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
 * @brief �ȴ�����ͷ׼����
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
