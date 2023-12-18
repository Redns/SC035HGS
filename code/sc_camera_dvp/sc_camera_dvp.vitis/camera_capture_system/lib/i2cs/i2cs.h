#ifndef __I2CS_H__
#define __I2CS_H__

#include "iic.h"
#include "sleep.h"
#include "xgpio.h"

#define SCCB_MODE_ENABLE            1

#define ACK_TIMEOUT_TICKS           100

#define SDA_IN()                    XGpio_SetDataDirection(&GPIO_I2Cs, 2, 0x1)
#define SDA_OUT()                   XGpio_SetDataDirection(&GPIO_I2Cs, 2, 0x0)

#define SCL_WRITE_H()               XGpio_DiscreteWrite(&GPIO_I2Cs, 1, 0x1)
#define SCL_WRITE_L()               XGpio_DiscreteWrite(&GPIO_I2Cs, 1, 0x0)
#define SDA_WRITE_H()               XGpio_DiscreteWrite(&GPIO_I2Cs, 2, 0x1)
#define SDA_WRITE_L()               XGpio_DiscreteWrite(&GPIO_I2Cs, 2, 0x0)

#define SDA_READ()                  XGpio_DiscreteRead(&GPIO_I2Cs, 2)

void I2Cs_Init(uint16_t DeviceId);
s32 I2Cs_CheckDev(uint8_t SlaveAddr);
s32 I2Cs_WriteReg(uint8_t SlaveAddr, uint16_t RegAddr, uint8_t Value);
uint8_t I2Cs_ReadReg(uint8_t SlaveAddr, uint16_t RegAddr);

#endif
