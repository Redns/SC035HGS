#include "sc035hgs.h"

/**
 * @brief 读单个寄存器
 * @param camera    摄像头句柄
 * @param reg_addr  寄存器地址
 * @return 寄存器值
*/
static uint8_t get_reg(camera_t *camera, uint16_t reg_addr)
{
	return I2Cs_ReadReg(camera->slv_addr, reg_addr);
}


/**
 * @brief 写单个寄存器
 * @param camera    摄像头句柄
 * @param reg_addr  寄存器地址
 * @param mask      掩码（对应 BIT 为 1 则修改）
 * @param value     待写入的值
 * @return 写入成功返回 XST_SUCCESS，否则返回 XST_FAILURE
*/
static s32 set_reg(camera_t *camera, uint16_t reg_addr, uint8_t value)
{
	return I2Cs_WriteReg(camera->slv_addr, reg_addr, value);
}


/**
 * @brief 写单个寄存器多个比特
 * @param camera    摄像头句柄
 * @param reg_addr  寄存器地址
 * @param offset    寄存器比特偏移
 * @param length    寄存器比特写入数量（以位为单位，由低位至高位）
 * @param value     待写入的值
 * @return 成功返回 XST_SUCCESS，否则返回 XST_FAILURE
*/
static s32 set_reg_bits(camera_t *camera, uint16_t reg_addr, uint8_t offset, uint8_t length, uint8_t value)
{
    uint8_t origin_value;

    // 获取寄存器原始值
    origin_value = I2Cs_ReadReg(camera->slv_addr, reg_addr);

    // 修改寄存器相应比特位
    uint8_t mask = ((1 << length) - 1) << offset;
    value = (origin_value & ~mask) | ((value << offset) & mask);

    // 写寄存器
    return I2Cs_WriteReg(camera->slv_addr, reg_addr, value);
}


/**
 * @brief 写多个寄存器
 * @param camera            摄像头句柄
 * @param reg_value_pairs   寄存器键值对
 * @return *
*/
static s32 write_regs(camera_t *camera, const RegValuePair *reg_value_pairs)
{
    u32 i = 0;
    while(reg_value_pairs[i].Addr != REG_NULL_ADDR)
    {
        if(reg_value_pairs[i].Addr == REG_DELAY_ADDR)
        {
            usleep(reg_value_pairs[i].Value * 1000);
        }
        else
        {
            if(set_reg(camera, reg_value_pairs[i].Addr, reg_value_pairs[i].Value) != XST_SUCCESS)
            {
                xil_printf("[ERROR] Failed to Write reg {0x%04x} << 0x%02x\n", reg_value_pairs[i].Addr, reg_value_pairs[i].Value);
                return XST_FAILURE;
            }
            else
            {
                xil_printf("[INFO] Success to write reg {0x%04x} << 0x%02x\n", reg_value_pairs[i].Addr, reg_value_pairs[i].Value);
            }
        }
        i++;
    }

    return XST_SUCCESS;
}


/**
 * @brief 水平镜像
 * @param camera    摄像头句柄
 * @param enable    水平镜像使能
 * @return *
*/
static void set_hmirror(camera_t *camera, int enable)
{
    if(enable)
    {
        set_reg_bits(camera, REG_MIRROR_ENABLE_ADDR, 1, 2, 0x3);
    }
    else
    {
        set_reg_bits(camera, REG_MIRROR_ENABLE_ADDR, 1, 2, 0x0);
    }
}


/**
 * @brief 垂直翻转
 * @param camera    摄像头句柄
 * @param enable    使能控制
 * @return *
*/
static void set_vflip(camera_t *camera, int enable)
{
    if(enable)
    {
        set_reg_bits(camera, REG_FLIP_ENABLE_ADDR, 5, 2, 0x3);
    }
    else
    {
        set_reg_bits(camera, REG_FLIP_ENABLE_ADDR, 5, 2, 0x0);
    }
}


/** // TODO
 * @brief 增益控制
 * @param
*/
static s32 set_agc(camera_t *camera, int gain)
{
    s32 status;
    // uint32_t coarse_gain, fine_gain, fine_again_reg_v, coarse_gain_reg_v;

    if(gain < 2)
    {
        status = set_reg(camera, 0x3314, 0x1e);
        set_reg(camera, 0x3317, 0x1b);
        set_reg(camera, 0x3631, 0x58);
        set_reg(camera, 0x3630, 0x4a);
    }
    else if(gain < 4)
    {
        set_reg(camera, 0x3314, 0x6f);
        set_reg(camera, 0x3317, 0x10);
        set_reg(camera, 0x3631, 0x48);
        set_reg(camera, 0x3630, 0x4c);
    }
    else
    {
        set_reg(camera, 0x3314, 0x76);
        set_reg(camera, 0x3317, 0x15);
        set_reg(camera, 0x3631, 0x48);
        set_reg(camera, 0x3630, 0x4c);
    }

    return status;
}


/**
 * @brief 测试模式
 * @param camera    摄像头句柄
 * @param enable    使能控制
 * @return *
*/
static void set_increment_pattern(camera_t *camera, int enable)
{
    if(enable)
    {
        // 使能灰度渐变测试模式
        set_reg_bits(camera, REG_INCREMENT_PATTERN_ENABLE_ADDR, 3, 1, 0x1);
        // 使能自动 BLC
        set_reg_bits(camera, REG_BLC_ENABLE_ADDR, 0, 1, 0x1);
        set_reg_bits(camera, REG_BLC_MODE_CTRL_ADDR, 6, 1, 0x1);
        // 设置增益为 4
        set_agc(camera, 4);
    }
    else
    {
        set_reg_bits(camera, REG_INCREMENT_PATTERN_ENABLE_ADDR, 3, 1, 0x0);
    }
}


/**
 * @brief 软休眠（通过修改寄存器休眠，此时仍可访问传感器寄存器）
 * @param camera    摄像头句柄
 * @param enable    使能控制
 * @return *
*/
static void set_sleep_mode(camera_t *camera, int enable)
{
    set_reg(camera, REG_SLEEP_MODE_CTRL_ADDR, enable ? REG_SLEEP_MODE_ENABLE : REG_SLEEP_MODE_DISABLE);
}


/**
 * @brief BLC 设置
 * @param camera    摄像头句柄
 * @param args      BLC 参数
 * @return *
*/
static void set_blc(camera_t *camera, blc_args *args)
{
    // 使能 BLC
    set_reg_bits(camera, REG_BLC_ENABLE_ADDR, 0, 1, args->enable ? 0x1 : 0x0);
    // 模式选择
    set_reg_bits(camera, REG_BLC_MODE_CTRL_ADDR, 6, 1, args->auto_mode_enable ? 0x1 : 0x0);
    // TODO 通道选择
    // 设置目标值
    set_reg_bits(camera, REG_BLC_TARGET_VALUE_HIGH_ADDR, 0, 5, args->target_value >> 8);
    set_reg_bits(camera, REG_BLC_TARGET_VALUE_LOW_ADDR, 0, 8, args->target_value & 0xff);
}


/**
 * @brief AEC 曝光时间设置
 * @param camera                摄像头句柄
 * @param total_exposure_time   总曝光时间（以 1/16 行为单位）
 * @param hdr_exposure_time     HDR 曝光时间（以 1/16 行为单位，Normal 模式下无效）
 * @return *
*/
static void set_aec(camera_t *camera, uint16_t total_exposure_time, uint16_t hdr_exposure_time)
{
    set_reg(camera, REG_AEC_TOTAL_EXPOSURE_TIME_HIGH_ADDR, (total_exposure_time >> 8) & 0xff);
    set_reg(camera, REG_AEC_TOTAL_EXPOSURE_TIME_LOW_ADDR, total_exposure_time & 0xff);
    if(camera->exposure_mode == EXPOSURE_HDR_MODE)
    {
        set_reg(camera, REG_HDR_EXPOSURE_TIME_HIGH_ADDR, (hdr_exposure_time >> 8) & 0xff);
        set_reg(camera, REG_HDR_EXPOSURE_TIME_LOW_ADDR, hdr_exposure_time & 0xff);
    }
}


/**
 * @brief 复位摄像头
 * @param camera    摄像头句柄
*/
static void reset(camera_t *camera)
{
    write_regs(camera, REGS_SOFTWARE_RESET);
}


/**
 * @brief 获取摄像头驱动芯片序列化
 * @param camera    摄像头句柄
 * @return chip id
*/
static uint16_t get_chip_id(camera_t *camera)
{
    uint16_t chip_id_high = get_reg(camera, REG_CHIP_ID_HIGH_ADDR);
    uint16_t chip_id_low = get_reg(camera, REG_CHIP_ID_LOW_ADDR);

    return ((chip_id_high << 8) & 0xff00) | (chip_id_low & 0x00ff);
}


/**
 * @brief 初始化 SC035HGS 摄像头
 * @param camera 摄像头句柄
 * @return *
*/
s32 sc035hgs_init(camera_t *camera)
{
    // 初始化摄像头从机地址
    // ZYNQ PS IIC 写地址会左移一位，若驱动写地址不左移则需要使用 SLAVE_ADDR << 1
    camera->slv_addr = SLAVE_ADDR;

    // 初始化摄像头 IIC 句柄
    #if IIC_PS_ENABLE
        camera->i2c_sclk_frq = IIC_FRQ_HZ;
        PS_IIC_Init(&camera->i2c_instance_ptr, camera->i2c_device_id, camera->i2c_sclk_frq);
    #else
        I2Cs_Init(camera->i2c_device_id);
    #endif

    // 检查摄像头 ID
    uint16_t chip_id = get_chip_id(camera);
    if(chip_id != CHIP_ID)
    {
        xil_printf("[ERROR] Read camera's chip 0x%04x, but it should be 0x%04x\n", chip_id, CHIP_ID);
        return XST_FAILURE;
    }

    // 初始化摄像头操作函数
    camera->reset = reset;
    camera->set_sleep_mode = set_sleep_mode;
    camera->set_agc = set_agc;
    camera->set_aec = set_aec;
    camera->set_blc = set_blc;
    camera->set_hmirror = set_hmirror;
    camera->set_vflip = set_vflip;
    camera->set_increment_pattern = set_increment_pattern;
    camera->get_chip_id = get_chip_id;

    // 初始化摄像头寄存器
    if(write_regs(camera, REGS_INIT_640_480_50FPS_24M_XCLK) != XST_SUCCESS)
    {
        xil_printf("[ERROR] SC035HGS's regs init failed\n");
        return XST_FAILURE;
    }

    return XST_SUCCESS;
}
