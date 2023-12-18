#ifndef __DMA_INTR_H__
#define __DMA_INTR_H__

#include "xaxidma.h"
#include "xparameters.h"
#include "xil_exception.h"
#include "xdebug.h"
#include "xscugic.h"

#define DMA_DEV_ID			XPAR_AXIDMA_0_DEVICE_ID
#define RX_INTR_ID			XPAR_FABRIC_AXI_DMA_0_S2MM_INTROUT_INTR

#define FRAME_WIDTH                 640                                     // 帧宽度
#define FRAME_HEIGHT                480                                     // 帧高度
#define FRAME_SIZE					(FRAME_WIDTH * FRAME_HEIGHT)

#define RX_BUFFER_NUMS		10
#define RX_BUFFER_BASE		0x08000000
#define RX_BUFFER_SIZE		0x00080000
#define RX_BUFFER_INVALID	0xFFFFFFFF

// 超时复位时间
#define RESET_TIMEOUT_COUNTER	10000

void DMA_DisableIntrSystem(XScuGic * IntcInstancePtr, u16 RxIntrId);
int  DMA_Setup_Intr_System(XScuGic * IntcInstancePtr,XAxiDma * AxiDmaPtr,  u16 RxIntrId);
int  DMA_Intr_Enable(XScuGic * IntcInstancePtr,XAxiDma *DMAPtr);
int  DMA_Intr_Init(XAxiDma *DMAPtr, u32 DeviceId);

#endif
