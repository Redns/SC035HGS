#ifndef __INTR_H__
#define __INTR_H__

#include "xparameters.h"
#include "xil_exception.h"
#include "xdebug.h"
#include "xscugic.h"

s32 Intr_Init(XScuGic *InstancePtr);
s32 Intr_Exception_Setup(XScuGic *InstancePtr);

#endif