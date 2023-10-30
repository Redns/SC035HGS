/*******************************MILIANKE*******************************
*Company : MiLianKe Electronic Technology Co., Ltd.
*WebSite:https://www.milianke.com
*TechWeb:https://www.uisrc.com
*tmall-shop:https://milianke.tmall.com
*jd-shop:https://milianke.jd.com
*taobao-shop1: https://milianke.taobao.com
*Create Date: 2021/10/15
*File Name:dma_intr.h
*Description:
*axi dma test
*The reference demo provided by Milianke is only used for learning.
*We cannot ensure that the demo itself is free of bugs, so users
*should be responsible for the technical problems and consequences
*caused by the use of their own products.
*Copyright: Copyright (c) MiLianKe
*All rights reserved.
*Revision: 1.0
*********************************************************************/

#ifndef DMA_INTR_H
#define DMA_INTR_H
#include "xaxidma.h"
#include "xparameters.h"
#include "xil_exception.h"
#include "xdebug.h"
#include "xscugic.h"

/************************** Constant Definitions *****************************/
/*
 * Device hardware build related constants.
 */
#define DMA_DEV_ID			XPAR_AXIDMA_0_DEVICE_ID
#define RX_INTR_ID			XPAR_FABRIC_AXI_DMA_0_S2MM_INTROUT_INTR
//#define TX_INTR_ID		XPAR_FABRIC_AXI_DMA_0_MM2S_INTROUT_INTR

#define RX_BUFFER_BASE		0x08000000


/* Timeout loop counter for reset
 */
#define RESET_TIMEOUT_COUNTER	10000

void DMA_DisableIntrSystem(XScuGic * IntcInstancePtr, u16 RxIntrId);
int  DMA_Setup_Intr_System(XScuGic * IntcInstancePtr,XAxiDma * AxiDmaPtr,  u16 RxIntrId);
int  DMA_Intr_Enable(XScuGic * IntcInstancePtr,XAxiDma *DMAPtr);
int  DMA_Intr_Init(XAxiDma *DMAPtr,u32 DeviceId);

#endif
