#include <stdio.h>
#include "xgpio.h"
#include "xparameters.h"
#include "netif/xadapter.h"
#include "platform.h"
#include "platform_config.h"
#include "lwipopts.h"
#include "xil_printf.h"
#include "sleep.h"
#include "tcp_client.h"
#include "lwip/priv/tcp_priv.h"
#include "lwip/init.h"
#include "lwip/inet.h"
#include "sc035hgs.h"
#include "dma_intr.h"
#include "sys_intr.h"


/* ������������� */
#define FRAME_WIDTH                 640                                     // ֡���
#define FRAME_HEIGHT                480                                     // ֡�߶�
#define CAMERA_IGNORE_FRAME_NUMS    10                                      // ����ͷ�ȶ�����֡������ʼ����һ��ʱ����������ȶ���
#define FRAME_CACHE_SIZE            FRAME_WIDTH * FRAME_HEIGHT              // ֡��������С����λ���ֽڣ�
#define FRAME_CACHE_NUMS            3                                       // ֡����������

/* IP ������� */
#define DEFAULT_IP_ADDRESS	        "192.168.1.10"                          // ���� IP
#define DEFAULT_IP_MASK		        "255.255.255.0"                         // ����
#define DEFAULT_GW_ADDRESS	        "192.168.1.1"                           // ����

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
#define DMA_CAMERA_OUTPUT_TRANSMIT  XPAR_AXI_DMA_0_DEVICE_ID                // DMA

extern volatile int TcpFastTmrFlag;
extern volatile int TcpSlowTmrFlag;

uint8_t MAC_ETHERNET_ADDRESS[] = { 0x00, 0x0a, 0x35, 0x00, 0x01, 0x02 };
struct netif server_netif;

/* ���ݻ����� */
u32 FrameCachePtrReceiveIndex;                                              // ���ջ�������
u32 FrameCachePtrTransmitIndex;                                             // ���ͻ�������
u32 FrameCachePtrLastReceiveIndex;                                          // ��һ�����ջ�������
u32 FrameCachePtr[FRAME_CACHE_NUMS + 1];                                    // ֡������

/* ������ */
XScuGic Intc;
XAxiDma AxiDma;
camera_t camera;
XGpio gpio_camera_pwdn;
XGpio gpio_camera_rstn;
XGpio gpio_camera_vsync;
XGpio gpio_eth_phy_rstn;
XGpio gpio_axis_transmit_enable;

void init_system();
void init_camera();
void init_axis_transmit();
void init_eth_phy();
void init_tcp();
void set_axis_transmit(int start);
void dma_rx_handler();
void wait_camera_ready();
uint8_t rgb2grayscale(uint8_t r, uint8_t g, uint8_t b);
uint8_t **ptr_converter(uint8_t *ptr, uint32_t width, uint32_t height);
void bayer2grayscale(uint8_t **bayer, uint8_t **grayscale, uint16_t image_width, uint16_t image_height);

int main(void)
{
    init_system();
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
        xemacif_input(&server_netif);
        if(FrameCachePtrTransmitIndex != FrameCachePtrLastReceiveIndex)
        {
            // �� Bayer ת��Ϊ�Ҷ�ͼ��
            FrameCachePtrTransmitIndex = FrameCachePtrLastReceiveIndex;
            bayer2grayscale(ptr_converter((uint8_t*)FrameCachePtr[FrameCachePtrTransmitIndex], FRAME_WIDTH, FRAME_HEIGHT), 
                ptr_converter((uint8_t*)FrameCachePtr[FRAME_CACHE_NUMS], FRAME_WIDTH, FRAME_HEIGHT), FRAME_WIDTH, FRAME_HEIGHT);
            // TCP ����
            tcp_client_send((uint8_t*)FrameCachePtr[FRAME_CACHE_NUMS], FRAME_CACHE_SIZE);
        }
	}
    cleanup_platform();
	return 0;
}


/**
 * @brief:ϵͳ��ʼ������
 * @return *
 */
void init_system()
{
    // ��ʼ��ƽ̨
    init_platform();
    // ��ʼ������
    init_eth_phy();
    init_tcp();
    // ��ʼ�� AXIS ����ת��ģ��
    init_axis_transmit();
    // ��ʼ������ͷ
    init_camera();
    // ��ʼ�� DMA
    DMA_Intr_Init(&AxiDma, 0);
	Init_Intr_System(&Intc);
	Setup_Intr_Exception(&Intc);
	DMA_Setup_Intr_System(&Intc, &AxiDma, RX_INTR_ID);
    DMA_Handler_Init(NULL, dma_rx_handler, NULL);
	DMA_Intr_Enable(&Intc, &AxiDma);
    // ��ʼ��֡������
    FrameCachePtrReceiveIndex  = 0;
    FrameCachePtrLastReceiveIndex = 0;
    FrameCachePtrTransmitIndex = 0;
    for(int i = 0; i < FRAME_CACHE_NUMS + 1; i++)
    {
        FrameCachePtr[i] = RX_BUFFER_BASE + FRAME_CACHE_NUMS * i;
    }
    // �ȴ�����ͷ����ȶ�
    wait_camera_ready();
    set_axis_transmit(AXIS_TRANSMIT_ENABLE);
}


/**
 * @brief ��ʼ������ͷ
 * @return *
*/
void init_camera()
{
    xil_printf("[INFO] Init camera sc035hgs...\n");

    // ��ʼ�������������
    // TODO ���ֲ������������ֲ�ָ����������Ӧ���ߣ�
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
    // ��ʼ������ͷ�Ĵ���
    xil_printf("[INFO] Get sc035hgs's chip id...\n");
    sc035hgs_init(&camera, IIC_CAMERA);
    xil_printf("[SUCCESS] Camera sc035hgs's chip id is %u\n", camera.chip_id);
}


/**
 * @brief ��ʼ�� AXIS ���ݴ���ģ��
 * @return *
*/
void init_axis_transmit()
{
    XGpio_Initialize(&gpio_axis_transmit_enable, GPIO_AXIS_TRANSMIT_ENABLE);
    XGpio_SetDataDirection(&gpio_axis_transmit_enable, 1, 0x0);
    XGpio_DiscreteWrite(&gpio_axis_transmit_enable, 1, 0x0);
}


/**
 * @brief ��ʼ����̫�� PHY оƬ
 * @return *
*/
void init_eth_phy()
{
    XGpio_Initialize(&gpio_eth_phy_rstn, GPIO_ETH_PHY_RESET);
	XGpio_SetDataDirection(&gpio_eth_phy_rstn, 1, 0x0);
    XGpio_DiscreteWrite(&gpio_eth_phy_rstn, 1, 0x0);
    usleep(10 * 1000);
    XGpio_DiscreteWrite(&gpio_eth_phy_rstn, 1, 0x1);
}


/**
 * @brief Ϊ������ IP ��ַ
 * @param ip    IP ��ַ
 * @param mask  Ĭ������
 * @param gw    Ĭ������
 * @return *
*/
static void assign_default_ip(ip_addr_t *ip, ip_addr_t *mask, ip_addr_t *gw)
{
	int err;

	xil_printf("[INFO] Configuring default IP %s\r\n", ip);

	err = inet_aton(DEFAULT_IP_ADDRESS, ip);
	if (!err)
    {
        xil_printf("[ERROR] Invalid default IP address: %d\r\n", err);
    }
		

	err = inet_aton(DEFAULT_IP_MASK, mask);
	if (!err)
    {
        xil_printf("[ERROR] Invalid default IP MASK: %d\r\n", err);
    }
		
	err = inet_aton(DEFAULT_GW_ADDRESS, gw);
	if (!err)
    {
        xil_printf("[ERROR] Invalid default gateway address: %d\r\n", err);
    }
}


/**
 * @brief ��ʼ�� TCP
 * @return *
*/
void init_tcp()
{
    // ��ʼ�� LWIP
	lwip_init();
    // ��������ӿ��������б�
	if(!xemac_add(&server_netif, NULL, NULL, NULL, MAC_ETHERNET_ADDRESS, PLATFORM_EMAC_BASEADDR)) 
    {
		xil_printf("Error adding N/W interface\r\n"); return;
	}
    // ����Ĭ������
	netif_set_default(&server_netif);
    // ʹ���ж�
	platform_enable_interrupts();
    // ��������
	netif_set_up(&server_netif);
    // �������� IP
	assign_default_ip(&(server_netif.ip_addr), &(server_netif.netmask), &(server_netif.gw));
	// ��ʼ���ͻ���
    tcp_client_init();
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
        XGpio_DiscreteWrite(&gpio_axis_transmit_enable, 1, 0x1);
    }
    else
    {
        XGpio_DiscreteWrite(&gpio_axis_transmit_enable, 1, 0x0);
    }
}


/**
 * @brief DMA �����жϺ���
 * @return *
*/
void dma_rx_handler()
{
    // ȷ�����ݾ��� DDR ��
    Xil_DCacheInvalidateRange((u32)FrameCachePtr[FrameCachePtrReceiveIndex], FRAME_CACHE_SIZE);
    // ����֡����������
    FrameCachePtrLastReceiveIndex = FrameCachePtrReceiveIndex;
    FrameCachePtrReceiveIndex = (FrameCachePtrReceiveIndex + 1) % FRAME_CACHE_NUMS;
    if(FrameCachePtrReceiveIndex == FrameCachePtrTransmitIndex)
    {
        FrameCachePtrReceiveIndex = (FrameCachePtrTransmitIndex + 1) % FRAME_CACHE_NUMS;
    }
    // ������һ�� DMA ����
    XAxiDma_SimpleTransfer(&AxiDma, (u32)FrameCachePtr[FrameCachePtrReceiveIndex], (u32)(FRAME_CACHE_SIZE), XAXIDMA_DEVICE_TO_DMA);
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
        while(XGpio_DiscreteRead(&gpio_camera_vsync, 1) == 0x0);
        while(XGpio_DiscreteRead(&gpio_camera_vsync, 1) == 0x1);
        frame_count++;
    }
}


/**
 * @brief RGB ת�Ҷ�
 * @param r R ͨ������ֵ
 * @param g G ͨ������ֵ
 * @param b B ͨ������ֵ
 * @return �Ҷ�����ֵ
*/
uint8_t rgb2grayscale(uint8_t r, uint8_t g, uint8_t b)
{
    return (r + g + b) / 3;
}


/**
 * @brief һάָ��ת��Ϊ��ά
 * @param ptr       ��ת����һάָ��
 * @param width     ��ά�����г�
 * @param height    ��ά��������
 * @return ת����Ķ�ά����
*/
uint8_t **ptr_converter(uint8_t *ptr, uint32_t width, uint32_t height)
{
    uint8_t **convertPtr = (uint8_t**)malloc(sizeof(uint8_t*) * height);
    for(uint32_t i = 0; i < height; i++)
    {
        convertPtr[i] = &ptr[width * i];
    } 
    return convertPtr;
}


/**
 * @brief �� bayer BG_GR ת��Ϊ�Ҷ�ͼ
 * @param bayer bayer ͼ�񻺳���
 * @param grayscale �Ҷ�ͼ�񻺳���
 * @param image_width ͼ����
 * @param image_height ͼ��߶�
*/
void bayer2grayscale(uint8_t **bayer, uint8_t **grayscale, uint16_t image_width, uint16_t image_height)
{
    if((image_width < 2) || (image_height < 2))
    {
        return;
    }

    if((image_width % 2 != 0) || (image_height % 2 != 0))
    {
        return;
    }

    // ��������Χ����
    for(uint16_t row = 0; row < image_height; row++)
    {
        if(row == 0)
        {
            grayscale[0][0] = rgb2grayscale(bayer[1][1], (bayer[0][1] + bayer[1][0]) / 2, bayer[0][0]);
            grayscale[0][image_width - 1] = rgb2grayscale(bayer[1][image_width - 1], bayer[0][image_width - 1], bayer[0][image_width - 2]);
            for(uint16_t col = 1; col < image_width - 1; col++)
            {
                grayscale[0][col] = (col % 2 == 0) ? rgb2grayscale((bayer[1][col - 1] + bayer[1][col + 1]) / 2, (bayer[0][col - 1] + bayer[0][col + 1] + bayer[1][col]) / 3, bayer[0][col]) :
                    rgb2grayscale(bayer[1][col], bayer[0][col], (bayer[0][col - 1] + bayer[0][col + 1]) / 2);
            }
        }
        else if(row == image_height - 1)
        {
            grayscale[image_height - 1][0] = rgb2grayscale(bayer[image_height - 1][1], bayer[image_height - 1][0], bayer[image_height - 2][0]);
            grayscale[image_height - 1][image_width - 1] = rgb2grayscale(bayer[image_height - 1][image_width - 1], (bayer[image_height - 1][image_width - 2] + bayer[image_height - 2][image_width - 1]) / 2, bayer[image_height - 2][image_width - 2]);
            for(uint16_t col = 1; col < image_width - 1; col++)
            {
                grayscale[image_height - 1][col] = (col % 2 == 0) ? rgb2grayscale((bayer[image_height - 1][col - 1] + bayer[image_height - 1][col + 1]) / 2, bayer[image_height - 1][col], bayer[image_height - 2][col]) : 
                    rgb2grayscale(bayer[image_height - 1][col], (bayer[image_height - 1][col - 1] + bayer[image_height - 1][col + 1] + bayer[image_height - 2][col]) / 3, (bayer[image_height - 2][col - 1] + bayer[image_height - 2][col + 1]));
            }
        }
        else
        {
            // �Ƕ���߽�����
            grayscale[row][0] = (row % 2 == 0) ? rgb2grayscale((bayer[row - 1][1] + bayer[row + 1][1]) / 2, (bayer[row - 1][0] + bayer[row + 1][0] + bayer[row][1]) / 3, bayer[row][0]) :
                rgb2grayscale(bayer[row][1], bayer[row][0], (bayer[row - 1][0] + bayer[row + 1][0]) / 2);
            grayscale[row][image_width - 1] = (row % 2 == 0) ? rgb2grayscale(bayer[row - 1][image_width - 1], bayer[row][image_width - 1], bayer[row][image_width - 2]) :
                rgb2grayscale(bayer[row][image_width - 1], (bayer[row][image_width - 2] + bayer[row - 1][image_width - 1] + bayer[row + 1][image_width - 1]) / 3, (bayer[row - 1][image_width - 2] + bayer[row + 1][image_width - 2]) / 2);
        }
    }

    // �����ڲ����ص�
    for(uint16_t row = 1; row < image_height - 1; row++)
    {
        if(row % 2 == 0)
        {
            // G
            for(uint16_t col = 1; col < image_width - 1; col += 2)
            {
                grayscale[row][col] = rgb2grayscale((bayer[row - 1][col] + bayer[row + 1][col]) / 2, bayer[row][col], (bayer[row][col - 1] + bayer[row][col + 1]) / 2);
            }
            // B
            for(uint16_t col = 2; col < image_width - 1; col += 2)
            {
                grayscale[row][col] = rgb2grayscale((bayer[row - 1][col - 1] + bayer[row - 1][col + 1] + bayer[row + 1][col - 1] + bayer[row + 1][col + 1]) / 4, (bayer[row - 1][col] + bayer[row][col - 1] + bayer[row][col + 1] + bayer[row + 1][col]) / 4, bayer[row][col]);
            }
        }
        else
        {
            // R
            for(uint16_t col = 1; col < image_width - 1; col += 2)
            {
                grayscale[row][col] = rgb2grayscale(bayer[row][col], (bayer[row][col - 1] + bayer[row][col + 1] + bayer[row - 1][col] + bayer[row + 1][col]) / 4, (bayer[row - 1][col - 1] + bayer[row - 1][col + 1] + bayer[row + 1][col - 1] + bayer[row + 1][col + 1]) / 4);
            }
            // G
            for(uint16_t col = 2; col < image_width - 1; col += 2)
            {
                grayscale[row][col] = rgb2grayscale((bayer[row][col - 1] + bayer[row][col + 1]) / 2, bayer[row][col], (bayer[row - 1][col] + bayer[row + 1][col]) / 2);
            }
        }
    }
}
