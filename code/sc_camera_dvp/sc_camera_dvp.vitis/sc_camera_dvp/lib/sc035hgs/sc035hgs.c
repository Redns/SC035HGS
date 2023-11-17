#include "sc035hgs.h"

/**
 * @brief 读单个寄存器
 * @param camera    摄像头句柄
 * @param reg_addr  寄存器地址
 * @return 寄存器值
*/
static uint8_t get_reg(camera_t *camera, uint16_t reg_addr)
{
    #ifdef PS_IIC
        return PS_IIC_Read_Reg(camera->ps_iic_inst, camera->slv_addr, reg_addr);
    #else
        return AXI_IIC_Read_Reg(camera->axi_iic_inst, camera->slv_addr, reg_addr);
    #endif
}


/**
 * @brief 写单个寄存器
 * @param camera    摄像头句柄
 * @param reg_addr  寄存器地址
 * @param mask      掩码（对应 BIT 为 1 则修改）
 * @param value     待写入的值
 * @return *
*/
static void set_reg(camera_t *camera, uint16_t reg_addr, uint8_t value)
{
    #ifdef PS_IIC
        PS_IIC_Write_Reg(camera->ps_iic_inst, camera->slv_addr, reg_addr, value);
    #else
        AXI_IIC_Write_Reg(camera->axi_iic_inst, camera->slv_addr, reg_addr, value);
    #endif
}


/**
 * @brief 写单个寄存器多个比特
 * @param camera    摄像头句柄
 * @param reg_addr  寄存器地址
 * @param offset    寄存器比特偏移
 * @param length    寄存器比特写入数量（以位为单位，由低位至高位）
 * @param value     待写入的值
 * @return *
*/
static void set_reg_bits(camera_t *camera, uint16_t reg_addr, uint8_t offset, uint8_t length, uint8_t value)
{
    #ifdef PS_IIC
        uint8_t ret = PS_IIC_Read_Reg(camera->ps_iic_inst, camera->slv_addr, reg_addr);
        uint8_t mask = ((1 << length) - 1) << offset;
        value = (ret & ~mask) | ((value << offset) & mask);
        PS_IIC_Write_Reg(camera->ps_iic_inst, camera->slv_addr, reg_addr, value);
    #else
        uint8_t ret = AXI_IIC_Read_Reg(camera->axi_iic_inst, camera->slv_addr, reg_addr);
        uint8_t mask = ((1 << length) - 1) << offset;
        value = (ret & ~mask) | ((value << offset) & mask);
        AXI_IIC_Write_Reg(camera->axi_iic_inst, camera->slv_addr, reg_addr, value);
    #endif
}


/**
 * @brief 写多个寄存器
 * @param camera            摄像头句柄
 * @param reg_value_pairs   寄存器键值对
 * @return *
*/
static void write_regs(camera_t *camera, const RegValuePair *reg_value_pairs)
{
    int i = 0;
    while(reg_value_pairs[i].Addr != REG_NULL_ADDR)
    {
        if(reg_value_pairs[i].Addr == REG_DELAY_ADDR)
        {
            xil_printf("[INFO] Delay %u ms\n", reg_value_pairs[i].Value);
            usleep(reg_value_pairs[i].Value * 1000);
        }
        else
        {
            #ifdef PS_IIC
                PS_IIC_Write_Reg(camera->ps_iic_inst, camera->slv_addr, reg_value_pairs[i].Addr, reg_value_pairs[i].Value);
            #else
                AXI_IIC_Write_Reg(camera->axi_iic_inst, camera->slv_addr, reg_value_pairs[i].Addr, reg_value_pairs[i].Value);
            #endif
            xil_printf("[INFO] Write camera's reg {0x%x} << 0x%x\n", reg_value_pairs[i].Addr, reg_value_pairs[i].Value);
        }
        i++;
    }
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
        // TODO 设置增益为 4
        set_reg_bits(camera, REG_DIGITAL_COARSE_GAIN_ADDR, 0, 2, DIGITAL_COARSE_GAIN_X4);
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
    set_reg(camera, REG_SLEEP_MODE_CTRL_ADDR, enable ? 0x0 : 0x1);
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
 * TODO 增益控制
*/
static void set_agc(camera_t *camera, int gain)
{
    // int ret = 0;
    // uint32_t coarse_gain, fine_gain, fine_again_reg_v, coarse_gain_reg_v;

    // if (gain < 0x20) {
    //     WRITE_REG_OR_RETURN(0x3314, 0x3a);
    //     WRITE_REG_OR_RETURN(0x3317, 0x20);
    // } else {
    //     WRITE_REG_OR_RETURN(0x3314, 0x44);
    //     WRITE_REG_OR_RETURN(0x3317, 0x0f);
    // }

    // // gain = 0x20
    // // fine_gain = 0x20 - 16 = 0x10
    // // coarse_gain = 0x03
    // // fine_again_reg_v = 0x10
    // // coarse_gain_reg_v = 0x03
    // fine_again_reg_v = 
    // if (gain < 0x20) { /*1x ~ 2x*/
    //     fine_gain = gain - 16;
    //     coarse_gain = 0x03;
    //     fine_again_reg_v = ((0x01 << 4) & 0x10) |
    //         (fine_gain & 0x0f);
    //     coarse_gain_reg_v = coarse_gain  & 0x1F;
    // } else if (gain < 0x40) { /*2x ~ 4x*/
    // // gain = 0x40
    // // fine_gain = (0x40 >> 1) - 16 = 0x10
    // // coarse_gain = 0x7
    // // fine_again_reg_v = 0x10
    // // coarse_gain_reg_v = 0x7
    //     fine_gain = (gain >> 1) - 16;
    //     coarse_gain = 0x7;
    //     fine_again_reg_v = ((0x01 << 4) & 0x10) |
    //         (fine_gain & 0x0f);
    //     coarse_gain_reg_v = coarse_gain  & 0x1F;
    // } else if (gain < 0x80) { /*4x ~ 8x*/
    //     fine_gain = (gain >> 2) - 16;
    //     coarse_gain = 0xf;
    //     fine_again_reg_v = ((0x01 << 4) & 0x10) |
    //         (fine_gain & 0x0f);
    //     coarse_gain_reg_v = coarse_gain  & 0x1F;
    // } else { /*8x ~ 16x*/
    //     fine_gain = (gain >> 3) - 16;
    //     coarse_gain = 0x1f;
    //     fine_again_reg_v = ((0x01 << 4) & 0x10) |
    //         (fine_gain & 0x0f);
    //     coarse_gain_reg_v = coarse_gain  & 0x1F;
    // }

    // WRITE_REG_OR_RETURN(SC031GS_GAIN_CTRL_COARSE_REG, coarse_gain_reg_v);
    // WRITE_REG_OR_RETURN(SC031GS_GAIN_CTRL_FINE_REG, fine_again_reg_v);
    
    // return ret;
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
    return (get_reg(camera, REG_CHIP_ID_HIGH_ADDR) & 0xff00) | (get_reg(camera, REG_CHIP_ID_LOW_ADDR) & 0x00ff);
}


/**
 * @brief 初始化 SC035HGS 摄像头
 * @param camera    摄像头句柄
 * @return *
*/
void sc035hgs_init(camera_t *camera, uint16_t device_id)
{
    // 初始化摄像头信息
    camera->slv_addr = SLAVE_ADDR;
    xil_printf("[INFO] Start to get camera's id...\n");
    #ifdef PS_IIC
        camera->ps_iic_inst = PS_IIC_Init(device_id, 400000);
    #else
        camera.axi_iic_inst = AXI_IIC_Init(device_id);
    #endif
    camera->chip_id = get_chip_id(camera);
    xil_printf("[INFO] Camera's id is %u\n", camera->chip_id);
    // 初始化摄像头操作函数
    camera->reset = reset;
    camera->set_sleep_mode = set_sleep_mode;
    camera->set_agc = set_agc;
    camera->set_aec = set_aec;
    camera->set_blc = set_blc;
    camera->set_hmirror = set_hmirror;
    camera->set_vflip = set_vflip;
    camera->set_increment_pattern = set_increment_pattern;
    // 初始化摄像头寄存器
    xil_printf("[INFO] Start to config camera's regs...\n");
    write_regs(camera, REGS_INIT_640_480_50FPS_24M_XCLK);
    xil_printf("[SUCCESS] Config camera's regs done\n");
}
