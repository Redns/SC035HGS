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


/* 缓冲区相关设置 */
#define FRAME_WIDTH                 640                                     // 帧宽度
#define FRAME_HEIGHT                480                                     // 帧高度
#define CAMERA_IGNORE_FRAME_NUMS    10                                      // 摄像头稳定所需帧数（初始化后一段时间内输出不稳定）
#define FRAME_CACHE_SIZE            FRAME_WIDTH * FRAME_HEIGHT              // 帧缓冲区大小（单位：字节）
#define FRAME_CACHE_NUMS            3                                       // 帧缓冲区数量

/* IP 相关设置 */
#define DEFAULT_IP_ADDRESS	        "192.168.1.10"                          // 本机 IP
#define DEFAULT_IP_MASK		        "255.255.255.0"                         // 掩码
#define DEFAULT_GW_ADDRESS	        "192.168.1.1"                           // 网关

/* AXIS 传输使能标志 */
#define AXIS_TRANSMIT_ENABLE        1                                       // 使能
#define AXIS_TRANSMIT_DISABLE       0                                       // 禁用

/* 相关外设 ID */
#define IIC_CAMERA                  XPAR_CAMERA_IIC_DEVICE_ID               // SC035HGS AXI_IIC
#define GPIO_CAMERA_PWDN            XPAR_CAMERA_PWDN_DEVICE_ID              // SC035HGS 休眠控制（正常工作需设置为低电平）
#define GPIO_CAMERA_RESET           XPAR_CAMERA_RESET_DEVICE_ID             // SC035HGS 硬件复位（低电平有效）
#define GPIO_CAMERA_VSYNC           XPAR_CAMERA_VSYNC_DEVICE_ID             // SC035HGS DVP 输出场同步信号
#define GPIO_ETH_PHY_RESET          XPAR_PHY_RESET_DEVICE_ID                // ETH 复位（高电平有效）
#define GPIO_AXIS_TRANSMIT_ENABLE   XPAR_AXIS_TRANSMIT_ENABLE_DEVICE_ID     // AXIS 数据转换使能（高电平有效）
#define DMA_CAMERA_OUTPUT_TRANSMIT  XPAR_AXI_DMA_0_DEVICE_ID                // DMA

extern volatile int TcpFastTmrFlag;
extern volatile int TcpSlowTmrFlag;

uint8_t MAC_ETHERNET_ADDRESS[] = { 0x00, 0x0a, 0x35, 0x00, 0x01, 0x02 };
struct netif server_netif;

/* 数据缓冲区 */
u32 FrameCachePtrReceiveIndex;                                              // 接收缓存索引
u32 FrameCachePtrTransmitIndex;                                             // 发送缓存索引
u32 FrameCachePtrLastReceiveIndex;                                          // 上一个接收缓存索引
u32 FrameCachePtr[FRAME_CACHE_NUMS + 1];                                    // 帧缓冲区

/* 外设句柄 */
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
            // 将 Bayer 转换为灰度图像
            FrameCachePtrTransmitIndex = FrameCachePtrLastReceiveIndex;
            bayer2grayscale(ptr_converter((uint8_t*)FrameCachePtr[FrameCachePtrTransmitIndex], FRAME_WIDTH, FRAME_HEIGHT), 
                ptr_converter((uint8_t*)FrameCachePtr[FRAME_CACHE_NUMS], FRAME_WIDTH, FRAME_HEIGHT), FRAME_WIDTH, FRAME_HEIGHT);
            // TCP 发送
            tcp_client_send((uint8_t*)FrameCachePtr[FRAME_CACHE_NUMS], FRAME_CACHE_SIZE);
        }
	}
    cleanup_platform();
	return 0;
}


/**
 * @brief:系统初始化函数
 * @return *
 */
void init_system()
{
    // 初始化平台
    init_platform();
    // 初始化网口
    init_eth_phy();
    init_tcp();
    // 初始化 AXIS 数据转换模块
    init_axis_transmit();
    // 初始化摄像头
    init_camera();
    // 初始化 DMA
    DMA_Intr_Init(&AxiDma, 0);
	Init_Intr_System(&Intc);
	Setup_Intr_Exception(&Intc);
	DMA_Setup_Intr_System(&Intc, &AxiDma, RX_INTR_ID);
    DMA_Handler_Init(NULL, dma_rx_handler, NULL);
	DMA_Intr_Enable(&Intc, &AxiDma);
    // 初始化帧缓冲区
    FrameCachePtrReceiveIndex  = 0;
    FrameCachePtrLastReceiveIndex = 0;
    FrameCachePtrTransmitIndex = 0;
    for(int i = 0; i < FRAME_CACHE_NUMS + 1; i++)
    {
        FrameCachePtr[i] = RX_BUFFER_BASE + FRAME_CACHE_NUMS * i;
    }
    // 等待摄像头输出稳定
    wait_camera_ready();
    set_axis_transmit(AXIS_TRANSMIT_ENABLE);
}


/**
 * @brief 初始化摄像头
 * @return *
*/
void init_camera()
{
    xil_printf("[INFO] Init camera sc035hgs...\n");

    // 初始化休眠输出引脚
    // TODO 与手册描述不符（手册指明正常工作应拉高）
    XGpio_Initialize(&gpio_camera_pwdn, GPIO_CAMERA_PWDN);
    XGpio_SetDataDirection(&gpio_camera_pwdn, 1, 0x0);
    XGpio_DiscreteWrite(&gpio_camera_pwdn, 1, 0x1);
    // 初始化复位输出引脚
    XGpio_Initialize(&gpio_camera_rstn, GPIO_CAMERA_RESET);
	XGpio_SetDataDirection(&gpio_camera_rstn, 1, 0x0);
    XGpio_DiscreteWrite(&gpio_camera_rstn, 1, 0x0);
    // 初始化场信号输入引脚
    XGpio_Initialize(&gpio_camera_vsync, GPIO_CAMERA_VSYNC);
	XGpio_SetDataDirection(&gpio_camera_vsync, 1, 0x1);
    // 上电时序
    usleep(6 * 1000);
    XGpio_DiscreteWrite(&gpio_camera_pwdn, 1, 0x0);
    usleep(2 * 1000);
    XGpio_DiscreteWrite(&gpio_camera_rstn, 1, 0x1);
    usleep(21 * 1000);
    xil_printf("[SUCCESS] Camera sc035hgs init done\n");
    // 初始化摄像头寄存器
    xil_printf("[INFO] Get sc035hgs's chip id...\n");
    sc035hgs_init(&camera, IIC_CAMERA);
    xil_printf("[SUCCESS] Camera sc035hgs's chip id is %u\n", camera.chip_id);
}


/**
 * @brief 初始化 AXIS 数据传输模块
 * @return *
*/
void init_axis_transmit()
{
    XGpio_Initialize(&gpio_axis_transmit_enable, GPIO_AXIS_TRANSMIT_ENABLE);
    XGpio_SetDataDirection(&gpio_axis_transmit_enable, 1, 0x0);
    XGpio_DiscreteWrite(&gpio_axis_transmit_enable, 1, 0x0);
}


/**
 * @brief 初始化以太网 PHY 芯片
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
 * @brief 为网卡绑定 IP 地址
 * @param ip    IP 地址
 * @param mask  默认掩码
 * @param gw    默认网关
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
 * @brief 初始化 TCP
 * @return *
*/
void init_tcp()
{
    // 初始化 LWIP
	lwip_init();
    // 添加网卡接口至网络列表
	if(!xemac_add(&server_netif, NULL, NULL, NULL, MAC_ETHERNET_ADDRESS, PLATFORM_EMAC_BASEADDR)) 
    {
		xil_printf("Error adding N/W interface\r\n"); return;
	}
    // 设置默认网卡
	netif_set_default(&server_netif);
    // 使能中断
	platform_enable_interrupts();
    // 启用网卡
	netif_set_up(&server_netif);
    // 设置网卡 IP
	assign_default_ip(&(server_netif.ip_addr), &(server_netif.netmask), &(server_netif.gw));
	// 初始化客户端
    tcp_client_init();
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
        XGpio_DiscreteWrite(&gpio_axis_transmit_enable, 1, 0x1);
    }
    else
    {
        XGpio_DiscreteWrite(&gpio_axis_transmit_enable, 1, 0x0);
    }
}


/**
 * @brief DMA 接收中断函数
 * @return *
*/
void dma_rx_handler()
{
    // 确保数据均在 DDR 中
    Xil_DCacheInvalidateRange((u32)FrameCachePtr[FrameCachePtrReceiveIndex], FRAME_CACHE_SIZE);
    // 更新帧缓冲区索引
    FrameCachePtrLastReceiveIndex = FrameCachePtrReceiveIndex;
    FrameCachePtrReceiveIndex = (FrameCachePtrReceiveIndex + 1) % FRAME_CACHE_NUMS;
    if(FrameCachePtrReceiveIndex == FrameCachePtrTransmitIndex)
    {
        FrameCachePtrReceiveIndex = (FrameCachePtrTransmitIndex + 1) % FRAME_CACHE_NUMS;
    }
    // 启动下一次 DMA 传输
    XAxiDma_SimpleTransfer(&AxiDma, (u32)FrameCachePtr[FrameCachePtrReceiveIndex], (u32)(FRAME_CACHE_SIZE), XAXIDMA_DEVICE_TO_DMA);
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
        while(XGpio_DiscreteRead(&gpio_camera_vsync, 1) == 0x0);
        while(XGpio_DiscreteRead(&gpio_camera_vsync, 1) == 0x1);
        frame_count++;
    }
}


/**
 * @brief RGB 转灰度
 * @param r R 通道像素值
 * @param g G 通道像素值
 * @param b B 通道像素值
 * @return 灰度像素值
*/
uint8_t rgb2grayscale(uint8_t r, uint8_t g, uint8_t b)
{
    return (r + g + b) / 3;
}


/**
 * @brief 一维指针转换为二维
 * @param ptr       待转换的一维指针
 * @param width     二维数组行长
 * @param height    二维数组列数
 * @return 转换后的二维数组
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
 * @brief 将 bayer BG_GR 转换为灰度图
 * @param bayer bayer 图像缓冲区
 * @param grayscale 灰度图像缓冲区
 * @param image_width 图像宽度
 * @param image_height 图像高度
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

    // 处理最外围像素
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
            // 非顶点边界像素
            grayscale[row][0] = (row % 2 == 0) ? rgb2grayscale((bayer[row - 1][1] + bayer[row + 1][1]) / 2, (bayer[row - 1][0] + bayer[row + 1][0] + bayer[row][1]) / 3, bayer[row][0]) :
                rgb2grayscale(bayer[row][1], bayer[row][0], (bayer[row - 1][0] + bayer[row + 1][0]) / 2);
            grayscale[row][image_width - 1] = (row % 2 == 0) ? rgb2grayscale(bayer[row - 1][image_width - 1], bayer[row][image_width - 1], bayer[row][image_width - 2]) :
                rgb2grayscale(bayer[row][image_width - 1], (bayer[row][image_width - 2] + bayer[row - 1][image_width - 1] + bayer[row + 1][image_width - 1]) / 3, (bayer[row - 1][image_width - 2] + bayer[row + 1][image_width - 2]) / 2);
        }
    }

    // 处理内部像素点
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
