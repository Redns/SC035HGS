#include "i2cs.h"

XGpio GPIO_I2Cs;

/**
 * @brief ��ʱ����
 * @param us ��ʱʱ�䣨΢�룩
 * @return *
*/
static void Delay_Us(uint8_t us)
{
    usleep(us);
}


/**
 * @brief ��ʱ����
 * @param us ��ʱʱ�䣨���룩
 * @return *
*/
static void Delay_Ms(uint8_t ms)
{
    usleep(ms * 1000);
}


/**
  * @brief I2C ��ʼ�ź�
  * @return *
  */
static void I2Cs_Start()
{
	SDA_OUT();
    SDA_WRITE_H();
    SCL_WRITE_H();
    Delay_Us(5);
    SDA_WRITE_L();
    Delay_Us(5);
    SCL_WRITE_L();
    Delay_Us(2);
    SDA_WRITE_H();
    Delay_Us(2);
}


/**
 * @brief I2C �����ź�
 * @return *
*/
static void I2Cs_Stop()
{
	SDA_OUT();

	SDA_WRITE_L();
    SCL_WRITE_L();
    Delay_Us(2);

	SCL_WRITE_H();
	Delay_Us(2);
	SDA_WRITE_H();
    Delay_Us(2);
    SCL_WRITE_L();

    Delay_Us(2);
}


/**
 * @brief ���͵����ֽ�
 * @param byte �����͵��ֽ�
 * @return *
*/
static void I2Cs_WriteByte(uint8_t byte)
{
    SDA_OUT();

	for(uint8_t i = 0; i < 8; i++)
	{
        SCL_WRITE_L();
        Delay_Us(5);
		if(byte & 0x80)
		{
			SDA_WRITE_H();
		}
		else
		{
			SDA_WRITE_L();
		}
		SCL_WRITE_H();
        Delay_Us(5);
        SCL_WRITE_L();
        byte <<= 1;
	}

    Delay_Us(2);
    SDA_WRITE_H();
    Delay_Us(2);
}


/**
 * @brief �������ֽ�
 * @return ��ȡ���ֽ�����
*/
static uint8_t I2Cs_ReadByte()
{
    uint8_t byte = 0;

    SDA_IN();

    Delay_Us(2);
    SDA_WRITE_H();
    Delay_Us(2);

	for(uint8_t i = 0; i < 8; i++)
	{
		byte <<= 1;
		SCL_WRITE_L();
		Delay_Us(5);
        SCL_WRITE_H();
        Delay_Us(2);

		if(SDA_READ())
		{
			byte |= 0x01;
		}
        else
        {
            byte &= 0xFE;
        }
	}

    SCL_WRITE_L();
    Delay_Us(2);

	return byte;
}


/**
 * @brief �ȴ� ACK �ź�
 * @return ��ȷӦ�𷵻� XST_SUCCESS�����򷵻� XST_FAILURE
*/
static s32 I2Cs_WaitAck()
{
    SDA_IN();

    // TODO
    SCL_WRITE_L();
    SDA_WRITE_H();
    Delay_Us(5);

    SCL_WRITE_H();
    Delay_Us(5);
    SCL_WRITE_L();

    Delay_Us(2);

    return XST_SUCCESS;
}


/**
 * @brief ���� ACK �ź�
 * @return *
*/
//static void I2Cs_Ack()
//{
//    SDA_OUT();
//
//    SCL_WRITE_L();
//	SDA_WRITE_L();
//	Delay_Us(5);
//
//	SCL_WRITE_H();
//	Delay_Us(5);
//	SCL_WRITE_L();
//
//	Delay_Us(2);
//	SDA_WRITE_H();
//    Delay_Us(2);
//}


/**
 * @brief ���� NACK �ź�
 * @return *
*/
static void I2Cs_NAck()
{
    SDA_OUT();

    SCL_WRITE_L();
	SDA_WRITE_H();
	Delay_Us(5);

	SCL_WRITE_H();
	Delay_Us(5);
	SCL_WRITE_L();

	Delay_Us(2);
    SDA_WRITE_H();
    Delay_Us(2);
}


/**
 * @brief ��� I2C ���豸�Ƿ����
 * @param SlaveAddr ���豸��ַ
 * @return ���豸�����򷵻� XST_SUCCESS�����򷵻� XST_FAILURE
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
 * @brief д�Ĵ�������
 * @param SlaveAddr �ӻ�����
 * @param RegAddr �Ĵ�����ַ
 * @param Value ��д�������
 * @return д��ɹ����� XST_SUCCESS�����򷵻� XST_FAILURE
*/
s32 I2Cs_WriteReg(uint8_t SlaveAddr, uint16_t RegAddr, uint8_t Value)
{
    I2Cs_Start();

    // д�ӻ��豸��ַ
    I2Cs_WriteByte(SlaveAddr << 1);
    if(I2Cs_WaitAck(ACK_TIMEOUT_TICKS) != XST_SUCCESS)
    {
        I2Cs_Stop();
        return XST_FAILURE;
    }

    // д�Ĵ�����ַ
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

    // д�Ĵ�������
    I2Cs_WriteByte(Value);
    if(I2Cs_WaitAck(ACK_TIMEOUT_TICKS) != XST_SUCCESS)
    {
        I2Cs_Stop();
        return XST_FAILURE;
    }
    I2Cs_Stop();

    Delay_Ms(5);

    return XST_SUCCESS;
}


/**
 * @brief ���Ĵ���
 * @param SlaveAddr �ӻ���ַ
 * @param RegAddr �Ĵ�����ַ
 * @return �Ĵ�������
*/
uint8_t I2Cs_ReadReg(uint8_t SlaveAddr, uint16_t RegAddr)
{
    uint8_t value;

    I2Cs_Start();

    // д�ӻ��豸��ַ
    I2Cs_WriteByte(SlaveAddr << 1);
    if(I2Cs_WaitAck(ACK_TIMEOUT_TICKS) != XST_SUCCESS)
    {
        I2Cs_Stop();
        return XST_FAILURE;
    }

    // д�Ĵ�����ַ
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

    // д�ӻ���ַ
    I2Cs_Start();
    I2Cs_WriteByte((SlaveAddr << 1) | 0x01);
    if(I2Cs_WaitAck(ACK_TIMEOUT_TICKS) != XST_SUCCESS)
    {
        I2Cs_Stop();
        return XST_FAILURE;
    }

    // ��ȡ�Ĵ�������
    value = I2Cs_ReadByte();

    I2Cs_NAck();
    I2Cs_Stop();

    return value;
}


/**
 * @brief ��ʼ�� I2Cs
 * @param �豸 ID
 * @return *
*/
void I2Cs_Init(uint16_t DeviceId)
{
    XGpio_Initialize(&GPIO_I2Cs, DeviceId);

    // ��������/���
    XGpio_SetDataDirection(&GPIO_I2Cs, 1, 0x0);
    XGpio_SetDataDirection(&GPIO_I2Cs, 2, 0x0);

    // ��ʼ���������
    XGpio_DiscreteWrite(&GPIO_I2Cs, 1, 0x1);
    XGpio_DiscreteWrite(&GPIO_I2Cs, 2, 0x1);
}
