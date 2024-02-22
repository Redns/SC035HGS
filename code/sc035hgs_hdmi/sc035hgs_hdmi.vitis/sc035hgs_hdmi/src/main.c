#include <stdio.h>
#include <sleep.h>
#include "platform.h"
#include "xil_printf.h"
#include "display_ctrl.h"
#include "dynclk.h"
#include "vdma_api.h"
#include "xparameters.h"
#include "xgpio.h"
#include "sc035hgs.h"

/* 相关外设 ID */
#define DEVICE_IICS                 XPAR_I2CS_DEVICE_ID                         // IIC（AXI GPIO 模拟）
#define DEVICE_CAMERA_PWDN			XPAR_CAMERA_PWDN_DEVICE_ID                  // SC035HGS 休眠控制（正常工作时应拉高）
#define DEVICE_CAMERA_VSYNC			XPAR_CAMERA_VSYNC_DEVICE_ID                 // SC035HGS 输出场同步信号
#define DEVICE_VIDEO_IN_ACTIVE      
#define DYNCLK_BASEADDR             XPAR_AXI_DYNCLK_0_BASEADDR                  // 动态时钟基地址
#define VDMA_ID                     XPAR_AXIVDMA_0_DEVICE_ID                    // VDMA器件ID
#define DISP_VTC_ID                 XPAR_VTC_0_DEVICE_ID                        // VTC器件ID

/* 外设句柄 */
static XGpio gpio_video_in_active;
static XGpio gpio_camera_pwdn;
static XGpio gpio_camera_vsync;

unsigned int const frame_buffer_addr = (XPAR_PS7_DDR_0_S_AXI_BASEADDR + 0x1000000);
XAxiVdma     vdma;
DisplayCtrl  dispCtrl;
VideoMode    vd_mode;

static s32 Camera_Init();
static s32 System_Init();
static void SC035HGS_Hello_Msg_Print();

int main(void)
{
    s32 Status;

    /* 欢迎信息 */
    SC035HGS_Hello_Msg_Print();
    
    /* 平台初始化 */
	init_platform();

	/* 系统初始化 */
	Status = System_Init();
	if(Status != XST_SUCCESS)
	{
		xil_printf("[ERROR] System init failed\n");
		return 0;
	}

    /* 等待场同步信号 */
	for(u8 frame_ignore_cnt = 0; frame_ignore_cnt < 10; frame_ignore_cnt++)
	{
		while(XGpio_DiscreteRead(&gpio_camera_vsync, 1) == 1);
		while(XGpio_DiscreteRead(&gpio_camera_vsync, 1) == 0);
	}
    XGpio_DiscreteWrite(&gpio_video_in_active, 1, 0x1);

	vd_mode = VMODE_1280x720;

	//配置VDMA
	run_vdma_frame_buffer(&vdma, VDMA_ID, vd_mode.width, vd_mode.height,
							frame_buffer_addr,0,0,BOTH);
    //初始化Display controller
	DisplayInitialize(&dispCtrl, DISP_VTC_ID, DYNCLK_BASEADDR);
    //设置VideoMode
	DisplaySetMode(&dispCtrl, &vd_mode);
	DisplayStart(&dispCtrl);

	while(1)
	{
		PL_LED(1,0);
		sleep(1);
		PL_LED(1,1);
		sleep(1);
	}
    return 0;
}


/**
 * @brief 初始化系统
 * @return 初始化成功返回 XST_SUCCESS，否则返回 XST_FAILURE
*/
static s32 System_Init()
{
	s32 Status;

	/* 初始化摄像头 */
	Status = Camera_Init();
	if(Status != XST_SUCCESS)
	{
		print("[ERROR] Failed to init camera\n");
		return XST_FAILURE;
	}

	return Status;
}

/**
 * @brief 初始化摄像头
 * @return 
*/
static s32 Camera_Init()
{
    s32 Status;
	camera_t camera;   

    /* 初始化相关引脚 */
    XGpio_Initialize(&gpio_camera_pwdn, DEVICE_CAMERA_PWDN);
    XGpio_Initialize(&gpio_camera_vsync, DEVICE_CAMERA_VSYNC);

    /* 等待摄像头输入时钟锁定 */
    while(XGpio_DiscreteRead(&gpio_camera_xclk_locked, 1) == 0);

    /* 拉高 PWDN 引脚以启用摄像头 */
    XGpio_DiscreteWrite(&gpio_camera_pwdn, 1, 0x1);

    // 至少等待 4ms 才能访问寄存器
    usleep(20 * 1000);

    /* 初始化摄像头寄存器 */
    camera.i2c_device_id = DEVICE_IICS;

    Status = sc035hgs_init(&camera);
    if(Status != XST_SUCCESS)
    {
    	print("[ERROR] SC035HGS's regs init failed\n");
    	return XST_FAILURE;
    }
    print("[INFO] Success to init SC035HGS\n");

    // 等待摄像头输出稳定
    u8 camera_ignore_frame_cnt = 0;
    while(camera_ignore_frame_cnt < 10)
    {
        camera_ignore_frame_cnt++;
        while(XGpio_DiscreteRead(&gpio_camera_vsync, 1) == 0);
        while(XGpio_DiscreteRead(&gpio_camera_vsync, 1) == 1);
    }

	return XST_SUCCESS;
}


/**
 * @brief 欢迎信息打印
 * @return *
*/
static void SC035HGS_Hello_Msg_Print()
{
	const s8 msg[][100] =
	{
		" .d8888b.   .d8888b.   .d8888b.   .d8888b.  888888888  888    888  .d8888b.   .d8888b.\n",
		"d88P  Y88b d88P  Y88b d88P  Y88b d88P  Y88b 888        888    888 d88P  Y88b d88P  Y88b\n",
		"Y88b.      888    888 888    888      .d88P 888        888    888 888    888 Y88b.\n",
		"\"Y888b.   888        888    888     8888\"  8888888b.  8888888888 888         \"Y888b.\n",
		"	\"Y88b. 888        888    888      \"Y8b.      \"Y88b 888    888 888  88888     \"Y88b.\n",
		"	  \"888 888    888 888    888 888    888        888 888    888 888    888       \"888\n",
		"Y88b  d88P Y88b  d88P Y88b  d88P Y88b  d88P Y88b  d88P 888    888 Y88b  d88P Y88b  d88P\n",
		" \"Y8888P\"   \"Y8888P\"   \"Y8888P\"   \"Y8888P\"   \"Y8888P\"  888    888  \"Y8888P88  \"Y8888P\"\n"
	};

    for(u8 i = 0; i < sizeof(msg) / sizeof(msg[0]); i++)
    {
        xil_printf(msg[i]);
    }
}