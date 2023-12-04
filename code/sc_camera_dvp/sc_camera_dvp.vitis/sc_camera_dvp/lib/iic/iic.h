#ifndef __IIC_H__
#define __IIC_H__

#include "stdint.h"

#define REG_DELAY_ADDR  0x0000
#define REG_NULL_ADDR   0xFFFF

#define IIC_FRQ_HZ     100000

typedef struct RegValuePair
{
    uint16_t Addr;
    uint8_t Value;
}RegValuePair;

#endif
