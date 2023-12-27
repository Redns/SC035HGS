#ifndef __DMA_H__
#define __DMA_H__

#include "xscugic.h"
#include "xaxidma.h"
#include "xil_types.h"

/* 帧属性 */
#define FRAME_WIDTH                 640                                     // 帧宽度
#define FRAME_HEIGHT                480                                     // 帧高度
#define FRAME_SIZE					(FRAME_WIDTH * FRAME_HEIGHT)            // 帧尺寸（字节）
#define FRAME_FRONT_SIZE            26
#define FRAME_BUFFER_BASE           0x10300000                              // 基地址
#define FRAME_BUFFER_NUMS			3	             

s32 XAxiDma_Init(XAxiDma *InstancePtr, u16 DeviceId);
s32 XAxiDma_Intr_Setup(XScuGic *ScuGicInstancePtr, XAxiDma *AxiDmaInstancePtr, u16 RxIntrId);
s32 XAxiDma_Intr_Enable(XAxiDma *InstancePtr);

#endif