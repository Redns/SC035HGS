#include "ps_iic.h"

/**
 * @brief 初始化 IIC
 * @param DeviceId  设备标识符
 * @param SclFrqHz  IIC 时钟频率（Hz）
 * @return IIC 句柄 
*/
s32 PS_IIC_Init(XIicPs *InstPtr, uint16_t DeviceId, uint32_t SclFrqHz)
{
    s32 status;
    XIicPs_Config* Config;

	// 查找 PS IIC 配置
	Config = XIicPs_LookupConfig(DeviceId);
    if(Config == NULL)
    {
        xil_printf("[ERROR] Failed to find the config of IIC_%u)\n", DeviceId);
        return XST_FAILURE;
    }
    // 配置 PS IIC
	status = XIicPs_CfgInitialize(InstPtr, Config, Config->BaseAddress);
    if(status != XST_SUCCESS)
    {
        xil_printf("[ERROR] Failed to config IIC_%u\n", DeviceId);
        return XST_FAILURE;
    }
    // 自测
    status = XIicPs_SelfTest(InstPtr);
    if(status != XST_SUCCESS)
    {
        xil_printf("[ERROR] Failed to self test IIC_%u\n", DeviceId);
        return XST_FAILURE;
    }
    // 使能 REPEATED START
    status = XIicPs_SetOptions(InstPtr, XIICPS_REP_START_OPTION);
    if(status != XST_SUCCESS)
    {
        xil_printf("[ERROR] Failed to set REPEATED_START option of IIC_%u\n", DeviceId);
        return XST_FAILURE;
    }
	// 设置 IIC SCL 时钟
	status = XIicPs_SetSClk(InstPtr, SclFrqHz);
    if(status != XST_SUCCESS)
    {
        xil_printf("[ERROR] Failed to set frq of IIC_%u, current frq is %uHz\n", DeviceId, XIicPs_GetSClk(InstPtr));
        return XST_FAILURE;
    }

    return XST_SUCCESS;
}


/**
 * @brief 写单个寄存器
 * @param InstPtr   IIC 句柄
 * @param SlaveAddr 从机地址
 * @param RegAddr   寄存器地址
 * @param Value     待写入的值
 * @return XST_STATUS
*/
s32 PS_IIC_Write_Reg(XIicPs *InstPtr, uint8_t SlaveAddr, uint16_t RegAddr, uint8_t Value)
{
    // 初始化数组
	uint8_t SendBuffer[3] = { RegAddr >> 8, RegAddr & 0xFF, Value };
    // 传输数据
    if(XIicPs_MasterSendPolled(InstPtr, SendBuffer, 3, SlaveAddr) != XST_SUCCESS)
    {
        xil_printf("[ERROR] Failed to write reg 0x%04x\n", RegAddr);
        return XST_FAILURE;
    }
    // while(XIicPs_BusIsBusy(InstPtr)){}
    usleep(10 * 1000);

    return XST_SUCCESS;
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
	uint8_t RecvBuffer[1] = { 0x00 };
    uint8_t SendBuffer[2] = { RegAddr >> 8, RegAddr & 0xFF };
    
    // 发送寄存器地址
    s32 status = XIicPs_MasterSendPolled(InstPtr, SendBuffer, 2, SlaveAddr);
    if(status != XST_SUCCESS)
    {
        xil_printf("[ERROR] Failed ro read reg {0x%04x}\n", RegAddr); return RecvBuffer[0];
    }
    // while(XIicPs_BusIsBusy(InstPtr)){}
    usleep(10 * 1000);
    // 接收寄存器数据
    status = XIicPs_MasterRecvPolled(InstPtr, RecvBuffer, 1, SlaveAddr);
    if(status != XST_SUCCESS)
    {
        xil_printf("[ERROR] Failed ro read reg {0x%04x}\n", RegAddr); return RecvBuffer[0];
    }
    // while(XIicPs_BusIsBusy(InstPtr)){}
    usleep(10 * 1000);

	return RecvBuffer[0];
}