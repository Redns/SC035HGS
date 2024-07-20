# sc_camera

`SC035HGS` 摄像头驱动，功能如下

- DVP 接口输出
- 视频尺寸、帧率可调（640×480@180fps）
- 支持水平、垂直镜像
- 支持 HDR，曝光时间可调
- 支持测试模式（渐变灰度条）

驱动包括 `i2c`、`i2cs` 和 `sc035hgs` 三部分

- `i2c`：I2C 驱动相关宏定义
- `i2cs`：I2C 软件驱动
- `sc035hgs`：SC035HGS 摄像头驱动

## 1 移植

该驱动基于 Xilinx Zynq 平台开发，在其他平台使用需要进行修改，如果不需要使用本库提供的 `I2C` 软件驱动，则仅需要修改 `sc035hgs.c` 中的寄存器读写相关函数

```c
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
```

若使用本库提供的 `I2C` 软件驱动，则首先修改 `i2cs.h` 中的宏定义

```c
#define SDA_IN()                    XGpio_SetDataDirection(&GPIO_I2Cs, 2, 0x1)      
#define SDA_OUT()                   XGpio_SetDataDirection(&GPIO_I2Cs, 2, 0x0)

#define SCL_WRITE_H()               XGpio_DiscreteWrite(&GPIO_I2Cs, 1, 0x1)
#define SCL_WRITE_L()               XGpio_DiscreteWrite(&GPIO_I2Cs, 1, 0x0)
#define SDA_WRITE_H()               XGpio_DiscreteWrite(&GPIO_I2Cs, 2, 0x1)
#define SDA_WRITE_L()               XGpio_DiscreteWrite(&GPIO_I2Cs, 2, 0x0)
```

然后修改 `i2cs.c` 中的初始化函数，此处的 `DeviceId` 是 `XGpio` 模块 `ID`，可根据实际情况修改相关参数定义

```c
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
    XGpio_DiscreteWrite(&GPIO_I2Cs, 1, 0x1);
    XGpio_DiscreteWrite(&GPIO_I2Cs, 2, 0x1);
}
```

# 2 如何使用

> 注意：本驱动库不包含 PWDN 引脚配置，摄像头工作时需要保证 PWDN 引脚拉高

```c
/* 摄像头信息 */
#define CAMERA_FPS								10
#define CAMERA_ADDR								0x30
#define CAMERA_CHIP_ID							0x31
#define CAMERA_FRAME_WIDTH						640
#define CAMERA_FRAME_HEIGHT						480
#define CAMERA_XCLK_FREQ						23805920
#define CAMERA_EXPOSURE_MODE					EXPOSURE_HDR_MODE
#define CAMERA_BLC_ENABLE						0x1
#define CAMERA_BLC_MODE							BLC_MODE_AUTO

int main()
{
    Camera_t Camera;

    /* 初始化摄像头信息 */
    Camera.Fps = CAMERA_FPS;
    Camera.XclkFreq = CAMERA_XCLK_FREQ;
    Camera.FrameWidth = CAMERA_FRAME_WIDTH;
    Camera.FrameHeight = CAMERA_FRAME_HEIGHT;
    Camera.SlaveAddr = CAMERA_ADDR;
    Camera.ChipId = CAMERA_CHIP_ID;
    Camera.I2Cs_DeviceId = CAMERA_I2CS_DEVICE_ID;
    Camera.ExposureMode = CAMERA_EXPOSURE_MODE;
    Camera.BLC_Args.Enable = CAMERA_BLC_ENABLE;
    Camera.BLC_Args.Mode = CAMERA_BLC_MODE;

    /* 初始化摄像头 */
    Status = SC035HGS_Init(&Camera);
    if(Status != XST_SUCCESS)
    {
        xil_printf("[ERROR] SC035HGS init failed\n");
        return Status;
    }
    xil_printf("[INFO] SC035HGS init successfully\n");

    return 0;
}

```