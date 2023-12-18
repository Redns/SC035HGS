#include "sc035hgs.h"

/**
 * @brief �������Ĵ���
 * @param camera    ����ͷ���
 * @param reg_addr  �Ĵ�����ַ
 * @return �Ĵ���ֵ
*/
static uint8_t get_reg(camera_t *camera, uint16_t reg_addr)
{
	return I2Cs_ReadReg(camera->slv_addr, reg_addr);
}


/**
 * @brief д�����Ĵ���
 * @param camera    ����ͷ���
 * @param reg_addr  �Ĵ�����ַ
 * @param mask      ���루��Ӧ BIT Ϊ 1 ���޸ģ�
 * @param value     ��д���ֵ
 * @return д��ɹ����� XST_SUCCESS�����򷵻� XST_FAILURE
*/
static s32 set_reg(camera_t *camera, uint16_t reg_addr, uint8_t value)
{
	return I2Cs_WriteReg(camera->slv_addr, reg_addr, value);
}


static s32 set_reg_best_effort(camera_t *camera, uint16_t reg_addr, uint8_t value, uint8_t max_try_nums)
{
    while(max_try_nums--)
    {
        if(set_reg(camera, reg_addr, value) == XST_SUCCESS)
        {
            return XST_SUCCESS;
        }

        xil_printf("[WARN] Do something to reset i2c module...\n");

        usleep(1 * 1000);
    }
    return XST_FAILURE;
}


/**
 * @brief д�����Ĵ����������
 * @param camera    ����ͷ���
 * @param reg_addr  �Ĵ�����ַ
 * @param offset    �Ĵ�������ƫ��
 * @param length    �Ĵ�������д����������λΪ��λ���ɵ�λ����λ��
 * @param value     ��д���ֵ
 * @return �ɹ����� XST_SUCCESS�����򷵻� XST_FAILURE
*/
static s32 set_reg_bits(camera_t *camera, uint16_t reg_addr, uint8_t offset, uint8_t length, uint8_t value)
{
    uint8_t origin_value;

    // ��ȡ�Ĵ���ԭʼֵ
    origin_value = I2Cs_ReadReg(camera->slv_addr, reg_addr);

    // �޸ļĴ�����Ӧ����λ
    uint8_t mask = ((1 << length) - 1) << offset;
    value = (origin_value & ~mask) | ((value << offset) & mask);

    // д�Ĵ���
    return I2Cs_WriteReg(camera->slv_addr, reg_addr, value);
}


/**
 * @brief д����Ĵ���
 * @param camera            ����ͷ���
 * @param reg_value_pairs   �Ĵ�����ֵ��
 * @return *
*/
static s32 write_regs(camera_t *camera, const RegValuePair *reg_value_pairs)
{
    u32 i = 0;
    while(reg_value_pairs[i].Addr != REG_NULL_ADDR)
    {
        if(reg_value_pairs[i].Addr == REG_DELAY_ADDR)
        {
            // ��ʱ
            usleep(reg_value_pairs[i].Value * 1000);
            xil_printf("[INFO] Delay %u ms\n", reg_value_pairs[i].Value);
        }
        else
        {
            if(set_reg_best_effort(camera, reg_value_pairs[i].Addr, reg_value_pairs[i].Value, MAX_SET_REG_NUMS) != XST_SUCCESS)
            {
                xil_printf("[ERROR] Failed to Write reg {0x%04x} << 0x%02x\n", reg_value_pairs[i].Addr, reg_value_pairs[i].Value);
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


/** // TODO
 * @brief �������
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
        // ��������Ϊ 4
        set_agc(camera, 4);
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
    set_reg(camera, REG_SLEEP_MODE_CTRL_ADDR, enable ? REG_SLEEP_MODE_ENABLE : REG_SLEEP_MODE_DISABLE);
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

    return ((chip_id_high << 8) & 0xff00) | (chip_id_low & 0x00ff);
}


/**
 * @brief ��ʼ�� SC035HGS ����ͷ
 * @param camera ����ͷ���
 * @return *
*/
s32 sc035hgs_init(camera_t *camera)
{
    // ��ʼ������ͷ�ӻ���ַ
    // ZYNQ PS IIC д��ַ������һλ��������д��ַ����������Ҫʹ�� SLAVE_ADDR << 1
    camera->slv_addr = SLAVE_ADDR;

    // ��ʼ������ͷ IIC ���
    #if IIC_PS_ENABLE
        camera->i2c_sclk_frq = IIC_FRQ_HZ;
        PS_IIC_Init(&camera->i2c_instance_ptr, camera->i2c_device_id, camera->i2c_sclk_frq);
    #else
        I2Cs_Init(camera->i2c_device_id);
    #endif

    // �������ͷ ID
    xil_printf("[INFO] Checking camera's chip id...\n");

    uint16_t chip_id = get_chip_id(camera);
    if(chip_id != CHIP_ID)
    {
        xil_printf("[ERROR] Read camera's chip 0x%04x, but it should be 0x%04x\n", chip_id, CHIP_ID);
        return XST_FAILURE;
    }

    xil_printf("[INFO] Success to check camera's chip id\n");

    // ��ʼ������ͷ��������
    camera->reset = reset;
    camera->set_sleep_mode = set_sleep_mode;
    camera->set_agc = set_agc;
    camera->set_aec = set_aec;
    camera->set_blc = set_blc;
    camera->set_hmirror = set_hmirror;
    camera->set_vflip = set_vflip;
    camera->set_increment_pattern = set_increment_pattern;
    camera->get_chip_id = get_chip_id;

    // ��ʼ������ͷ�Ĵ���
    xil_printf("[INFO] Configing camera's regs...\n");
    if(write_regs(camera, REGS_INIT_640_480_50FPS_24M_XCLK) != XST_SUCCESS)
    {
        xil_printf("[ERROR] Failed to config camera's regs\n");
        return XST_FAILURE;
    }
    xil_printf("[INFO] Success to config camera's regs\n");

    return XST_SUCCESS;
}
