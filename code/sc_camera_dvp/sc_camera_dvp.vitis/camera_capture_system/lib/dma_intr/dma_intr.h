#ifndef __DMA_INTR_H__
#define __DMA_INTR_H__

#include "xaxidma.h"
#include "xparameters.h"
#include "xil_exception.h"
#include "xdebug.h"
#include "xscugic.h"
#include "sleep.h"
#include "global.h"

// 复位超时计数器
#define RESET_TIMEOUT_COUNTER   10000

s32 XDMA_Init(XAxiDma* InstancePtr, u32 DeviceId);
s32 XDMA_Intr_Init(XScuGic* IntcInstancePtr, XAxiDma* DmaInstancePtr, u16 RxIntrId);
void XDMA_Intr_Enable(XAxiDma* InstancePtr);

#endif
