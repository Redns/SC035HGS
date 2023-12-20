#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "xil_types.h"

/* 帧属性 */
#define FRAME_WIDTH                 640                                     // 帧宽度
#define FRAME_HEIGHT                480                                     // 帧高度
#define FRAME_SIZE					(FRAME_WIDTH * FRAME_HEIGHT)            // 帧尺寸（字节）

/* 接收缓冲区 */
#define RX_BUFFER_NUMS		        3                                       // 数量                           
#define RX_BUFFER_SIZE		        0x00080000                              // 大小（字节）
#define RX_BUFFER_INVALID_FLAG	    0xFFFFFFFF                              // 缓冲区无效标志

#endif
