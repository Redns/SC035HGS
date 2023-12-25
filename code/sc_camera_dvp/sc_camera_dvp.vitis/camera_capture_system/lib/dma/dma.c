#include "dma.h"

/**
 * @brief 初始化 AXI DMA
 * @param InstancePtr
 * @param DeviceId
 * @return 初始化成功返回 XST_SUCCESS，否则返回 XST_FAILURE
*/
s32 XAxiDma_Init(XAxiDma *InstancePtr, u16 DeviceId)
{
    /* 初始化 AXI DMA 设备 */ 
    XAxiDma_Config *CfgPtr = XAxiDma_LookupConfig(DeviceId);
    if(CfgPtr == NULL)
    {
        xil_printf("[ERROR] No config found for DMA%d\n", DeviceId);
        return XST_FAILURE;
    }
    
    if(XAxiDma_CfgInitialize(InstancePtr, CfgPtr) != XST_SUCCESS)
    {
        xil_printf("[ERROR] Failed to init DMA%d\n", DeviceId);
        return XST_FAILURE;
    }

    if(XAxiDma_HasSg(InstancePtr))
    {
        xil_printf("[ERROR] DMA%d configured as SG mode\n", DeviceId);
        return XST_FAILURE;
    }

    /* 禁用中断 */
    XAxiDma_IntrDisable(InstancePtr, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DEVICE_TO_DMA);
	XAxiDma_IntrDisable(InstancePtr, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DMA_TO_DEVICE);

    return XST_SUCCESS;
}

/**
 * @brief AXI DMA 单次接收
 * @param InstancePtr
 * @param BufferAddr
 * @param Length
 * @return 接收成功返回 XST_SUCCESS，否则返回 XST_FAILURE
*/
s32 XAxiDma_SingleReceive(XAxiDma *InstancePtr, UINTPTR BufferAddr, u32 Length)
{
    if(XAxiDma_SimpleTransfer(InstancePtr, BufferAddr, Length, XAXIDMA_DEVICE_TO_DMA) != XST_SUCCESS)
    {
        xil_printf("[ERROR] Failed to launch dma single receive\n");
        return XST_FAILURE;
    }
    while(XAxiDma_Busy(InstancePtr, XAXIDMA_DEVICE_TO_DMA));
    
    return XST_SUCCESS;
}
