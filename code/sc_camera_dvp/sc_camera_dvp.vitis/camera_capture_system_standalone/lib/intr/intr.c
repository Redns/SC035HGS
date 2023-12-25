#include "intr.h"

s32 Intr_Exception_Setup(XScuGic *InstancePtr)
{
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, InstancePtr);
	Xil_ExceptionEnable();

	return XST_SUCCESS;
}

/**
 * @brief 初始化全局中断
 * @param InstancePtr
 * @return 初始化成功返回 XST_SUCCESS，否则返回 XST_FAILURE
*/
s32 Intr_Init(XScuGic *InstancePtr)
{
	s32 Status;

	XScuGic_Config *IntcConfig = XScuGic_LookupConfig(XPAR_SCUGIC_SINGLE_DEVICE_ID);
	if(IntcConfig == NULL) 
    {
        xil_printf("[ERROR] No config found for ScuGic\n");
		return XST_FAILURE;
	}

	Status = XScuGic_CfgInitialize(InstancePtr, IntcConfig, IntcConfig->CpuBaseAddress);
	if(Status != XST_SUCCESS) 
    {
        xil_printf("[ERROR] Failed to init ScuGic\n");
		return Status;
	}

	return XST_SUCCESS;
}