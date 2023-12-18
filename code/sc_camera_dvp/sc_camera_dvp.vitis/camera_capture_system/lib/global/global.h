#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "xil_types.h"

#define FRAME_WIDTH                 640                                     // Ö¡¿í¶È
#define FRAME_HEIGHT                480                                     // Ö¡¸ß¶È
#define FRAME_SIZE					(FRAME_WIDTH * FRAME_HEIGHT)

#define RX_BUFFER_NUMS		10
#define RX_BUFFER_BASE		0x08000000
#define RX_BUFFER_SIZE		0x00080000
#define RX_BUFFER_INVALID	0xFFFFFFFF

#endif
