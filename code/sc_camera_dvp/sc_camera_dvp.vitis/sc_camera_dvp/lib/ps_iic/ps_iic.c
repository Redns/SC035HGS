#include "ps_iic.h"

/**
 * @brief 初始化 IIC
 * @param DeviceId  设备标识符
 * @param SclFrqHz  IIC 时钟频率（Hz）
 * @return IIC 句柄 
*/
XIicPs* PS_IIC_Init(uint16_t DeviceId, uint32_t SclFrqHz)
{
	XIicPs_Config *Config;
    XIicPs* InstPtr = (XIicPs*)malloc(sizeof(XIicPs));

	// 查找 PS IIC 配置
	Config = XIicPs_LookupConfig(DeviceId);
	XIicPs_CfgInitialize(InstPtr, Config, Config->BaseAddress);

	// 设置时钟
	XIicPs_SetSClk(InstPtr, SclFrqHz);

    return InstPtr;
}


/**
 * @brief 写单个寄存器
 * @param InstPtr   IIC 句柄
 * @param SlaveAddr 从机地址
 * @param RegAddr   寄存器地址
 * @param Value     待写入的值
 * @return XST_STATUS
*/
void PS_IIC_Write_Reg(XIicPs *InstPtr, uint8_t SlaveAddr, uint16_t RegAddr, uint8_t Value)
{
    // 初始化数组
	uint8_t SendBuffer[3] = { RegAddr >> 8, RegAddr & 0xFF, Value };
    // 传输数据
    XIicPs_MasterSendPolled(InstPtr, SendBuffer, 3, SlaveAddr);
    // 等待数据传输完成
    while(XIicPs_BusIsBusy(InstPtr));
}


/**
 * @brief 读单个寄存器
 * @param InstPtr   IIC 句柄
 * @param SlaveAddr 从机地址
 * @param RegAddr   寄存器地址
 * @return 寄存器值
*/
uint8_t PS_IIC_Read_Reg(XIicPs *InstPtr, uint8_t SlaveAddr, uint16_t RegAddr)
{
	uint8_t RecvBuffer[1];
    uint8_t SendBuffer[2] = { RegAddr >> 8, RegAddr & 0xFF };
    
    // 发送寄存器地址
    XIicPs_MasterSendPolled(InstPtr, SendBuffer, 2, SlaveAddr);
    // 等待数据传输完成
    while (XIicPs_BusIsBusy(InstPtr));
    // 接收寄存器数据
    XIicPs_MasterRecvPolled(InstPtr, RecvBuffer, 1, SlaveAddr);
	//等待数据接收完成
    while (XIicPs_BusIsBusy(InstPtr));

	return RecvBuffer[0];
}