#ifndef __DMA_INTR_H__
#define __DMA_INTR_H__

#include "xaxidma.h"
#include "xparameters.h"
#include "xil_exception.h"
#include "xdebug.h"
#include "xscugic.h"
#include "sleep.h"
#include "global.h"

// ��ʱ��λʱ��
#define RESET_TIMEOUT_COUNTER	10000

void DMA_DisableIntrSystem(XScuGic * IntcInstancePtr, u16 RxIntrId);
int  DMA_Setup_Intr_System(XScuGic * IntcInstancePtr,XAxiDma * AxiDmaPtr,  u16 RxIntrId);
int  DMA_Intr_Enable(XScuGic * IntcInstancePtr,XAxiDma *DMAPtr);
int  DMA_Intr_Init(XAxiDma *DMAPtr, u32 DeviceId);

#endif
