#include "dma_intr.h"

volatile XAxiDma AxiDma;

volatile u32 RxBufferReceiveCount;
volatile u32 RxBufferPtrReceiveIndex;
volatile u32 RxBufferPtrTransmitIndex;
volatile u32 RxBufferPtrLastReceiveIndex;
volatile u32 RxBufferPtr[RX_BUFFER_NUMS];
volatile u32 RxBufferFrameStartAddrPtr[RX_BUFFER_NUMS];

/**
 * @brief
 * */
void DMA_DisableIntrSystem(XScuGic * IntcInstancePtr, u16 RxIntrId)
{
	#ifdef XPAR_INTC_0_DEVICE_ID
		XIntc_Disconnect(IntcInstancePtr, TxIntrId);
		XIntc_Disconnect(IntcInstancePtr, RxIntrId);
	#else
		XScuGic_Disconnect(IntcInstancePtr, RxIntrId);
	#endif
}


/*****************************************************************************/
/*
*
* This is the DMA RX interrupt handler function
* It gets the interrupt status from the hardware, acknowledges it, and if any
* error happens, it resets the hardware. Otherwise, if a completion interrupt
* is present, then it sets the RxDone flag.
*
* @param	Callback is a pointer to RX channel of the DMA engine.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
static void DMA_RxIntrHandler(void *Callback)
{
	u32 IrqStatus;
	int TimeOut;
	XAxiDma *AxiDmaInst = (XAxiDma *)Callback;

	/* Read pending interrupts */
	IrqStatus = XAxiDma_IntrGetIrq(AxiDmaInst, XAXIDMA_DEVICE_TO_DMA);

	/* Acknowledge pending interrupts */
	XAxiDma_IntrAckIrq(AxiDmaInst, IrqStatus, XAXIDMA_DEVICE_TO_DMA);

	/*
	 * If no interrupt is asserted, we do not do anything
	 */
	if (!(IrqStatus & XAXIDMA_IRQ_ALL_MASK)) {
		return;
	}

	/*
	 * If error interrupt is asserted, raise error flag, reset the
	 * hardware to recover from the error, and return with no further
	 * processing.
	 */
	if ((IrqStatus & XAXIDMA_IRQ_ERROR_MASK)) {

		// TODO err_handler();

		/* Reset could fail and hang
		 * NEED a way to handle this or do not call it??
		 */
		XAxiDma_Reset(AxiDmaInst);

		TimeOut = RESET_TIMEOUT_COUNTER;

		while (TimeOut) {
			if(XAxiDma_ResetIsDone(AxiDmaInst)) {
				break;
			}
			TimeOut -= 1;
		}

		return;
	}

	/*
	 * If completion interrupt is asserted, then set RxDone flag
	 */
	if ((IrqStatus & XAXIDMA_IRQ_IOC_MASK))
	{
//		// 确保数据均在 DDR 中
//		Xil_DCacheInvalidateRange(RxBufferPtr[RxBufferPtrReceiveIndex], RX_BUFFER_SIZE);
//
//		// 设置帧起始地址
//		RxBufferReceiveCount++;
//		u32 surplusFrameSize = (RX_BUFFER_SIZE * RxBufferReceiveCount) % FRAME_SIZE;
//		if(surplusFrameSize <= RX_BUFFER_SIZE - FRAME_SIZE)
//		{
//			RxBufferFrameStartAddrPtr[RxBufferPtrReceiveIndex] = RX_BUFFER_SIZE - (surplusFrameSize + FRAME_SIZE);
//		}
//		else
//		{
//			RxBufferFrameStartAddrPtr[RxBufferPtrReceiveIndex] = RX_BUFFER_INVALID;
//		}
//
//		// 更新帧缓冲区索引
//		RxBufferPtrLastReceiveIndex = RxBufferPtrReceiveIndex;
//		RxBufferPtrReceiveIndex = (RxBufferPtrReceiveIndex + 1) % RX_BUFFER_NUMS;
//		if(RxBufferPtrReceiveIndex == RxBufferPtrTransmitIndex)
//		{
//			RxBufferPtrReceiveIndex = (RxBufferPtrTransmitIndex + 1) % RX_BUFFER_NUMS;
//		}
//
//		// 启动下一次 DMA 传输
//		XAxiDma_SimpleTransfer(&AxiDma, RxBufferPtr[RxBufferPtrReceiveIndex], RX_BUFFER_SIZE, XAXIDMA_DEVICE_TO_DMA);
//		usleep(10 * 1000);
	}
}

/*****************************************************************************/
/*
*
* This function setups the interrupt system so interrupts can occur for the
* DMA, it assumes INTC component exists in the hardware system.
*
* @param	IntcInstancePtr is a pointer to the instance of the INTC.
* @param	AxiDmaPtr is a pointer to the instance of the DMA engine
* @param	TxIntrId is the TX channel Interrupt ID.
* @param	RxIntrId is the RX channel Interrupt ID.
*
* @return
*		- XST_SUCCESS if successful,
*		- XST_FAILURE.if not succesful
*
* @note		None.
*
******************************************************************************/
int DMA_Setup_Intr_System(XScuGic * IntcInstancePtr,XAxiDma * AxiDmaPtr, u16 RxIntrId)
{
	int Status;

	XScuGic_SetPriorityTriggerType(IntcInstancePtr, RxIntrId, 0xA0, 0x3);
	/*
	 * Connect the device driver handler that will be called when an
	 * interrupt for the device occurs, the handler defined above performs
	 * the specific interrupt processing for the device.
	 */
	Status = XScuGic_Connect(IntcInstancePtr, RxIntrId,
				(Xil_InterruptHandler)DMA_RxIntrHandler,
				AxiDmaPtr);
	if (Status != XST_SUCCESS) {
		return Status;
	}

	XScuGic_Enable(IntcInstancePtr, RxIntrId);
	return XST_SUCCESS;
}



int DMA_Intr_Enable(XScuGic * IntcInstancePtr,XAxiDma *DMAPtr)
{

	/* Disable all interrupts before setup */
	XAxiDma_IntrDisable(DMAPtr, XAXIDMA_IRQ_ALL_MASK,
				XAXIDMA_DEVICE_TO_DMA);

	/* Enable all interrupts */
	XAxiDma_IntrEnable(DMAPtr, XAXIDMA_IRQ_ALL_MASK,
							XAXIDMA_DEVICE_TO_DMA);
	return XST_SUCCESS;

}


int DMA_Intr_Init(XAxiDma *DMAPtr, u32 DeviceId)
{
	int Status;
	XAxiDma_Config *Config=NULL;

	Config = XAxiDma_LookupConfig(DeviceId);
	if (!Config) {
		xil_printf("No config found for %d\r\n", DeviceId);
		return XST_FAILURE;
	}

	/* Initialize DMA engine */
	Status = XAxiDma_CfgInitialize(DMAPtr, Config);

	if (Status != XST_SUCCESS) {
		xil_printf("Initialization failed %d\r\n", Status);
		return XST_FAILURE;
	}

	if(XAxiDma_HasSg(DMAPtr)){
		xil_printf("Device configured as SG mode \r\n");
		return XST_FAILURE;
	}
	return XST_SUCCESS;

}
