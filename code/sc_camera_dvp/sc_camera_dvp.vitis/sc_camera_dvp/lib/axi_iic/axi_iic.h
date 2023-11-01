#ifndef __AXI_IIC_H__
#define __AXI_IIC_H__

#include "xiic.h"
#include <malloc.h>

/* 特殊寄存器地址 */ 
#define REG_NULL_ADDR                           0xffff      // 空地址（标志寄存器列表结尾）
#define REG_DELAY_ADDR                          0x0000      // 延时地址（标志此处需要延时若干毫秒）

// 寄存器键值对
typedef struct RegValuePair {
    uint16_t Addr;      // 寄存器地址
    uint8_t Value;      // 寄存器值
} RegValuePair;

XIic* AXI_IIC_Init(uint16_t DeviceId);
void AXI_IIC_Write_Reg(XIic *InstPtr, uint8_t SlaveAddr, uint16_t RegAddr, uint8_t Value);
uint8_t AXI_IIC_Read_Reg(XIic *InstPtr, uint8_t SlaveAddr, uint16_t RegAddr);

#endif