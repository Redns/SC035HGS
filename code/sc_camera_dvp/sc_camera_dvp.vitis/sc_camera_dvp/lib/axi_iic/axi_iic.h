#ifndef __AXI_IIC_H__
#define __AXI_IIC_H__

#include "xiic.h"

// 寄存器键值对
typedef struct RegValuePair {
    uint16_t Addr;      // 寄存器地址
    uint8_t Value;      // 寄存器值
} RegValuePair;

void AXI_IIC_Init(XIic *InstPtr, uint16_t DeviceId);
void AXI_IIC_Write_Reg(XIic *InstPtr, uint8_t SlaveAddr, uint16_t RegAddr, uint8_t Value);
uint8_t AXI_IIC_Read_Reg(XIic *InstPtr, uint8_t SlaveAddr, uint16_t RegAddr);

#endif