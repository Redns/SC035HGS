#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "FreeRTOS.h"
#include "semphr.h"
#include "xil_types.h"

#define PLATFORM_ZYNQ 

/* 帧属性 */
#define FRAME_WIDTH                 640                                     // 帧宽度
#define FRAME_HEIGHT                480                                     // 帧高度
#define FRAME_SIZE					(FRAME_WIDTH * FRAME_HEIGHT)            // 帧尺寸（字节）

/* 接收缓冲区 */
#define RX_BUFFER_NUMS		        3                                       // 数量 
#define RX_BUFFER_BASE              0x11000000                              // 基地址
#define RX_BUFFER_SIZE		        0x00080000                              // 大小（单位：字节，默认 512 KB）
#define RX_BUFFER_INVALID_ADDR	    0xFFFFFFFF                              // 缓冲区无效标志

#endif
