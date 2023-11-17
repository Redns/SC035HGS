#ifndef __VOFA_H__
#define __VOFA_H__

#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <string.h>

#define IMAGE_FRONT_FRAME_SIZE          64              // 图片前导帧尺寸（字节）

typedef enum Image_Format {
    Format_Invalid = 0,
    Format_Mono,
    Format_MonoLSB,
    Format_Indexed8,
    Format_RGB32,
    Format_ARGB32,
    Format_ARGB32_Premultiplied,
    Format_RGB16,
    Format_ARGB8565_Premultiplied,
    Format_RGB666,
    Format_ARGB6666_Premultiplied,
    Format_RGB555,
    Format_ARGB8555_Premultiplied,
    Format_RGB888,
    Format_RGB444,
    Format_ARGB4444_Premultiplied,
    Format_RGBX8888,
    Format_RGBA8888,
    Format_RGBA8888_Premultiplied,
    Format_BGR30,
    Format_A2BGR30_Premultiplied,
    Format_RGB30,
    Format_A2RGB30_Premultiplied,
    Format_Alpha8,
    Format_Grayscalec8,

    // 以下格式发送时，IMG_WIDTH和IMG_HEIGHT不需要强制指定，设置为-1即可
    Format_BMP,
    Format_GIF,
    Format_JPG,
    Format_PNG,
    Format_PBM,
    Format_PGM,
    Format_PPM,
    Format_XBM,
    Format_XPM,
    Format_SVG,
} Image_Format;

char* generate_image_front_frame(uint32_t image_id, uint32_t image_size, uint32_t image_width, uint32_t image_height, Image_Format image_format);

#endif