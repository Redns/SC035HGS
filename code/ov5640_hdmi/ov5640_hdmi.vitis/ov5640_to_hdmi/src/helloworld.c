#include <stdio.h>
#include <sleep.h>
#include "platform.h"
#include "xil_printf.h"
#include "display_ctrl.h"
#include "dynclk.h"
#include "ov5640_sccb.h"
#include "vdma_api.h"


//�궨��
#define DYNCLK_BASEADDR  XPAR_AXI_DYNCLK_0_BASEADDR  //��̬ʱ�ӻ���ַ
#define VDMA_ID          XPAR_AXIVDMA_0_DEVICE_ID    //VDMA����ID
#define DISP_VTC_ID      XPAR_VTC_0_DEVICE_ID        //VTC����ID

//ȫ�ֱ���
//frame buffer����ʼ��ַ
unsigned int const frame_buffer_addr = (XPAR_PS7_DDR_0_S_AXI_BASEADDR
										+ 0x1000000);
XAxiVdma     vdma;
DisplayCtrl  dispCtrl;
VideoMode    vd_mode;

int main(void)
{
	u8 ov5640_id;
	vd_mode=VMODE_1280x720;
    print("Hello World\n\r");
    OV5640_SCCB_Init();
    OV5640_Init();
    print("Hello World\n\r");

    ov5640_id=SCCB_RecvByteFReg(SlaveADDR,0x3100);
    if(ov5640_id!=0x78){
    	xil_printf("��ʼ��ʧ�ܣ�ID��%d",ov5640_id);
    	return 0;
    }
    else{
    	xil_printf("OV5640 ������ID��%d",ov5640_id);
    }

	vd_mode = VMODE_1280x720;

	//����VDMA
	run_vdma_frame_buffer(&vdma, VDMA_ID, vd_mode.width, vd_mode.height,
							frame_buffer_addr,0,0,BOTH);
    //��ʼ��Display controller
	DisplayInitialize(&dispCtrl, DISP_VTC_ID, DYNCLK_BASEADDR);
    //����VideoMode
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
