
/*******************************MILIANKE*******************************
*Company : MiLianKe Electronic Technology Co., Ltd.
*WebSite:https://www.milianke.com
*TechWeb:https://www.uisrc.com
*tmall-shop:https://milianke.tmall.com
*jd-shop:https://milianke.jd.com
*taobao-shop1: https://milianke.taobao.com
*Create Date: 2021/10/15
*Module Name:uicfg0135
*File Name:main.c
*Description: 
*axi dma test
*The reference demo provided by Milianke is only used for learning. 
*We cannot ensure that the demo itself is free of bugs, so users 
*should be responsible for the technical problems and consequences
*caused by the use of their own products.
*Copyright: Copyright (c) MiLianKe
*All rights reserved.
*Revision: 1.0
*********************************************************************/

#include "dma_intr.h"
#include "sys_intr.h"

extern volatile int TxDone;
extern volatile int RxDone;
extern volatile int Error;

static XScuGic Intc; //GIC
static  XAxiDma AxiDma;

volatile u32 success;


int Tries = NUMBER_OF_TRANSFERS;
int i;
int Index;
u8 *TxBufferPtr= (u8 *)TX_BUFFER_BASE;
u8 *RxBufferPtr=(u8 *)RX_BUFFER_BASE;
u8 Value;


int axi_dma_test()
{
	int Status;
	TxDone = 0;
	RxDone = 0;
	Error = 0;

	xil_printf("\r\n----DMA Test----\r\n");

	xil_printf("PKT_LEN=%d\r\n",MAX_PKT_LEN);


	//while(1)
	for(i = 0; i < Tries; i ++)
	{
		Value = TEST_START_VALUE + (i & 0xFF);
		for(Index = 0; Index < MAX_PKT_LEN; Index ++) {
				TxBufferPtr[Index] = Value;

				Value = (Value + 1) & 0xFF;
		}

		/* Flush the SrcBuffer before the DMA transfer, in case the Data Cache
		 * is enabled
		 */
		Xil_DCacheFlushRange((u32)TxBufferPtr, MAX_PKT_LEN);

		Status = XAxiDma_SimpleTransfer(&AxiDma,(u32) RxBufferPtr,
					MAX_PKT_LEN, XAXIDMA_DEVICE_TO_DMA);

		if (Status != XST_SUCCESS) {
			return XST_FAILURE;
		}

		Status = XAxiDma_SimpleTransfer(&AxiDma,(u32) TxBufferPtr,
					MAX_PKT_LEN, XAXIDMA_DMA_TO_DEVICE);

		if (Status != XST_SUCCESS) {
			return XST_FAILURE;
		}

		/*
		 * Wait TX done and RX done
		 */
		while (!TxDone || !RxDone) {
				/* NOP */
		}

		success++;
		TxDone = 0;
		RxDone = 0;

		if (Error) {
			xil_printf("Failed test transmit%s done, "
			"receive%s done\r\n", TxDone? "":" not",
							RxDone? "":" not");
			goto Done;
		}
		/*
		 * Test finished, check data
		 */
		Status = DMA_CheckData(MAX_PKT_LEN, (TEST_START_VALUE + (i & 0xFF)));
		if (Status != XST_SUCCESS) {
			xil_printf("Data check failed\r\n");
			goto Done;
		}

	}
	xil_printf("AXI DMA interrupt example test passed\r\n");
	xil_printf("success=%d\r\n",success);
	/* Disable TX and RX Ring interrupts and return success */
	DMA_DisableIntrSystem(&Intc, TX_INTR_ID, RX_INTR_ID);
Done:
	xil_printf("--- Exiting Test --- \r\n");
	return XST_SUCCESS;

}

int init_intr_sys(void)
{
	DMA_Intr_Init(&AxiDma,0);//initial interrupt system
	Init_Intr_System(&Intc); // initial DMA interrupt system
	Setup_Intr_Exception(&Intc);
	DMA_Setup_Intr_System(&Intc,&AxiDma,TX_INTR_ID,RX_INTR_ID);//setup dma interrpt system
	DMA_Intr_Enable(&Intc,&AxiDma);

	return 0;
}

int main(void)
{

	init_intr_sys();
	axi_dma_test();

}


