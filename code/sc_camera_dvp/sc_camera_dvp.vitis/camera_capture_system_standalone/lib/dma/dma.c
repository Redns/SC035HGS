#include "dma.h"

volatile u8 RxDone;
volatile u8 RxError;

/**
 * @brief 中断处理函数
 * @param Callback
 * @return *
*/
static void DMA_RxIntrHandler(void *Callback)
{
	u32 IrqStatus;
	XAxiDma *AxiDmaInstance = (XAxiDma *)Callback;

	IrqStatus = XAxiDma_IntrGetIrq(AxiDmaInstance, XAXIDMA_DEVICE_TO_DMA);
	XAxiDma_IntrAckIrq(AxiDmaInstance, IrqStatus, XAXIDMA_DEVICE_TO_DMA);

	// 无中断
	if(!(IrqStatus & XAXIDMA_IRQ_ALL_MASK)) 
    {
		return;
	}

	// 中断发生错误
	if(IrqStatus & XAXIDMA_IRQ_ERROR_MASK) 
    {
		RxError = 1;

		XAxiDma_Reset(AxiDmaInstance);

		u32 TimeOut = 10000;
		while(TimeOut) 
        {
			if(XAxiDma_ResetIsDone(AxiDmaInstance)) 
            {
				break;
			}
			TimeOut--;
		}

		return;
	}

	// 接收中断
	if(IrqStatus & XAXIDMA_IRQ_IOC_MASK) 
    {
		RxDone = 1;
	}
}

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

    return XST_SUCCESS;
}

/**
 * @brief 初始化 DMA 中断
 * @param ScuGicInstancePtr
 * @param AxiDmaInstancePtr
 * @param RxIntrId
 * @return 初始化成功返回 XST_SUCCESS，否则返回 XST_FAILURE
*/
s32 XAxiDma_Intr_Setup(XScuGic *ScuGicInstancePtr, XAxiDma *AxiDmaInstancePtr, u16 RxIntrId)
{
    s32 Status;

    // 初始化中断处理函数
    Status = XScuGic_Connect(ScuGicInstancePtr, RxIntrId, (Xil_InterruptHandler)DMA_RxIntrHandler, AxiDmaInstancePtr);
	if(Status != XST_SUCCESS) 
    {
        xil_printf("[ERROR] Failed to init DMA receive handler\n");
		return Status;
	}

    // 设置中断优先级（0xA0）和触发条件（上升沿）
    XScuGic_SetPriorityTriggerType(ScuGicInstancePtr, RxIntrId, 0xA0, 0x3);

	// 使能全局中断
	XScuGic_Enable(ScuGicInstancePtr, RxIntrId);

    return XST_SUCCESS;
}

/**
 * @brief 使能 DMA 中断
 * @param InstancePtr
 * @return 使能成功返回 XST_SUCCESS，否则返回 XST_FAILURE
*/
s32 XAxiDma_Intr_Enable(XAxiDma *InstancePtr)
{
    /* 禁用 DMA 中断 */
    XAxiDma_IntrDisable(InstancePtr, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DEVICE_TO_DMA);
	XAxiDma_IntrDisable(InstancePtr, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DMA_TO_DEVICE);

    /* 使能 DMA 接收中断 */
    XAxiDma_IntrEnable(InstancePtr, XAXIDMA_IRQ_IOC_MASK, XAXIDMA_DEVICE_TO_DMA);

    return XST_SUCCESS;
}