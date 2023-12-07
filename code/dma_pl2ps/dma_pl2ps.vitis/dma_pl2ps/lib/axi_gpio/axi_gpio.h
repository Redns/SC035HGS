#ifndef __AXI_GPIO_H__
#define __AXI_GPIO_H__

#include "gpio.h"
#include "xgpio.h"
#include "xil_types.h"

typedef struct
{
    GpioDirection Direction;
    u32 Value;
} AxiGpioChannel;

typedef struct 
{
    u16 DeviceId;
    XGpio* XGpioInstancePtr;
    AxiGpioChannel Channel1;
    AxiGpioChannel Channel2;
} AxiGpio;

#endif