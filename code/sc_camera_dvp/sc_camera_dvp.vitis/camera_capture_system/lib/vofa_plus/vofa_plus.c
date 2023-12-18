#include "vofa_plus.h"

/**
 * @brief ͼƬǰ��֡����
 * @param image_id      ͼƬ��ʶ��
 * @param image_size    ͼƬ�ߴ磨�ֽڣ�
 * @param image_width   ͼƬ���
 * @param image_height  ͼƬ�߶�
 * @param image_format  ͼƬ��ʽ
 * @return *
 */
char* generate_image_front_frame(uint32_t image_id, uint32_t image_size, uint32_t image_width, uint32_t image_height, Image_Format image_format)
{
    // ͼƬǰ��֡����ͼƬʶ���롢�ߴ硢�߶ȡ���ȡ���ʽ��Ϣ
    char* image_frame_front = (char*)malloc(sizeof(char) * IMAGE_FRONT_FRAME_SIZE);
    memset(image_frame_front, 0, sizeof(char) * IMAGE_FRONT_FRAME_SIZE);
    // ǰ��֡��ʽΪ��"image:<image_id>,<image_size>,<image_width>,<image_height>,<image_format>\n"
    // ʾ����"image:0,128,8,16,24\n"
    sprintf(image_frame_front, "image:%lu,%lu,%lu,%lu,%d\n", image_id, image_size, image_width, image_height, image_format);
    return image_frame_front;
}
