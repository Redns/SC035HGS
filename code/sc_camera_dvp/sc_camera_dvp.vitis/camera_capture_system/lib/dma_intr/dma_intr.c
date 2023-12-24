#include "dma_intr.h"

XAxiDma AxiDma;

/* DMA */
extern s32 RxCount;
extern s32 RxIndex;
extern s32 TxIndex;
extern s32 RxLastIndex;
extern u32 RxBufferPtr[RX_BUFFER_NUMS];
extern u32 RxBufferFrameAddr[RX_BUFFER_NUMS];
extern u32 EthTxBufferPtr;


/**
 * @brief DMA 接收中断处理函数
 * @param Callback 
 * @return *
*/
static void DMA_Rx_IntcHandler(void* Callback)
{
	XAxiDma *AxiDmaInst = (XAxiDma *)Callback;

	// 检查中断是否触发
	u32 IrqStatus = XAxiDma_IntrGetIrq(AxiDmaInst, XAXIDMA_DEVICE_TO_DMA);
	XAxiDma_IntrAckIrq(AxiDmaInst, IrqStatus, XAXIDMA_DEVICE_TO_DMA);
	if(!(IrqStatus & XAXIDMA_IRQ_ALL_MASK)) 
	{
		return;
	}

	// 错误中断是否触发
	if(IrqStatus & XAXIDMA_IRQ_ERROR_MASK) 
	{
		// 复位 DMA
		XAxiDma_Reset(AxiDmaInst);

		// 等待复位完成
		u32 Timeout = RESET_TIMEOUT_COUNTER;
		while((Timeout > 0) && !XAxiDma_ResetIsDone(AxiDmaInst)) 
		{
			Timeout--;
		}

		return;
	}

	// 接收完成中断触发
	if(IrqStatus & XAXIDMA_IRQ_IOC_MASK)
	{
		RxCount++;

		// 检查当前缓冲区是否包含完整帧图像
		u32 surplusFrameSize = (RX_BUFFER_SIZE * RxCount) % FRAME_SIZE;
		if(surplusFrameSize <= RX_BUFFER_SIZE - FRAME_SIZE)
		{
			RxBufferFrameAddr[RxIndex] = RX_BUFFER_SIZE - (surplusFrameSize + FRAME_SIZE);
		}
		else
		{
			RxBufferFrameAddr[RxIndex] = RX_BUFFER_INVALID_ADDR;
		}
		
		// 更新缓冲区索引
		RxLastIndex = RxIndex;
		do {
			RxIndex = (RxIndex + 1) % RX_BUFFER_NUMS;
		} while(RxIndex == TxIndex);

		// 启动下一次接收
		XAxiDma_SimpleTransfer(&AxiDma, (u32)RxBufferPtr[RxIndex], RX_BUFFER_SIZE, XAXIDMA_DEVICE_TO_DMA);
	}
}


/**
 * @brief 初始化 DMA 中断
 * @param IntcInstancePtr 中断管理单元句柄
 * @param DmaInstancePtr DMA 句柄
 * @param RxIntrId  DMA 接收中断 ID
 * @return 初始化成功返回 XST_SUCCESS，否则返回 XST_FAILURE
*/
s32 XDMA_Intr_Init(XScuGic* IntcInstancePtr, XAxiDma* DmaInstancePtr, u16 RxIntrId)
{
	s32 Status;

	// 设置中断优先级为 0xA0，上升沿触发
	XScuGic_SetPriorityTriggerType(IntcInstancePtr, RxIntrId, 0xA0, 0x3);

	// 设置中断处理函数
	Status = XScuGic_Connect(IntcInstancePtr, RxIntrId, (Xil_InterruptHandler)DMA_Rx_IntcHandler, DmaInstancePtr);
	if(Status != XST_SUCCESS) 
	{
		return Status;
	}
	XScuGic_Enable(IntcInstancePtr, RxIntrId);

	return XST_SUCCESS;
}


/**
 * @brief 使能 DMA 中断
 * @param InstancePtr
 * @return *
*/
void XDMA_Intr_Enable(XAxiDma* InstancePtr)
{
	XAxiDma_IntrDisable(InstancePtr, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DEVICE_TO_DMA);
	XAxiDma_IntrEnable(InstancePtr, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DEVICE_TO_DMA);
}


/**
 * @brief 初始化 DMA
 * @param InstancePtr
 * @param DeviceId	
 * @return 初始化成功返回 XST_SUCCESS，否则返回 XST_FAILURE
*/
s32 XDMA_Init(XAxiDma* InstancePtr, u32 DeviceId)
{
	s32 Status;

	// 查找 DMA 配置信息
	XAxiDma_Config* Config = XAxiDma_LookupConfig(DeviceId);
	if(Config == NULL) 
	{
		xil_printf("[ERROR] No config found for DMA %d\n", DeviceId);
		return XST_FAILURE;
	}

	// 初始化 DMA 
	Status = XAxiDma_CfgInitialize(InstancePtr, Config);
	if(Status != XST_SUCCESS) 
	{
		xil_printf("[ERROR] Failed to init DMA %d, status code is %d\n", DeviceId, Status);
		return XST_FAILURE;
	}

	// 检查 DMA 运行模式
	if(XAxiDma_HasSg(InstancePtr))
	{
		xil_printf("[ERROR] Failed to init DMA %d, device configured as SG mode\n", DeviceId);
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}