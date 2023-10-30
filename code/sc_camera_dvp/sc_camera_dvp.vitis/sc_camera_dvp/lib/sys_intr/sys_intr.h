/*******************************MILIANKE*******************************
*Company:MiLianKe Electronic Technology Co., Ltd.
*WebSite:https://www.milianke.com
*TechWeb:https://www.uisrc.com
*tmall-shop:https://milianke.tmall.com
*jd-shop:https://milianke.jd.com
*taobao-shop1: https://milianke.taobao.com
*Create Date: 2021/10/15
*File Name:sys_intr.h
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


#ifndef SYS_INTR_H_
#define SYS_INTR_H_

#include "xparameters.h"
#include "xil_exception.h"
#include "xdebug.h"
#include "xscugic.h"


#define INTC_DEVICE_ID          XPAR_SCUGIC_SINGLE_DEVICE_ID

int Init_Intr_System(XScuGic * IntcInstancePtr);
void Setup_Intr_Exception(XScuGic * IntcInstancePtr);

#endif /* SYS_INTR_H_ */
