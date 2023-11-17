/*
 * ov5640_sccb.h
 *
 *  Created on: 2020��6��1��
 *      Author: Administrator
 */

#ifndef SRC_OV5640_SCCB_H_
#define SRC_OV5640_SCCB_H_

#include "xgpiops.h"

//����һ���ṹ��
typedef struct RegData{
	u16 reg;
	u8  data;
}SccbRD;



XGpioPs   SCCB_INST;

#define SEQUENCE_END 0x0000

#define	SlaveADDR 0x78

//V18~EMIO0~54Pin
#define SCL_H		XGpioPs_WritePin(&SCCB_INST,54,1)
#define SCL_L		XGpioPs_WritePin(&SCCB_INST,54,0)

//PWDN
#define PWDN_H		XGpioPs_WritePin(&SCCB_INST,57,1)
#define PWDN_L		XGpioPs_WritePin(&SCCB_INST,57,0)

//RESET_N
#define RST_N_L		XGpioPs_WritePin(&SCCB_INST,56,0)
#define RST_N_H		XGpioPs_WritePin(&SCCB_INST,56,1)//

//V17~EMIO1~55Pin
#define SDA_IN		XGpioPs_SetDirectionPin(&SCCB_INST,55,0)
#define SDA_OUT		XGpioPs_SetDirectionPin(&SCCB_INST,55,1)
#define SDA_Ibit	XGpioPs_ReadPin(&SCCB_INST,55)
#define SDA_O(n)	XGpioPs_WritePin(&SCCB_INST,55,n)

//PL_LEDx,x=1,2;n=1,2;
#define PL_LED(x,n) XGpioPs_WritePin(&SCCB_INST,x+57,n)

//OV5640��ʼ��
void OV5640_SCCB_Init(void);


//SCCB��ʼ�ź�
void SCCB_Start(void);
//SCCBֹͣ�ź�
void SCCB_Stop(void);

//SCCB����һ���ֽ�
void SCCB_SendByte(u8 data);
//SCCB����һ���ֽ�
u8   SCCB_RevByte(void);
//SCCB����X�ź�
u8 SCCB_RevXs(void);


//SCCB����һ���ֽ�
u8 SCCB_RecvByteFReg(u8 SlaveAddr,u16 RegAddr);

//SCCB��u16�Ĵ�������һ���ֽ�
void SCCB_SendByte2Reg(u8 SlaveAddr,u16 RegAddr,u8 Data);
void OV5640_Init(void);

#endif /* SRC_OV5640_SCCB_H_ */



