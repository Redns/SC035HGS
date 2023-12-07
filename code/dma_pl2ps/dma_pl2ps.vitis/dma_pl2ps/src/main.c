/* 缓冲区相关设置 */
#include "xil_types.h"
#include "xscugic.h"
#include "xaxidma.h"
#include "xgpio.h"
#include "dma_intr.h"
#define FRAME_WIDTH                 640                                     // 帧宽度
#define FRAME_HEIGHT                480                                     // 帧高度
#define FRAME_CACHE_SIZE            FRAME_WIDTH * FRAME_HEIGHT              // 帧缓冲区大小（单位：字节）
#define FRAME_CACHE_NUMS            3                                       // 帧缓冲区数量

/* 相关外设 ID */
#define DMA                         XPAR_AXI_DMA_0_DEVICE_ID
#define GPIO_AXISBUFW_CTRL          XPAR_AXI_GPIO_AXISBUFW_CTRL_DEVICE_ID
#define GPIO_AXISBUFW_DATA          XPAR_AXI_GPIO_AXISBUFW_DATA_DEVICE_ID         

/* 数据缓冲区 */
u32 FrameCachePtrReceiveIndex;                                              // 接收缓存索引
u32 FrameCachePtrTransmitIndex;                                             // 发送缓存索引
u32 FrameCachePtrLastReceiveIndex;                                          // 上一个接收缓存索引
u32 FrameCachePtr[FRAME_CACHE_NUMS + 1];                                    // 帧缓冲区（RAW, RAW...、RAW, RGB）

/* 外设句柄 */
XScuGic Intc;
XAxiDma AxiDma;
XGpio GpioAxisbufwCtrl;
XGpio GpioAxisbufwData;

void dma_rx_handler();

int main(void)
{
    // FS
    XGpio_Initialize(&GpioAxisbufwCtrl, GPIO_AXISBUFW_CTRL);
    XGpio_SetDataDirection(&GpioAxisbufwCtrl, 1, 0x0);
    XGpio_DiscreteWrite(&GpioAxisbufwCtrl, 1, 0x1);
    // Wren
    XGpio_Initialize(&GpioAxisbufwCtrl, GPIO_AXISBUFW_CTRL);
    XGpio_SetDataDirection(&GpioAxisbufwCtrl, 2, 0x0);
    XGpio_DiscreteWrite(&GpioAxisbufwCtrl, 2, 0x1);
    // Data
    XGpio_Initialize(&GpioAxisbufwData, GPIO_AXISBUFW_DATA);
    XGpio_SetDataDirection(&GpioAxisbufwCtrl, 1, 0x0);
    XGpio_DiscreteWrite(&GpioAxisbufwCtrl, 1, 0x77ABCDEF);

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

    // 启动首次 DMA 传输
    XAxiDma_SimpleTransfer(&AxiDma, (u32)FrameCachePtr[FrameCachePtrReceiveIndex], (u32)(FRAME_CACHE_SIZE), XAXIDMA_DEVICE_TO_DMA);

	while(1)
	{
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
	
    return 0;
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