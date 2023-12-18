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

/* �����ջ��С */
#define THREAD_STACKSIZE 			2048

/* ������� ID */
#define DEVICE_IICS                 XPAR_I2CS_DEVICE_ID
#define DEVICE_BUFW_FS				XPAR_BUFW_FS_DEVICE_ID
#define DEVICE_BUFW_RSTN			XPAR_BUFW_RSTN_DEVICE_ID
#define DEVICE_CAMERA_PWDN			XPAR_CAMERA_PWDN_DEVICE_ID
#define DEVICE_CAMERA_HREF			XPAR_CAMERA_HREF_DEVICE_ID
#define DEVICE_CAMERA_VSYNC			XPAR_CAMERA_VSYNC_DEVICE_ID
#define DEVICE_XCLK_LOCKED			XPAR_XCLK_LOCKED_DEVICE_ID
#define DEVICE_PHY_RETN				XPAR_PHY_RSTN_DEVICE_ID

/* ������������� */
#define CAMERA_IGNORE_FRAME_NUMS    10                                      // ����ͷ�ȶ�����֡������ʼ����һ��ʱ����������ȶ���

/* ����ͷ��� */
camera_t camera;

/* GPIO & ȫ���жϾ�� */
XGpio gpio_bufw_fs;
XGpio gpio_bufw_rstn;
XGpio gpio_camera_pwdn;
XGpio gpio_camera_xclk_locked;
XGpio gpio_camera_vsync;
XGpio gpio_camera_href;
XGpio gpio_phy_rstn;

// TODO DMA ������ TCP �޷�ͬʱ���У�DMA һ�� ping ��ͨ
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

	// ��ʼ�� LWIP
	lwip_init();

	// ��ʼ�� IP & MASK & GATWALL
	IP4_ADDR(&ipaddr, 192, 168, 1, 10);
	IP4_ADDR(&netmask, 255, 255, 255, 0);
	IP4_ADDR(&gw, 192, 168, 1, 1);

	// �������ӿ�
	if(!xemac_add(&server_netif, &ipaddr, &netmask, &gw, mac_ethernet_address, PLATFORM_EMAC_BASEADDR))
	{
		xil_printf("[ERROR] Failed to add N/W interface\n");
		return;
	}
    netif_set_default(&server_netif);
    netif_set_up(&server_netif);

    // ������λ�������߳�
	sys_thread_new("xemacif_input_thread", (void(*)(void*))xemacif_input_thread, &server_netif, THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);
	sys_thread_new("upper_transmit_thread", upper_transmit_thread, 0, THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);

	vTaskDelete(NULL);
}

/**
 * @brief ���߳�
 * @return
 */
void main_thread(void *p)
{
	// ��������
    sys_thread_new("network_thread", network_thread, NULL, THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);

    // ϵͳ��ʼ��
	system_init();

    vTaskDelete(NULL);
}


/**
 * @brief:ϵͳ��ʼ������
 * @param p
 * @return *
 */
void system_init()
{
	// ��ʼ�� AXIS ����ת��ģ��
	init_axis_transmit();

	// ��ʼ������ͷ
	init_camera();

	/* DMA */
	DMA_Intr_Init(&AxiDma, 0);
	DMA_Setup_Intr_System(&xInterruptController, &AxiDma, RX_INTR_ID);
	DMA_Intr_Enable(&xInterruptController, &AxiDma);

	/* ֡������ */
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

	// ���� BUFW ��λ
	XGpio_DiscreteWrite(&gpio_bufw_rstn, 1, 0x1);

	// �ȴ�����ͷ����ȶ�
	wait_camera_ready();

	// ʹ�� AXIS ģ��
	set_axis_transmit(1);

	// �����״� DMA ����
	XAxiDma_SimpleTransfer(&AxiDma, (u32)RxBufferPtr[RxBufferPtrReceiveIndex], (u32)(RX_BUFFER_SIZE), XAXIDMA_DEVICE_TO_DMA);
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
    if(sc035hgs_init(&camera) != XST_SUCCESS)
    {
    	xil_printf("[ERROR] Success to init sc035hgs\n");
    	return;
    }
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
