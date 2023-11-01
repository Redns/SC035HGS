#include "sc035hgs.h"

/**
 * @brief �������Ĵ���
 * @param camera    ����ͷ���
 * @param reg_addr  �Ĵ�����ַ
 * @return �Ĵ���ֵ
*/
static uint8_t get_reg(camera_t *camera, uint16_t reg_addr)
{
    return AXI_IIC_Read_Reg(camera->instance, camera->slv_addr, reg_addr);
}


/**
 * @brief д�����Ĵ���
 * @param camera    ����ͷ���
 * @param reg_addr  �Ĵ�����ַ
 * @param mask      ���루��Ӧ BIT Ϊ 1 ���޸ģ�
 * @param value     ��д���ֵ
 * @return *
*/
static void set_reg(camera_t *camera, uint16_t reg_addr, uint8_t value)
{
    AXI_IIC_Write_Reg(camera->instance, camera->slv_addr, reg_addr, value);
}


/**
 * @brief д�����Ĵ����������
 * @param camera    ����ͷ���
 * @param reg_addr  �Ĵ�����ַ
 * @param offset    �Ĵ�������ƫ��
 * @param length    �Ĵ�������д����������λΪ��λ���ɵ�λ����λ��
 * @param value     ��д���ֵ
 * @return *
*/
static void set_reg_bits(camera_t *camera, uint16_t reg_addr, uint8_t offset, uint8_t length, uint8_t value)
{
    uint8_t ret = AXI_IIC_Read_Reg(camera->instance, camera->slv_addr, reg_addr);
    uint8_t mask = ((1 << length) - 1) << offset;
    value = (ret & ~mask) | ((value << offset) & mask);
    AXI_IIC_Write_Reg(camera->instance, camera->slv_addr, reg_addr, value);
}


/**
 * @brief д����Ĵ���
 * @param camera            ����ͷ���
 * @param reg_value_pairs   �Ĵ�����ֵ��
 * @return *
*/
static void write_regs(camera_t *camera, const RegValuePair *reg_value_pairs)
{
    int i = 0;
    while(reg_value_pairs[i].Addr != REG_NULL_ADDR)
    {
        if(reg_value_pairs[i].Addr == REG_DELAY_ADDR)
        {
            usleep(reg_value_pairs[i].Value * 1000);
        }
        else
        {
            AXI_IIC_Write_Reg(camera->instance, camera->slv_addr, reg_value_pairs[i].Addr, reg_value_pairs[i].Value);
        }
    }
}


/**
 * @brief ˮƽ����
 * @param camera    ����ͷ���
 * @param enable    ˮƽ����ʹ��
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
 * @brief ��ֱ��ת
 * @param camera    ����ͷ���
 * @param enable    ʹ�ܿ���
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
 * @brief ����ģʽ
 * @param camera    ����ͷ���
 * @param enable    ʹ�ܿ���
 * @return *
*/
static void set_increment_pattern(camera_t *camera, int enable)
{
    if(enable)
    {
        // ʹ�ܻҶȽ������ģʽ
        set_reg_bits(camera, REG_INCREMENT_PATTERN_ENABLE_ADDR, 3, 1, 0x1);
        // ʹ���Զ� BLC
        set_reg_bits(camera, REG_BLC_ENABLE_ADDR, 0, 1, 0x1);
        set_reg_bits(camera, REG_BLC_MODE_CTRL_ADDR, 6, 1, 0x1);
        // TODO ��������Ϊ 4
        set_reg_bits(camera, REG_DIGITAL_COARSE_GAIN_ADDR, 0, 2, DIGITAL_COARSE_GAIN_X4);
    }
    else
    {
        set_reg_bits(camera, REG_INCREMENT_PATTERN_ENABLE_ADDR, 3, 1, 0x0);
    }
}


/**
 * @brief �����ߣ�ͨ���޸ļĴ������ߣ���ʱ�Կɷ��ʴ������Ĵ�����
 * @param camera    ����ͷ���
 * @param enable    ʹ�ܿ���
 * @return *
*/
static void set_sleep_mode(camera_t *camera, int enable)
{
    set_reg(camera, REG_SLEEP_MODE_CTRL_ADDR, enable ? 0x0 : 0x1);
}


/**
 * @brief BLC ����
 * @param camera    ����ͷ���
 * @param args      BLC ����
 * @return *
*/
static void set_blc(camera_t *camera, blc_args *args)
{
    // ʹ�� BLC
    set_reg_bits(camera, REG_BLC_ENABLE_ADDR, 0, 1, args->enable ? 0x1 : 0x0);
    // ģʽѡ��
    set_reg_bits(camera, REG_BLC_MODE_CTRL_ADDR, 6, 1, args->auto_mode_enable ? 0x1 : 0x0);
    // TODO ͨ��ѡ��
    // ����Ŀ��ֵ
    set_reg_bits(camera, REG_BLC_TARGET_VALUE_HIGH_ADDR, 0, 5, args->target_value >> 8);
    set_reg_bits(camera, REG_BLC_TARGET_VALUE_LOW_ADDR, 0, 8, args->target_value & 0xff);
}

/**
 * TODO �������
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
 * @brief AEC �ع�ʱ������
 * @param camera                ����ͷ���
 * @param total_exposure_time   ���ع�ʱ�䣨�� 1/16 ��Ϊ��λ��
 * @param hdr_exposure_time     HDR �ع�ʱ�䣨�� 1/16 ��Ϊ��λ��Normal ģʽ����Ч��
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
 * @brief ��λ����ͷ
 * @param camera    ����ͷ���
*/
static void reset(camera_t *camera)
{
    write_regs(camera, REGS_SOFTWARE_RESET);
}


/**
 * @brief ��ȡ����ͷ����оƬ���л�
 * @param camera    ����ͷ���
 * @return chip id
*/
static uint16_t get_chip_id(camera_t *camera)
{
    uint16_t chip_id_high = get_reg(camera, REG_CHIP_ID_HIGH_ADDR);
    uint16_t chip_id_low = get_reg(camera, REG_CHIP_ID_LOW_ADDR);
    return (chip_id_high & 0xff00) | (chip_id_low & 0x00ff);
}


/**
 * @brief �������ͷ
 * @param ����ͷ AXI_IIC �豸 ID
 * @return ����ͷ AXI_IIC �豸���
*/
static XIic* detect(uint16_t device_id)
{
    return AXI_IIC_Init(device_id);
}


/**
 * @brief ��ʼ�� SC035HGS ����ͷ
 * @param camera    ����ͷ���
 * @return *
*/
void sc035hgs_init(camera_t *camera, uint16_t device_id)
{
    // ��ʼ������ͷ��Ϣ
    camera->slv_addr = SLAVE_ADDR;
    camera->instance = detect(device_id);
    camera->chip_id = get_chip_id(camera);
    // ��ʼ������ͷ��������
    camera->reset = reset;
    camera->get_chip_id = get_chip_id;
    camera->set_sleep_mode = set_sleep_mode;
    camera->set_agc = set_agc;
    camera->set_aec = set_aec;
    camera->set_blc = set_blc;
    camera->set_hmirror = set_hmirror;
    camera->set_vflip = set_vflip;
    camera->set_increment_pattern = set_increment_pattern;
    // ��ʼ������ͷ�Ĵ���
    write_regs(camera, REGS_INIT_640_480_60FPS_24M_XCLK);
}
