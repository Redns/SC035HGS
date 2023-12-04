#include "iic_software.h"

XGpio GPIO_I2Cs;

/**  
  * @brief I2C 开始信号
  * @return *
  */
static void I2Cs_Start()
{
    Delay();
	SDA_OUT();
    SDA_WRITE_H();
    SCL_WRITE_H();
    Delay();
    SDA_WRITE_L();
    Delay();
    SCL_WRITE_L();
    Delay();
}


/**
 * @brief I2C 结束信号
 * @return *
*/
static void I2Cs_Stop()
{
    Delay();
	SDA_OUT();
	SDA_WRITE_L();
    Delay();
	SCL_WRITE_H();
	Delay();
	SDA_WRITE_H();
}


/**
 * @brief 发送单个字节
 * @param byte 待发送的字节
 * @return *
*/
static void I2Cs_WriteByte(uint8_t byte)
{
    Delay();
    SDA_OUT();
	for(uint8_t i = 0; i < 8; i++)
	{
		if(byte & 0x80)
		{
			SDA_WRITE_H();
		}
		else 
		{
			SDA_WRITE_L();
		}
		Delay();
		SCL_WRITE_H();
		Delay();
		SCL_WRITE_L();
		if(i == 7)
        {
            SDA_WRITE_H();
        }
		byte <<= 1;
		Delay();
	}
}


/**
 * @brief 读单个字节
 * @return 读取的字节数据
*/
static uint8_t I2Cs_ReadByte()
{
	//初始SCL为0，SCL拉高时读值
	uint8_t byte=0;
	
    Delay();
    SDA_IN();
	for(uint8_t i = 0; i < 8; i++)
	{
		byte <<= 1;
		SCL_WRITE_H();
		Delay();
		if(SDA_READ())
		{
			byte++;
		}
        Delay();
		SCL_WRITE_L();
		Delay();
	}
	return byte;
}


/**
 * @brief 等待 ACK 信号
 * @return 正确应答返回 XST_SUCCESS，否则返回 XST_FAILURE
*/
static s32 I2Cs_WaitAck(uint32_t timeout_ticks)
{
	s32 status;
	
    Delay();
	SCL_WRITE_H();
	Delay();
    SDA_IN();
    while(SDA_READ() && (timeout_ticks > 0))
	{
        Delay();
        timeout_ticks--;
    }
	SCL_WRITE_L();
	Delay();

	return (timeout_ticks > 0) ? XST_SUCCESS : XST_FAILURE;
}


/**
 * @brief 产生 ACK 信号
 * @return *
*/
static void I2Cs_Ack()
{
    Delay();
    SDA_OUT();
	SDA_WRITE_L();
	Delay();
	SCL_WRITE_H();
	Delay();
	SCL_WRITE_L();
	Delay();
	SDA_WRITE_H();
}


/**
 * @brief 产生 NACK 信号
 * @return *
*/
static void I2Cs_NAck()
{
    Delay();
    SDA_OUT();
	SDA_WRITE_H();
	Delay();
	SCL_WRITE_H();
	Delay();
	SCL_WRITE_L();
	Delay();
}


/**
 * @brief 检测 I2C 从设备是否存在
 * @param SlaveAddr 从设备地址
 * @return 若设备存在则返回 XST_SUCCESS，否则返回 XST_FAILURE
*/
s32 I2Cs_CheckDev(uint8_t SlaveAddr)
{
	s32 status;

	I2Cs_Start();
	I2Cs_WriteByte(SlaveAddr << 1);
    status = I2Cs_WaitAck(ACK_TIMEOUT_TICKS);
	I2Cs_Stop();
	
	return status;
}


/**
 * @brief 写寄存器数据
 * @param SlaveAddr 从机地主
 * @param RegAddr 寄存器地址
 * @param Value 待写入的数据
 * @return 写入成功返回 XST_SUCCESS，否则返回 XST_FAILURE
*/
s32 I2Cs_WriteReg(uint8_t SlaveAddr, uint16_t RegAddr, uint8_t Value)
{
    I2Cs_Start();

    // 写从机设备地址
    I2Cs_WriteByte(SlaveAddr << 1);
    if(I2Cs_WaitAck(ACK_TIMEOUT_TICKS) != XST_SUCCESS)
    {
        I2Cs_Stop();
        return XST_FAILURE;
    }

    // 写寄存器地址
    I2Cs_WriteByte(RegAddr >> 8);
    if(I2Cs_WaitAck(ACK_TIMEOUT_TICKS) != XST_SUCCESS)
    {
        I2Cs_Stop();
        return XST_FAILURE;
    }
    I2Cs_WriteByte(RegAddr & 0xFF);
    if(I2Cs_WaitAck(ACK_TIMEOUT_TICKS) != XST_SUCCESS)
    {
        I2Cs_Stop();
        return XST_FAILURE;
    }

    // 写寄存器数据
    I2Cs_WriteByte(Value);
    if(I2Cs_WaitAck(ACK_TIMEOUT_TICKS) != XST_SUCCESS)
    {
        I2Cs_Stop();
        return XST_FAILURE;
    }
    I2Cs_Stop();

    return XST_SUCCESS;
}


/**
 * @brief 读寄存器
 * @param SlaveAddr 从机地址
 * @param RegAddr 寄存器地址
 * @return 寄存器数据
*/
uint8_t I2Cs_ReadReg(uint8_t SlaveAddr, uint16_t RegAddr)
{
    uint8_t value;

    I2Cs_Start();

    // 写从机设备地址
    I2Cs_WriteByte(SlaveAddr << 1);
    if(I2Cs_WaitAck(ACK_TIMEOUT_TICKS) != XST_SUCCESS)
    {
        I2Cs_Stop();
        return XST_FAILURE;
    }

    // 写寄存器地址
    I2Cs_WriteByte(RegAddr >> 8);
    if(I2Cs_WaitAck(ACK_TIMEOUT_TICKS) != XST_SUCCESS)
    {
        I2Cs_Stop();
        return XST_FAILURE;
    }
    I2Cs_WriteByte(RegAddr & 0xFF);
    if(I2Cs_WaitAck(ACK_TIMEOUT_TICKS) != XST_SUCCESS)
    {
        I2Cs_Stop();
        return XST_FAILURE;
    }

    // 写从机地址
    I2Cs_Start();
    I2Cs_WriteByte((SlaveAddr << 1) | 0x01);
    if(I2Cs_WaitAck(ACK_TIMEOUT_TICKS) != XST_SUCCESS)
    {
        I2Cs_Stop();
        return XST_FAILURE;
    }

    // 读取寄存器数据
    value = I2Cs_ReadByte();

    I2Cs_NAck();
    I2Cs_Stop();

    return value;
}


/**
 * @brief 初始化 I2Cs
 * @param 设备 ID
 * @return *
*/
void I2Cs_Init(uint16_t DeviceId)
{
    XGpio_Initialize(&GPIO_I2Cs, DeviceId);

    // 设置输入/输出
    XGpio_SetDataDirection(&GPIO_I2Cs, 1, 0x0);
    XGpio_SetDataDirection(&GPIO_I2Cs, 2, 0x0);
    
    // 初始化总线输出
    SDA_WRITE_H();
    Delay();
    SCL_WRITE_H();
    Delay();
}