#ifndef __DMA_H__
#define __DMA_H__

#include "xscugic.h"
#include "xaxidma.h"
#include "xil_types.h"

s32 XAxiDma_Init(XAxiDma *InstancePtr, u16 DeviceId);
s32 XAxiDma_Intr_Setup(XScuGic *ScuGicInstancePtr, XAxiDma *AxiDmaInstancePtr, u16 RxIntrId);
s32 XAxiDma_Intr_Enable(XAxiDma *InstancePtr);

#endif