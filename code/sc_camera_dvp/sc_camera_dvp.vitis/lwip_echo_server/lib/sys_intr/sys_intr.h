#ifndef __SYS_INTR_H__
#define __SYS_INTR_H__

#include "xparameters.h"
#include "xil_exception.h"
#include "xdebug.h"
#include "xscugic.h"


#define INTC_DEVICE_ID          XPAR_SCUGIC_SINGLE_DEVICE_ID

int Init_Intr_System(XScuGic * IntcInstancePtr);
void Setup_Intr_Exception(XScuGic * IntcInstancePtr);

#endif
