#ifndef __DMA_H__
#define __DMA_H__

#include "xaxidma.h"
#include "xil_types.h"

s32 XAxiDma_Init(XAxiDma *InstancePtr, u16 DeviceId);
s32 XAxiDma_SingleReceive(XAxiDma *InstancePtr, UINTPTR BufferAddr, u32 Length);

#endif