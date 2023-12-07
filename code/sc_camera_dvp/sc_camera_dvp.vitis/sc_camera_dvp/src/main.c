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
#include "open_image.h"
#include "vofa.h"

#define DMA_CHECK_ENABLE            0
#define TCP_TRANSMIT_ENABLE         0

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

/* LED 状态*/
#define LED_ON                      1
#define LED_OFF                     0

/* 相关外设 ID */
#define IICS                        XPAR_I2CS_DEVICE_ID
#define IIC_PS                      XPAR_PS7_I2C_0_DEVICE_ID
#define GPIO_LED                    XPAR_LED_DEVICE_ID
#define GPIO_DMA_CHECK              XPAR_AXI_GPIO_DMA_CHECK_DEVICE_ID       // DMA 测试控制
#define GPIO_CAMERA_PWDN            XPAR_CAMERA_PWDN_DEVICE_ID              // SC035HGS 休眠控制（正常工作需设置为低电平）
#define GPIO_CAMERA_VSYNC           XPAR_CAMERA_VSYNC_DEVICE_ID             // SC035HGS DVP 输出场同步信号
#define GPIO_CAMERA_XCLK_LOCKED     XPAR_XCLK_LOCKED_DEVICE_ID              // SC035HGS 像素时钟输入锁定
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
u32 FrameCachePtr[FRAME_CACHE_NUMS + 1];                                    // 帧缓冲区（RAW, RAW...、RAW, RGB）

uint8_t EthTransmitCache[FRAME_CACHE_SIZE + 1];                             // TCP 发送缓冲区

/* 外设句柄 */
XScuGic Intc;
XAxiDma AxiDma;
camera_t camera;
XGpio gpio_led;
XGpio gpio_dma_check;
XGpio gpio_camera_pwdn;
XGpio gpio_camera_xclk_locked;
XGpio gpio_camera_vsync;
XGpio gpio_eth_phy_rstn;
XGpio gpio_axis_transmit_enable;

void init_led();
void set_led(uint8_t on);
void init_dma_check();
void set_dma_check(uint8_t on);
void init_system();
void init_camera();
void init_axis_transmit();
void init_eth_phy();
void init_tcp();
void set_axis_transmit(int start);
void dma_rx_handler();
void wait_camera_ready();

int main(void)
{
    init_system();

    for(uint8_t i = 0; i < 5; i++)
    {
        set_led(LED_ON);
        usleep(200 * 1000);
        set_led(LED_OFF);
        usleep(200 * 1000);
    }
    set_led(LED_ON);

	while(1)
	{
        #if TCP_TRANSMIT_ENABLE
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
        #endif

        if(FrameCachePtrTransmitIndex != FrameCachePtrLastReceiveIndex)
        {
            xil_printf("[INFO] Sending %d frames...\n", FrameCachePtrTransmitIndex);
            // // 将 Bayer 转换为灰度图像
            // FrameCachePtrTransmitIndex = FrameCachePtrLastReceiveIndex;
            // bayer2grayscale(ptr_converter((uint8_t*)FrameCachePtr[FrameCachePtrTransmitIndex], FRAME_WIDTH, FRAME_HEIGHT),
            //     ptr_converter((uint8_t*)FrameCachePtr[FRAME_CACHE_NUMS], FRAME_WIDTH, FRAME_HEIGHT), FRAME_WIDTH, FRAME_HEIGHT);
            
            // // 发送前导帧
            // char *image_front_frame = generate_image_front_frame(0, FRAME_CACHE_SIZE, FRAME_WIDTH, FRAME_HEIGHT, Format_Grayscalec8);
            // tcp_client_send(image_front_frame, strlen(image_front_frame));
            
            // // 图片数据发送
            // memset(EthTransmitCache, '\n', sizeof(EthTransmitCache));
            // memcpy(EthTransmitCache, (uint8_t*)FrameCachePtr[FRAME_CACHE_NUMS], sizeof(uint8_t) * FRAME_CACHE_SIZE);
            // tcp_client_send(EthTransmitCache, sizeof(EthTransmitCache));
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
    // 初始化 LED
    init_led();
    // 初始化 AXIS 数据转换模块
    init_axis_transmit();
    // 初始化摄像头
    init_camera();

    /* 网口传输 */
    #if TCP_TRANSMIT_ENABLE
        // 初始化网卡
        init_eth_phy();
        // 初始化 TCP 连接
        init_tcp();
    #endif

    /* DMA */ 
    DMA_Intr_Init(&AxiDma, 0);
	Init_Intr_System(&Intc);
	Setup_Intr_Exception(&Intc);
	DMA_Setup_Intr_System(&Intc, &AxiDma, RX_INTR_ID);
    DMA_Handler_Init(NULL, dma_rx_handler, NULL);
	DMA_Intr_Enable(&Intc, &AxiDma);

    /* 帧缓冲区 */
    FrameCachePtrReceiveIndex  = 0;
    FrameCachePtrLastReceiveIndex = 0;
    FrameCachePtrTransmitIndex = 0;
    for(int i = 0; i < FRAME_CACHE_NUMS + 1; i++)
    {
        FrameCachePtr[i] = RX_BUFFER_BASE + FRAME_CACHE_NUMS * i;
    }

    /* DMA 测试*/
    #if DMA_CHECK_ENABLE
        init_dma_check();
        set_dma_check(1);
    #else
        // 等待摄像头输出稳定
        wait_camera_ready();
    #endif

    // 使能 AXIS 模块
    set_axis_transmit(AXIS_TRANSMIT_ENABLE);

    // 启动首次 DMA 传输
    XAxiDma_SimpleTransfer(&AxiDma, (u32)FrameCachePtr[FrameCachePtrReceiveIndex], (u32)(FRAME_CACHE_SIZE), XAXIDMA_DEVICE_TO_DMA);
}


/**
 * @brief 初始化 LED
 * @return *
*/
void init_led()
{
    XGpio_Initialize(&gpio_led, GPIO_LED);
    XGpio_SetDataDirection(&gpio_led, 1, 0x0);
    set_led(LED_OFF);
}


/**
 * @brief DMA 测试初始化函数
 * @return *
*/
void init_dma_check()
{
    XGpio_Initialize(&gpio_dma_check, GPIO_DMA_CHECK);
    XGpio_SetDataDirection(&gpio_dma_check, 1, 0x0);
}


/**
 * @brief DMA 测试控制函数
 * @param on 为 true 启动测试，否则关闭
 * @return *
*/
void set_dma_check(uint8_t on)
{
    if(on)
    {
        XGpio_DiscreteWrite(&gpio_dma_check, 1, 0x1);
    }    
    else
    {
        XGpio_DiscreteWrite(&gpio_dma_check, 1, 0x0);
    }
}


/**
 * @brief 设置 LED 状态
 * @param on 建议使用 LED_ON/LED_OFF 控制
 * @return *
*/
void set_led(uint8_t on)
{
	if(on)
	{
        XGpio_DiscreteWrite(&gpio_led, 1, 0x1);
	}
    else
    {
        XGpio_DiscreteWrite(&gpio_led, 1, 0x0);
    }
}


/**
 * @brief 初始化摄像头
 * @return *
*/
void init_camera()
{
    xil_printf("[INFO] Start to init camera...\n");

    // 初始化休眠输出引脚
    XGpio_Initialize(&gpio_camera_pwdn, GPIO_CAMERA_PWDN);
    XGpio_SetDataDirection(&gpio_camera_pwdn, 1, 0x0);
    XGpio_DiscreteWrite(&gpio_camera_pwdn, 1, 0x0);
    // 初始化时钟输入锁定引脚
    XGpio_Initialize(&gpio_camera_xclk_locked, GPIO_CAMERA_XCLK_LOCKED);
	XGpio_SetDataDirection(&gpio_camera_xclk_locked, 1, 0x1);
    // 等待摄像头输入时钟锁定
    while(XGpio_DiscreteRead(&gpio_camera_xclk_locked, 1) == 0);
    // 初始化场信号输入引脚
    XGpio_Initialize(&gpio_camera_vsync, GPIO_CAMERA_VSYNC);
	XGpio_SetDataDirection(&gpio_camera_vsync, 1, 0x1);
    // 拉高 PWDN 引脚启用摄像头
    XGpio_DiscreteWrite(&gpio_camera_pwdn, 1, 0x1);
    // 拉高 PWDN 后至少等待 4ms 才能访问寄存器
    usleep(20 * 1000);
    
    // 初始化摄像头寄存器
    #if IIC_PS_ENABLE
        camera.i2c_device_id = IIC_PS;
    #else
        camera.i2c_device_id = IICS;
    #endif
    sc035hgs_init(&camera);
    
    xil_printf("[SUCCESS] Init camera done\n");
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
    xil_printf("[INFO] DMA receive interrupt\n");
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
        xil_printf("[INFO] Camera output %u frame\n", frame_count);
        while(XGpio_DiscreteRead(&gpio_camera_vsync, 1) == 0x0);
        while(XGpio_DiscreteRead(&gpio_camera_vsync, 1) == 0x1);
        frame_count++;
    }
}