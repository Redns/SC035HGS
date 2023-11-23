#ifndef __PS_IIC_H__
#define __PS_IIC_H__

#include <malloc.h>
#include "sleep.h"
#include "xiicps.h"

#define REG_DELAY_ADDR  0x0000
#define REG_NULL_ADDR   0xFFFF

#define IIC_FRQ_HZ      400000

typedef struct RegValuePair
{
    uint16_t Addr;
    uint8_t Value;
}RegValuePair;

s32 PS_IIC_Init(XIicPs *InstPtr, uint16_t DeviceId, uint32_t SclFrqHz);
s32 PS_IIC_Write_Reg(XIicPs *InstPtr, uint8_t SlaveAddr, uint16_t RegAddr, uint8_t Value);
uint8_t PS_IIC_Read_Reg(XIicPs *InstPtr, uint8_t SlaveAddr, uint16_t RegAddr);

#endif
