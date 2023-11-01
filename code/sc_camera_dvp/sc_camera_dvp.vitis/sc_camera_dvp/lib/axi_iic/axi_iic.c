#include "axi_iic.h"

/**
 * @brief 初始化 AXI_IIC 设备实例
 * @param DeviceId  设备地址
 * @return 设备实例
*/
XIic* AXI_IIC_Init(uint16_t DeviceId)
{
    XIic* InstPtr = (XIic*)malloc(sizeof(XIic));
    if(InstPtr != NULL)
    {
        XIic_Config *ConfigPtr = XIic_LookupConfig(DeviceId);
	    XIic_CfgInitialize(InstPtr, ConfigPtr, ConfigPtr->BaseAddress);
    }
    return InstPtr;
}


/**
 * @brief 写单个寄存器
 * @param InstPtr   AXI_IIC 设备实例
 * @param SlaveAddr 从机地址
 * @param RegAddr   寄存器地址
 * @param Value     待写入的寄存器值
 * @return *
*/
void AXI_IIC_Write_Reg(XIic *InstPtr, uint8_t SlaveAddr, uint16_t RegAddr, uint8_t Value)
{
	uint8_t SendByteCount = 0;
	uint8_t SendBuffer[3] = { RegAddr >> 8, RegAddr & 0xFF, Value };
	do
    {
        SendByteCount = XIic_Send(InstPtr->BaseAddress, SlaveAddr, SendBuffer, 3, XIIC_STOP);
    }while(SendByteCount < 3);
}


/**
 * @brief 读单个寄存器
 * @param InstPtr   AXI_IIC 设备实例
 * @param SlaveAddr 从机地址
 * @return 寄存器值
*/
uint8_t AXI_IIC_Read_Reg(XIic *InstPtr, uint8_t SlaveAddr, uint16_t RegAddr)
{
	uint8_t ByteCount = 0;
	uint8_t ReadBuffer[1];
    uint8_t WriteBuffer[2] = { RegAddr >> 8, RegAddr & 0xFF };

	// 写寄存器地址
    do
    {
        ByteCount = XIic_Send(InstPtr->BaseAddress, SlaveAddr, WriteBuffer, 2, XIIC_STOP);
    }while(ByteCount < 2);
	//接收数据
	do
	{
		ByteCount = XIic_Recv(InstPtr->BaseAddress, SlaveAddr, ReadBuffer, 1, XIIC_STOP);
	}while(ByteCount < 1);

	return ReadBuffer[0];
}


/**
 * @brief 写入多个寄存器
 * @param InstPtr       AXI_IIC 设备实例
 * @param RegValuePairs 待写入的寄存器键值对
 * @return *
*/
void AXI_IIC_Write_Regs(XIic *InstPtr, uint8_t SlaveAddr, RegValuePair *RegValuePairs)
{
    uint16_t RegWriteIndex = 0;
    while(RegValuePairs[RegWriteIndex].Addr != REG_NULL_ADDR)
    {
        AXI_IIC_Write_Reg(InstPtr, SlaveAddr, RegValuePairs[RegWriteIndex].Addr, RegValuePairs[RegWriteIndex].Value);
        RegWriteIndex++;
    }
}