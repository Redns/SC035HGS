#ifndef __SC035HGS_H__
#define __SC035HGS_H__

#include <malloc.h>
#include "sleep.h"
#include "axi_iic.h"

#define ENABLE                                  1
#define DISABLE                                 0

/* ???????? */
#define SLAVE_ADDR                              0x30        // ?????????????DVP ????????????
#define REG_CHIP_ID_HIGH_ADDR                   0x3107      // CHIP ID
#define REG_CHIP_ID_LOW_ADDR                    0x3108

/* ????¦Ë & ???? */
#define REG_SOFTWARE_RESET_ADDR                 0x0103      // ????¦Ë??§Õ 1 ??¦Ë??
#define REG_SLEEP_MODE_CTRL_ADDR                0x0100      // ????????§Õ 0 ?????

/* ??????? */
#define REG_FRAME_WIDTH_HIGH_ADDR               0x3208      // ???????????????¦Ë??
#define REG_FRAME_WIDTH_LOW_ADDR                0x3209
#define REG_FRAME_HEIGHT_HIGH_ADDR              0x320a      // ????????????¦Ë??
#define REG_FRAME_HEIGHT_LOW_ADDR               0x320b
#define REG_FRAME_LINE_WIDTH_HIGH_ADDR          0x320c      // ?§Ô???????? + ??????????
#define REG_FRAME_LINE_WIDTH_LOW_ADDR           0x320d      
#define REG_FRAME_LENGTH_HIGH_ADDR              0x320e      // ????????? + ???????????
#define REG_FRAME_LENGTH_LOW_ADDR               0x320f
#define REG_FRAME_COL_START_HIGH_ADDR           0x3210      // ????????????¦Ë??
#define REG_FRAME_COL_START_LOW_ADDR            0x3211
#define REG_FRAME_ROW_START_HIGH_ADDR           0x3212      // ????????????¦Ë??
#define REG_FRAME_ROW_START_LOW_ADDR            0x3213

/* ?????????? */
#define REG_EXT_EXPOSURE_BLANK_ROWS_ADDR        0x3218      // ???????§à??????????????????????????¦Ë??
#define REG_EXT_EXPOSURE_TRIG_DELAY_ADDR        0x3226      // ??????????????¦Ë??
#define REG_EXT_EXPOSURE_EXP_ROWS_HIGH_ADDR     0x3e01      // ?????????????¦Ë??
#define REG_EXT_EXPOSURE_EXP_ROWS_LOW_ADDR      0x3e02 

/* HDR */
#define REG_HDR_ENABLE_CTRL_ADDR                0x3220      // HDR ??????

/* BLC */
#define REG_BLC_ENABLE_ADDR                     0x3900      // BLC ???
#define REG_BLC_MODE_CTRL_ADDR                  0x3902      // BLC ??????????/?????
#define REG_BLC_CHANNEL_HIGH_ADDR               0x3928      // BLC ??????
#define REG_BLC_CHANNEL_LOW_ADDR                0x3905
#define REG_BLC_TARGET_VALUE_HIGH_ADDR          0x3907      // BLC ????????????????????
#define REG_BLC_TARGET_VALUE_LOW_ADDR           0x3908

/* DVP */
#define REG_DVP_POL_CTRL_ADDR                   0x3d08      // DVP ?????? 

/* AGC */
#define REG_AGC_MODE_CTRL_ADDR                  0x3e03      // AGC ??????
#define REG_AGC_GAIN_MAPPING_HIGH_ADDR          0x3e08      // Gain Mapping ?????????
#define REG_AGC_GAIN_MAPPING_LOW_ADDR           0x3e09
#define REG_DIGITAL_COARSE_GAIN_ADDR            0x3e06      // ??????????
#define REG_DIGITAL_FINE_GAIN_ADDR              0x3e07      // ???????????
#define REG_ANALOG_COARSE_GAIN_ADDR             0x3e08      // ?????????
#define REG_ANALOG_FINE_GAIN_ADDR               0x3e09      // ??????????

/* AEC */
#define REG_AEC_TOTAL_EXPOSURE_TIME_HIGH_ADDR   0x3e01      // ?????????? 1/16 ?????¦Ë??
#define REG_AEC_TOTAL_EXPOSURE_TIME_LOW_ADDR    0x3e02
#define REG_HDR_EXPOSURE_TIME_HIGH_ADDR         0x3e31      // HDR ???????? 1/16 ?????¦Ë??
#define REG_HDR_EXPOSURE_TIME_LOW_ADDR          0x3e32

/* ????? */
#define REG_MIRROR_ENABLE_ADDR                  0x3221      // ??????????Bit[2:1]??
#define REG_FLIP_ENABLE_ADDR                    0x3221      // ??????????Bit[6:5]??

/* ?????? */
#define REG_INCREMENT_PATTERN_ENABLE_ADDR       0x4501      // ???????????

/* AGC ??????? */
// ?????
typedef enum
{
    ANALOG_COARSE_GAIN_X1               =   0x0,
    ANALOG_COARSE_GAIN_X2               =   0x1,
    ANALOG_COARSE_GAIN_X4               =   0x3,
    ANALOG_COARSE_GAIN_X8               =   0x7,
} analog_coarse_gain;

// ?????
typedef enum
{
    ANALOG_FINE_GAIN_X1                 =   0x10,
    ANALOG_FINE_GAIN_1X0625             =   0x11,
    ANALOG_FINE_GAIN_1X125              =   0x12,
    ANALOG_FINE_GAIN_1X1875             =   0x13,
    ANALOG_FINE_GAIN_1X25               =   0x14,
    ANALOG_FINE_GAIN_1X3125             =   0x15,
    ANALOG_FINE_GAIN_1X375              =   0x16,
    ANALOG_FINE_GAIN_1X4375             =   0x17,
    ANALOG_FINE_GAIN_1X5                =   0x18,
    ANALOG_FINE_GAIN_1X5625             =   0x19,
    ANALOG_FINE_GAIN_1X625              =   0x1a,
    ANALOG_FINE_GAIN_1X6875             =   0x1b,
    ANALOG_FINE_GAIN_1X75               =   0x1c,
    ANALOG_FINE_GAIN_1X8125             =   0x1d,
    ANALOG_FINE_GAIN_1X875              =   0x1e,
    ANALOG_FINE_GAIN_1X9375             =   0x1f
} analog_fine_gain;

// ??????
typedef enum
{
    DIGITAL_COARSE_GAIN_X1              =   0x0,
    DIGITAL_COARSE_GAIN_X2              =   0x1,
    DIGITAL_COARSE_GAIN_X4              =   0x3
} digital_coarse_gain;

// ???????
typedef enum
{
    DIGITAL_FINE_GAIN_X1                =   0x80,
    DIGITAL_FINE_GAIN_1X0625            =   0x88,
    DIGITAL_FINE_GAIN_1X125             =   0x90,
    DIGITAL_FINE_GAIN_1X1875            =   0x98,
    DIGITAL_FINE_GAIN_1X25              =   0xa0,
    DIGITAL_FINE_GAIN_1X3125            =   0xa8,
    DIGITAL_FINE_GAIN_1X375             =   0xb0,
    DIGITAL_FINE_GAIN_1X4375            =   0xb8,
    DIGITAL_FINE_GAIN_1X5               =   0xc0,
    DIGITAL_FINE_GAIN_1X5625            =   0xc8,
    DIGITAL_FINE_GAIN_1X625             =   0xd0,
    DIGITAL_FINE_GAIN_1X6875            =   0xd8,
    DIGITAL_FINE_GAIN_1X75              =   0xe0,
    DIGITAL_FINE_GAIN_1X8125            =   0xe8,
    DIGITAL_FINE_GAIN_1X875             =   0xf0,
    DIGITAL_FINE_GAIN_1X9375            =   0xf8
} digital_fine_gain;

/* BLC ???? */
// BLC ??????
typedef enum 
{
    BLC_CHANNEL_OFFSET_8                =   0,
    BLC_CHANNEL_OFFSET_4,
    BLC_CHANNEL_ENABLE_1_OFFSET_8_OR_4,
    BLC_CHANNEL_ENABLE_1
} blc_channel;

// BLC ???¨°???
typedef struct
{
    uint8_t enable;                 // BLC ???
    uint8_t auto_mode_enable;       // ????????
    blc_channel channel;            // ??????
    uint16_t target_value;          // ????
} blc_args;

// ?????
typedef enum 
{
    EXPOSURE_NORMAL_MODE                =   0,
    EXPOSURE_HDR_MODE     
} exposure_mode;

// ??¦Ë??????§Ò?
static const RegValuePair REGS_SOFTWARE_RESET[] = {
	{REG_SOFTWARE_RESET_ADDR, 0x01},
	{REG_DELAY_ADDR, 10},
    {REG_NULL_ADDR, 0x00}
};

// 640*480, xclk=24M, fps=60fps
static const RegValuePair REGS_INIT_640_480_60FPS_24M_XCLK[] = {
	{REG_SLEEP_MODE_CTRL_ADDR, 0x00},                   // ?????????
	{0x36e9, 0x80},
	{0x36f9, 0x80},
	{0x300f, 0x0f},
	{0x3018, 0x1f},
	{0x3019, 0xff},
	{0x301c, 0xb4},
	{0x301f, 0x6c},
	{0x3028, 0x82},
	{0x3200, 0x00},
	{0x3201, 0x00},
	{0x3202, 0x00},
	{0x3203, 0x08},
	{0x3204, 0x02},
	{0x3205, 0x8f},
	{0x3206, 0x01},
	{0x3207, 0xf7},
	{REG_FRAME_WIDTH_HIGH_ADDR, 0x02},                  // ?????0x0280 = 640??
	{REG_FRAME_WIDTH_LOW_ADDR, 0x80},
	{REG_FRAME_HEIGHT_HIGH_ADDR, 0x01},                 // ????0x01e0 = 480??
	{REG_FRAME_HEIGHT_LOW_ADDR, 0xe0},
    {REG_FRAME_LINE_WIDTH_HIGH_ADDR, 0x03},             // ?§Ô???0x036e = 878??
	{REG_FRAME_LINE_WIDTH_LOW_ADDR, 0x6e},
	{REG_FRAME_LENGTH_HIGH_ADDR, 0x04},                 // ?????0x0472 = 1138??
	{REG_FRAME_LENGTH_LOW_ADDR, 0x72},
	{REG_FRAME_COL_START_HIGH_ADDR, 0x00},              // ????????¦Ë??
	{REG_FRAME_COL_START_LOW_ADDR, 0x08},
	{REG_FRAME_ROW_START_HIGH_ADDR, 0x00},              // ????????¦Ë??
	{REG_FRAME_ROW_START_LOW_ADDR, 0x08},
	{REG_HDR_ENABLE_CTRL_ADDR, 0x10},                   // ??? HDR ??
	{0x3223, 0x50},
	{0x3250, 0xf0},
	{0x3251, 0x02},
	{0x3252, 0x03},
	{0x3253, 0xb0},
	{0x3254, 0x02},
	{0x3255, 0x07},
	{0x3304, 0x48},
	{0x3306, 0x38},
	{0x3309, 0x68},
	{0x330b, 0xe0},
	{0x330c, 0x18},
	{0x330f, 0x20},
	{0x3310, 0x10},
	{0x3314, 0x6d},
	{0x3315, 0x38},
	{0x3316, 0x68},
	{0x3317, 0x0f},
	{0x3329, 0x5c},
	{0x332d, 0x5c},
	{0x332f, 0x60},
	{0x3335, 0x64},
	{0x3344, 0x64},
	{0x335b, 0x80},
	{0x335f, 0x80},
	{0x3366, 0x06},
	{0x3385, 0x31},
	{0x3387, 0x51},
	{0x3389, 0x01},
	{0x33b1, 0x03},
	{0x33b2, 0x06},
	{0x3621, 0xa4},
	{0x3622, 0x05},
	{0x3624, 0x47},
	{0x3631, 0x48},
	{0x3633, 0x52},
	{0x3635, 0x18},
	{0x3636, 0x25},
	{0x3637, 0x89},
	{0x3638, 0x0f},
	{0x3639, 0x08},
	{0x363a, 0x00},
	{0x363b, 0x48},
	{0x363c, 0x06},
	{0x363e, 0xf8},
	{0x3640, 0x00},
	{0x3641, 0x01},
	{0x36ea, 0x36},
	{0x36eb, 0x1a},
	{0x36ec, 0x0a},
	{0x36ed, 0x23},
	{0x36fa, 0x36},
	{0x36fb, 0x10},
	{0x36fc, 0x01},
	{0x36fd, 0x03},
	{REG_BLC_TARGET_VALUE_LOW_ADDR, 0x91},
	{REG_DVP_POL_CTRL_ADDR, 0x01},
	{REG_AEC_TOTAL_EXPOSURE_TIME_HIGH_ADDR, 0x14},
	{REG_AEC_TOTAL_EXPOSURE_TIME_LOW_ADDR, 0x80},
	{REG_DIGITAL_COARSE_GAIN_ADDR, 0x0c},
	{0x3f04, 0x03},
	{0x3f05, 0x4e},
	{0x4500, 0x59},
	{REG_INCREMENT_PATTERN_ENABLE_ADDR, 0xc4},
	{0x4809, 0x01},
	{0x4837, 0x1b},
	{0x5011, 0x00},
	{0x36e9, 0x20},
	{0x36f9, 0x24},
	{REG_SLEEP_MODE_CTRL_ADDR, 0x01},
	{REG_DELAY_ADDR, 0x0a},
	{0x4418, 0x08},
	{0x4419, 0x80},
	{0x363d, 0x10},
	{0x3630, 0x48},
	{REG_NULL_ADDR, 0x00}
};

// ????????
typedef struct _camera camera_t;
typedef struct _camera{
    uint16_t slv_addr;              // IIC ??????
    uint16_t chip_id;               // CHIP ID

    XIic* instance;                 // AXI_IIC ???

    exposure_mode exposure_mode;    // ?????

    void    (*reset)                    (camera_t *camera);
    uint16_t(*get_chip_id)              (camera_t *camera);
    void    (*set_sleep_mode)           (camera_t *camera, int enable);
    void    (*set_output_window)        (camera_t *camera, int offset_x, int offset_y, int w, int h);
    void    (*set_agc)                  (camera_t *camera, int gain);
    void    (*set_aec)                  (camera_t *camera, uint16_t total_exposure_time, uint16_t hdr_exposure_time);
    void    (*set_blc)                  (camera_t *camera, blc_args *args);
    void    (*set_hmirror)              (camera_t *camera, int enable);
    void    (*set_vflip)                (camera_t *camera, int enable);
    void    (*set_increment_pattern)    (camera_t *camera, int enable);
} camera_t;

void sc035hgs_init(camera_t *camera, uint16_t device_id);

#endif
