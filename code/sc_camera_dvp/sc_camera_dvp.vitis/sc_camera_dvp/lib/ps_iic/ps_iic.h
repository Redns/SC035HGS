#ifndef __PS_IIC_H__
#define __PS_IIC_H__

#include <malloc.h>
#include "xiicps.h"

XIicPs* PS_IIC_Init(uint16_t DeviceId, uint32_t SclFrqHz);
void PS_IIC_Write_Reg(XIicPs *InstPtr, uint8_t SlaveAddr, uint16_t RegAddr, uint8_t Value);
uint8_t PS_IIC_Read_Reg(XIicPs *InstPtr, uint8_t SlaveAddr, uint16_t RegAddr);

#endif
