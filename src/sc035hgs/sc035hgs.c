#include "sc035hgs.h"

/**
 * @brief 读单个寄存器
 * @param InstancePtr    摄像头句柄
 * @param reg_addr  寄存器地址
 * @return 寄存器值
*/
static u8 Get_Reg(Camera_t *InstancePtr, u16 RegAddr)
{
	return I2Cs_ReadReg(InstancePtr->SlaveAddr, RegAddr);
}

/**
 * @brief 写单个寄存器
 * @param InstancePtr    摄像头句柄
 * @param reg_addr  寄存器地址
 * @param mask      掩码（对应 BIT 为 1 则修改）
 * @param value     待写入的值
 * @return 写入成功返回 XST_SUCCESS，否则返回 XST_FAILURE
*/
static u32 Set_Reg(Camera_t *InstancePtr, u16 RegAddr, u8 Value)
{
	return I2Cs_WriteReg(InstancePtr->SlaveAddr, RegAddr, Value);
}

/**
 * @brief 写单个寄存器多个比特
 * @param InstancePtr    摄像头句柄
 * @param reg_addr  寄存器地址
 * @param offset    寄存器比特偏移
 * @param length    寄存器比特写入数量（以位为单位，由低位至高位）
 * @param value     待写入的值
 * @return 成功返回 XST_SUCCESS，否则返回 XST_FAILURE
*/
static u32 Set_Reg_Bits(Camera_t *InstancePtr, u16 RegAddr, u8 Offset, u8 Length, u8 Value)
{
    u8 OriginValue;

    // 获取寄存器原始值
    OriginValue = I2Cs_ReadReg(InstancePtr->SlaveAddr, RegAddr);

    // 修改寄存器相应比特位
    u8 mask = ((1 << Length) - 1) << Offset;
    Value = (OriginValue & ~mask) | ((Value << Offset) & mask);

    // 写寄存器
    return I2Cs_WriteReg(InstancePtr->SlaveAddr, RegAddr, Value);
}

/**
 * @brief 写多个寄存器
 * @param InstancePtr            摄像头句柄
 * @param reg_value_pairs   寄存器键值对
 * @return 写入成功返回 XST_SUCCESS
*/
static u32 Write_Regs(Camera_t *InstancePtr, const RegValuePair *RegValuePairs)
{
    u32 Status;

    for(u16 i = 0; ; i++)
    {
        /* 配置完成 */
        if(RegValuePairs[i].Addr == REG_NULL_ADDR)
        {
            break;
        }

        /* 延时（以 ms 为单位） */
        if(RegValuePairs[i].Addr == REG_DELAY_ADDR)
        {
            usleep(RegValuePairs[i].Value * 1000);
            continue;
        }

        /* 配置寄存器 */
        Status = Set_Reg(InstancePtr, RegValuePairs[i].Addr, RegValuePairs[i].Value);
        if(Status != XST_SUCCESS)
        {
            xil_printf("[ERROR] Failed to write reg {0x%04x} << 0x%02x\n", RegValuePairs[i].Addr, RegValuePairs[i].Value);
            return Status;
        }
        xil_printf("[INFO] Success to write reg {0x%04x} << 0x%02x\n", RegValuePairs[i].Addr, RegValuePairs[i].Value);
    }

    return XST_SUCCESS;
}

/**
 * @brief 水平镜像
 * @param InstancePtr    摄像头句柄
 * @param Enable    水平镜像使能
 * @return 配置成功返回 XST_SUCCESS
*/
u32 SC035HGS_Set_Hmirror(Camera_t *InstancePtr, u8 Enable)
{
    return Set_Reg_Bits(InstancePtr, REG_MIRROR_ENABLE_ADDR, 1, 2, Enable ? 0x3 : 0x0); 
}

/**
 * @brief 垂直翻转
 * @param InstancePtr    摄像头句柄
 * @param Enable    使能控制
 * @return 配置成功返回 XST_SUCCESS
*/
u32 SC035HGS_Set_Vflip(Camera_t *InstancePtr, u8 Enable)
{
    return Set_Reg_Bits(InstancePtr, REG_FLIP_ENABLE_ADDR, 5, 2, Enable ? 0x3 : 0x0);
}

/**
 * @brief 增益控制
 * @param
*/
u32 SC035HGS_Set_Agc(Camera_t *InstancePtr, u8 Gain)
{
    // TODO 增益控制实现
    u32 Status;
    // uint32_t coarse_gain, fine_gain, fine_again_reg_v, coarse_gain_reg_v;

    if(Gain < 2)
    {
        Status = Set_Reg(InstancePtr, 0x3314, 0x1e) |
                 Set_Reg(InstancePtr, 0x3317, 0x1b) |
                 Set_Reg(InstancePtr, 0x3631, 0x58) |
                 Set_Reg(InstancePtr, 0x3630, 0x4a);
    }
    else if(Gain < 4)
    {
        Status = Set_Reg(InstancePtr, 0x3314, 0x6f) |
                 Set_Reg(InstancePtr, 0x3317, 0x10) |
                 Set_Reg(InstancePtr, 0x3631, 0x48) |
                 Set_Reg(InstancePtr, 0x3630, 0x4c);
    }
    else
    {
        Status = Set_Reg(InstancePtr, 0x3314, 0x76) |
                 Set_Reg(InstancePtr, 0x3317, 0x15) |
                 Set_Reg(InstancePtr, 0x3631, 0x48) |
                 Set_Reg(InstancePtr, 0x3630, 0x4c);
    }

    return Status;
}

/**
 * @brief 获取像素时钟频率
 * @param InstancePtr 摄像头句柄
 * @return u32 像素时钟频率
 */
u32 SC035HGS_Get_PclkFreq(Camera_t *InstancePtr)
{
    /* 锁相环输入时钟范围 6~27MHz */
    // 此处像素时钟应由锁相环配置计算得到，但由于手册中没有锁相环相关配置寄存器的介绍，
    // 因此只能按照官方提供的寄存器列表中，输入时钟和像素时钟的换算关系计算
    if((InstancePtr->XclkFreq < 6000000) || (InstancePtr->XclkFreq > 27000000))
    {
        xil_printf("[ERROR] SC035HGS input xclk out of PLL range\n");
        return XST_FAILURE;
    }
    return InstancePtr->XclkFreq *1.0f / 24000000 * 85000000;
}  

/**
 * @brief 设置帧尺寸
 * @param InstancePtr 摄像头句柄
 * @param FrameWidth 帧宽
 * @param FrameHeight 帧高
 * @return u32 设置成功返回 XST_SUCCESS
 */
u32 SC035HGS_Set_FrameSize(Camera_t *InstancePtr, u16 FrameWidth, u16 FrameHeight)
{
    u32 Status;

    /* 检查输入参数 */
    if((FrameWidth <= 0) || (FrameWidth > FRAME_MAX_WIDTH) || (FrameHeight <= 0) || (FrameHeight > FRAME_MAX_HEIGHT))
    {
        xil_printf("[ERROR] FrameSize set failed, invalid param\n");
        return XST_FAILURE;
    }

    /* 调整输出窗口 */
    Status = Set_Reg(InstancePtr, REG_FRAME_WIDTH_HIGH_ADDR, FrameWidth >> 8)   | Set_Reg(InstancePtr, REG_FRAME_WIDTH_LOW_ADDR, FrameWidth & 0xFF)  |
             Set_Reg(InstancePtr, REG_FRAME_HEIGHT_HIGH_ADDR, FrameHeight >> 8) | Set_Reg(InstancePtr, REG_FRAME_HEIGHT_LOW_ADDR, FrameHeight & 0xFF);

    if(Status != XST_SUCCESS)
    {
        return Status;
    }

    /* 更新摄像头属性 */
    InstancePtr->FrameWidth = FrameWidth;
    InstancePtr->FrameHeight = FrameHeight;

    return  XST_SUCCESS;
}

/**
 * @brief 设置图像帧率
 * @param InstancePtr 摄像头句柄
 * @param fps 图像帧率
 * @return u32 设置成功返回 XST_SUCCESS
 */
u32 SC035HGS_Set_Fps(Camera_t *InstancePtr, u8 Fps)
{
    u32 Status;

    /* 获取像素时钟 */
    u32 PclkFreq = SC035HGS_Get_PclkFreq(InstancePtr);
    if(PclkFreq == XST_FAILURE)
    {
        xil_printf("[ERROR] SC035HGS pclk error\n");
        return XST_FAILURE;
    }

    /* 判断帧率是否可实现 */
    float FrameResizeRatio = PclkFreq * 1.0f / (InstancePtr->FrameWidth * InstancePtr->FrameHeight * Fps);
    if((!Fps) || (Fps > 180) || (FrameResizeRatio < 1.0f))
    {
        xil_printf("[ERROR] FPS %u unrealizable\n", Fps);
        return XST_FAILURE;
    }

    /* 计算帧长和帧宽 */
    u16 WindowWidth = InstancePtr->FrameWidth * sqrt(FrameResizeRatio);
    u16 WindowHeight = PclkFreq / (WindowWidth * Fps);
    
    Status = SC035HGS_Set_WindowWidth(InstancePtr, WindowWidth) | SC035HGS_Set_WindowHeight(InstancePtr, WindowHeight);
    if(Status != XST_SUCCESS)
    {
        return Status;
    }
    InstancePtr->Fps = Fps;

    return XST_SUCCESS;
}

/**
 * @brief 获取窗口宽度
 * @param InsatncePtr 摄像头句柄
 * @return u32 获取到的窗口宽度
 */
u16 SC035HGS_Get_WindowWidth(Camera_t *InsatncePtr)
{
    return (Get_Reg(InsatncePtr, REG_WINDOW_WIDTH_HIGH_ADDR) << 8) | Get_Reg(InsatncePtr, REG_WINDOW_WIDTH_LOW_ADDR);
}

/**
 * @brief 获取窗口高度
 * @param InsatncePtr 摄像头句柄
 * @return u32 获取到的窗口宽度
 */
u16 SC035HGS_Get_WindowHeight(Camera_t *InsatncePtr)
{
    return (Get_Reg(InsatncePtr, REG_WINDOW_HEIGHT_HIGH_ADDR) << 8) | Get_Reg(InsatncePtr, REG_WINDOW_HEIGHT_LOW_ADDR);
}

/**
 * @brief 设置摄像头输出窗口宽度
 * @param InstancePtr 摄像头句柄
 * @param Width 窗口宽度
 * @return u32 设置成功返回 XST_SUCCESS
 */
u32 SC035HGS_Set_WindowWidth(Camera_t *InstancePtr, u16 Width)
{
    if(!InstancePtr || !Width)
    {
        xil_printf("[ERROR] SC035HGS set window width failed because of invalid args (InstancePtr: %p, Width %u)\n", InstancePtr, Width);
        return XST_FAILURE;
    }

    return Set_Reg(InstancePtr, REG_WINDOW_WIDTH_HIGH_ADDR, Width >> 8) | Set_Reg(InstancePtr, REG_WINDOW_WIDTH_LOW_ADDR, Width & 0xFF);
}

/**
 * @brief 设置摄像头输出窗口高度
 * @param InstancePtr 摄像头句柄
 * @param Width 窗口高度
 * @return u32 设置成功返回 XST_SUCCESS
 */
u32 SC035HGS_Set_WindowHeight(Camera_t *InstancePtr, u16 Height)
{
    if(!InstancePtr || !Height)
    {
        xil_printf("[ERROR] SC035HGS set window width failed because of invalid args (InstancePtr: %p, Height %u)\n", InstancePtr, Height);
        return XST_FAILURE;
    }

    return Set_Reg(InstancePtr, REG_WINDOW_HEIGHT_HIGH_ADDR, Height >> 8) | Set_Reg(InstancePtr, REG_WINDOW_HEIGHT_LOW_ADDR, Height & 0xFF);
}

/**
 * @brief 设置摄像头输出窗口尺寸
 * @param InstancePtr 摄像头句柄
 * @param Width 输出窗口宽度
 * @param Height 输出窗口高度
 * @return u32 设置成功返回 XST_SUCCESS
 */
u32 SC035HGS_Set_WindowSize(Camera_t *InstancePtr, u16 Width, u16 Height)
{
    if(!InstancePtr || !Width || !Height)
    {
        xil_printf("[ERROR] SC035HGS set window size failed, invalid args (InstancePtr: %p, Width %u, Height: %u)\n", InstancePtr, Width, Height);
        return XST_FAILURE;
    }

    return SC035HGS_Set_WindowWidth(InstancePtr, Width) | SC035HGS_Set_WindowHeight(InstancePtr, Height);
}

/**
 * @brief 测试模式
 * @param InstancePtr    摄像头句柄
 * @param Enable    使能控制
 * @return *
*/
u32 SC035HGS_Set_Increment_Pattern(Camera_t *InstancePtr, u8 Enable)
{
    u32 Status;
    
    /* 使能灰度渐变测试模式 */
    Status = Set_Reg_Bits(InstancePtr, REG_INCREMENT_PATTERN_ENABLE_ADDR, 3, 1, Enable ? 0x1 : 0x0);
    if(Status != XST_SUCCESS)
    {
        xil_printf("[ERROR] SC035HGS increment pattern set failed\n");
        return Status;
    }

    /* 使能自动 BLC */
    Status = SC035HGC_Set_Blc(InstancePtr, &InstancePtr->BLC_Args);
    if(Status != XST_SUCCESS)
    {
        xil_printf("[ERROR] SC035HGS failed to Enable auto blc\n");
        return Status;
    }

    /* 设置自动增益 */
    Status = SC035HGS_Set_Agc(InstancePtr, 4);
    if(Status != XST_SUCCESS)
    {
        xil_printf("[ERROR] SC035HGS failed to set agc\n");
        return Status;
    }

    return XST_SUCCESS;
}

/**
 * @brief 软休眠（通过修改寄存器休眠，此时仍可访问传感器寄存器）
 * @param InstancePtr    摄像头句柄
 * @param Enable    使能控制
 * @return *
*/
u32 SC035HGS_Set_Sleep_Mode(Camera_t *InstancePtr, u8 Enable)
{
    return Set_Reg(InstancePtr, REG_SLEEP_MODE_CTRL_ADDR, Enable ? REG_SLEEP_MODE_ENABLE : REG_SLEEP_MODE_DISABLE);
}

/**
 * @brief BLC 设置
 * @param InstancePtr    摄像头句柄
 * @param args      BLC 参数
 * @return *
*/
u32 SC035HGC_Set_Blc(Camera_t *InstancePtr, BLC_Args *Args)
{
    u32 Status;
    
    /* 使能 BLC */
    Status = Set_Reg_Bits(InstancePtr, REG_BLC_ENABLE_ADDR, 0, 1, Args->Enable);
    if(Status != XST_SUCCESS)
    {
        xil_printf("[ERROR] SC035HGS BLC enable/disable failed\n");
        return Status;
    }
    InstancePtr->BLC_Args.Enable = Args->Enable;

    /* 模式选择 */
    Status = Set_Reg_Bits(InstancePtr, REG_BLC_MODE_CTRL_ADDR, 6, 1, Args->Mode);
    if(Status != XST_SUCCESS)
    {
        xil_printf("[ERROR] SC035HGS BLC mode set failed\n");
        return Status;
    }
    InstancePtr->BLC_Args.Mode = Args->Mode;

    /* 设置目标值 */
    if(Args->Mode == BLC_MODE_AUTO)
    {
        return XST_SUCCESS;
    }

    Status |= Set_Reg_Bits(InstancePtr, REG_BLC_TARGET_VALUE_HIGH_ADDR, 0, 5, Args->TargetValue >> 8);
    Status |= Set_Reg_Bits(InstancePtr, REG_BLC_TARGET_VALUE_LOW_ADDR, 0, 8, Args->TargetValue & 0xff);
    if(Status != XST_SUCCESS)
    {
        xil_printf("[ERROR] SC035HGS BLC target value set failed\n");
        return Status;
    }
    InstancePtr->BLC_Args.TargetValue = Args->TargetValue;

    return XST_SUCCESS;
}

/**
 * @brief 设置摄像头曝光模式
 * @param InsatncePtr 摄像头句柄
 * @param Mode 曝光模式
 * @return u32 设置成功返回 XST_SUCCESS
 */
u32 SC035HGS_Set_ExposureMode(Camera_t *InsatncePtr, Exposure_Mode Mode)
{
    u32 Status;

    if(!InsatncePtr)
    {
        xil_printf("[ERROR] SC035HGS set exposure mode failed, invalid args\n");
        return XST_FAILURE;
    }

    Status = Set_Reg_Bits(InsatncePtr, REG_HDR_ENABLE_CTRL_ADDR, 6, 1, Mode);
    if(Status != XST_SUCCESS)
    {
        xil_printf("[ERROR] SC035HGS exposure mode set failed\n");
        return Status;
    }
    InsatncePtr->ExposureMode = Mode;

    return XST_SUCCESS;
}

/**
 * @brief AEC 曝光时间设置
 * @param InstancePtr       摄像头句柄
 * @param TotalExposureTime 总曝光时间（以 1/16 行为单位）
 * @param HDRExposureTime   HDR 曝光时间（以 1/16 行为单位，Normal 模式下无效）
 * @return 设置成功返回 XST_SUCCESS
*/
u32 SC035HGS_Set_Aec(Camera_t *InstancePtr, u16 TotalExposureTime, u16 HDRExposureTime)
{
    u32 Status;

    if(!InstancePtr || !TotalExposureTime)
    {
        xil_printf("[ERROR] SC035HGS failed to set aec, invalid args\n");
        return XST_FAILURE;
    }

    /* 设置总曝光时间 */
    // 曝光时间上限不能超过当前帧长减去 6 行
    u32 CameraWindowHeight = SC035HGS_Get_WindowHeight(InstancePtr);
    if((TotalExposureTime >> 4) > CameraWindowHeight - 6)
    {
        TotalExposureTime -= (6 << 4); 
    }

    Status = Set_Reg(InstancePtr, REG_AEC_TOTAL_EXPOSURE_TIME_HIGH_ADDR, (TotalExposureTime >> 8) & 0xff) | Set_Reg(InstancePtr, REG_AEC_TOTAL_EXPOSURE_TIME_LOW_ADDR, TotalExposureTime & 0xff);
    if(Status != XST_SUCCESS)
    {
        xil_printf("[ERROR] SC035HGS failed to set aec total exposure time\n");
        return Status;
    }

    if(InstancePtr->ExposureMode != EXPOSURE_HDR_MODE)
    {
        return XST_SUCCESS;
    }

    /* 设置 HDR 曝光时间 */
    if(!HDRExposureTime || (HDRExposureTime > TotalExposureTime))
    {
        xil_printf("[ERROR] SC035HGS failed to set HDR exposure tme, invalid args (HDR Exposure Time: %u, Total Exposure Time: %u)\n", HDRExposureTime, TotalExposureTime);
        return XST_FAILURE;
    }

    Status = Set_Reg(InstancePtr, REG_HDR_EXPOSURE_TIME_HIGH_ADDR, (HDRExposureTime >> 8) & 0xff) | Set_Reg(InstancePtr, REG_HDR_EXPOSURE_TIME_LOW_ADDR, HDRExposureTime & 0xff);
    if(Status != XST_SUCCESS)
    {
        xil_printf("[ERROR] SC035HGS failed to set HDR exposure time\n");
        return Status;
    }

    return XST_SUCCESS;
}


/**
 * @brief 复位摄像头
 * @param InstancePtr    摄像头句柄
*/
u32 SC035HGS_Reset(Camera_t *InstancePtr)
{
    return Write_Regs(InstancePtr, REGS_SOFTWARE_RESET);
}

/**
 * @brief 获取摄像头驱动芯片序列化
 * @param InstancePtr    摄像头句柄
 * @return chip id
*/
u16 SC035HGS_Get_ChipId(Camera_t *InstancePtr)
{
    return (Get_Reg(InstancePtr, REG_CHIP_ID_HIGH_ADDR) << 8) | Get_Reg(InstancePtr, REG_CHIP_ID_LOW_ADDR);
}

/**
 * @brief 初始化 SC035HGS 摄像头
 * @param InstancePtr 摄像头句柄
 * @return *
*/
u32 SC035HGS_Init(Camera_t *InstancePtr)
{
    u32 Status;

    if(!InstancePtr)
    {
        xil_printf("[ERROR] SC035HGS init failed, invalid args\n");
        return XST_FAILURE;
    }

    /* 初始化摄像头 IIC 句柄 */
    I2Cs_Init(InstancePtr->I2Cs_DeviceId);

    /* 检查摄像头芯片 ID */
    u16 ChipId = SC035HGS_Get_ChipId(InstancePtr);
    if(ChipId != InstancePtr->ChipId)
    {
        xil_printf("[ERROR] Read SC035HGS's chip 0x%04x, but it should be 0x%04x\n", ChipId, InstancePtr->ChipId);
        return XST_FAILURE;
    }

    /* 初始化摄像头寄存器 */
    Status = Write_Regs(InstancePtr, REGS_INIT_640_480_60FPS_24M_XCLK);
    if(Status != XST_SUCCESS)
    {
        xil_printf("[ERROR] SC035HGS's regs init failed\n");
        return Status;
    }

    /* 设置帧尺寸 */
    Status = SC035HGS_Set_FrameSize(InstancePtr, InstancePtr->FrameWidth, InstancePtr->FrameHeight);
    if(Status != XST_SUCCESS)
    {
        xil_printf("[ERROR] SC035HGS frame size set failed\n");
        return Status;
    }

    /* 设置帧率 */
	Status = SC035HGS_Set_Fps(InstancePtr, InstancePtr->Fps);
    if(Status != XST_SUCCESS)
    {
        xil_printf("[ERROR] SC035HGS fps set failed\n");
        return Status;
    }
    
    /* 曝光设置 */
    // 默认曝光时长为帧高度
    Status |= SC035HGS_Set_ExposureMode(InstancePtr, InstancePtr->ExposureMode);
    Status |= SC035HGS_Set_Aec(InstancePtr, InstancePtr->FrameHeight << 4, InstancePtr->FrameHeight << 4);
    if(Status != XST_SUCCESS)
    {
        xil_printf("[ERROR] SC035HGS aec set failed\n");
        return Status;
    }

    /* BLC */
    Status = SC035HGC_Set_Blc(InstancePtr, &InstancePtr->BLC_Args);
    

    return XST_SUCCESS;
}
