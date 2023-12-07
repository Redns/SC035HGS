#include "vofa.h"

/**
 * @brief VOFA 上位机图片控件前导帧生成
 * @param image_id 图片序号
 * @param image_size 图片尺寸（字节）
 * @param image_width 图片宽度
 * @param image_height 图片高度
 * @param image_format 图片格式
 * @return 前导帧字符串
*/
char* generate_image_front_frame(uint32_t image_id, uint32_t image_size, uint32_t image_width, uint32_t image_height, Image_Format image_format)
{
    // 图片前导帧包含图片识别码、尺寸、高度、宽度、格式信息
    char* image_frame_front = (char*)malloc(sizeof(char) * 64);
    memset(image_frame_front, 0, sizeof(char) * 64);
    // 前导帧格式为："image:<image_id>,<image_size>,<image_width>,<image_height>,<image_format>\n"
    // 示例："image:0,128,8,16,24\n"
    sprintf(image_frame_front, "image:%lu,%lu,%lu,%lu,%d\n", image_id, image_size, image_width, image_height, image_format);
    return image_frame_front;
}