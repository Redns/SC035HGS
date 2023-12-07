#include "axi_gpio.h"

/**
 * @brief 初始化 AXI GPIO
 * @param InstancePtr AXI GPIO 配置结构体
 * @return 配置成功返回 XST_SUCCESS
*/
s32 Axi_Gpio_Init(AxiGpio* InstancePtr)
{
    s32 Status;

    // 初始化配置
    Status = XGpio_Initialize(InstancePtr->XGpioInstancePtr, InstancePtr->DeviceId);  
    if(Status != XST_SUCCESS)
    {
        return Status;
    } 

    // 设置通道方向
    XGpio_SetDataDirection(InstancePtr->XGpioInstancePtr, 1, (InstancePtr->Channel1.Direction ==  GPIO_DIRECTION_INPUT) ? 0xFFFFFFFF : 0x0);
    XGpio_SetDataDirection(InstancePtr->XGpioInstancePtr, 2, (InstancePtr->Channel2.Direction ==  GPIO_DIRECTION_INPUT) ? 0xFFFFFFFF : 0x0);
    
    // 设置通道电平
    XGpio_DiscreteWrite(InstancePtr->XGpioInstancePtr, 1, InstancePtr->Channel1.Value);
    XGpio_DiscreteWrite(InstancePtr->XGpioInstancePtr, 2, InstancePtr->Channel2.Value);

    return Status;
}


s32 Axi_Gpio_WriteChannel(AxiGpio* InstancePtr, u8 ChannelId, u32 Value)
{
    // 获取通道信息
    AxiGpioChannel Channel = (ChannelId == 1) ? InstancePtr->Channel1 : InstancePtr->Channel2;
    if(Channel.Direction == GPIO_DIRECTION_INPUT)
    {
        return XST_FAILURE;
    }

    // 设置通道输出
    Channel.Value = Value;
    XGpio_DiscreteWrite(InstancePtr->XGpioInstancePtr, ChannelId, Channel.Value);
}


s32 Axi_Gpio_WriteBit(AxiGpio* InstancePtr, u8 ChannelId, u8 BitStart, u8 BitNums, u32 Value)
{

}