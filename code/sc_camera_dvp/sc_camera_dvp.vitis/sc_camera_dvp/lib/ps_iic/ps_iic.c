#include "ps_iic.h"


/**
 * @brief 等待总线空闲
 * @return *
*/
static void Wait_Bus_Free(XIicPs* InstPtr)
{
    uint8_t wait_bus_free_ticks = WAIT_BUS_FREE_MAX_TICKS;
    while(XIicPs_BusIsBusy(InstPtr) && (wait_bus_free_ticks--))
    {
    }
    usleep(10);
}

/**
 * @brief 初始化 IIC
 * @param DeviceId  设备标识符
 * @param SclFrqHz  IIC 时钟频率（Hz）
 * @return IIC 句柄 
*/
s32 PS_IIC_Init(XIicPs *InstPtr, uint16_t DeviceId, uint32_t SclFrqHz)
{
    s32 Status;

	// 查找 PS IIC 配置
	XIicPs_Config* Config = XIicPs_LookupConfig(DeviceId);
    if(Config == NULL)
    {
        return XST_FAILURE;
    }

    // 配置 PS IIC
	Status = XIicPs_CfgInitialize(InstPtr, Config, Config->BaseAddress);
    if(Status != XST_SUCCESS)
    {
        return XST_FAILURE;
    }

    // 自测
    Status = XIicPs_SelfTest(InstPtr);
    if(Status != XST_SUCCESS)
    {
        return XST_FAILURE;
    }

    // 设置 IIC SCL 时钟
	Status = XIicPs_SetSClk(InstPtr, SclFrqHz);
    if(Status != XST_SUCCESS)
    {
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
        return XST_FAILURE;
    }
    Wait_Bus_Free(InstPtr);

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
    s32 Status;
	uint8_t RecvBuffer[1] = { 0x00 };
    uint8_t SendBuffer[2] = { RegAddr >> 8, RegAddr & 0xFF };
    
    /* 发送从机地址+寄存器地址 */
    // 启用 Repeat Start
    XIicPs_SetOptions(InstPtr, XIICPS_REP_START_OPTION);
    // 发送地址
    Status = XIicPs_MasterSendPolled(InstPtr, SendBuffer, 2, SlaveAddr);
    if(Status != XST_SUCCESS)
    {
        return XST_FAILURE;
    }
    // 禁用 Repeat Start
    XIicPs_ClearOptions(InstPtr, XIICPS_REP_START_OPTION);

    // 接收寄存器数据
    Status = XIicPs_MasterRecvPolled(InstPtr, RecvBuffer, 1, SlaveAddr);
    if(Status != XST_SUCCESS)
    {
        return XST_FAILURE;
    }
    Wait_Bus_Free(InstPtr);

	return RecvBuffer[0];
}