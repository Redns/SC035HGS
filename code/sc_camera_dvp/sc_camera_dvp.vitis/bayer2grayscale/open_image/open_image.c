#include "open_image.h"

/**
 * @brief 一维指针转换为二维
 * @param ptr       待转换的一维指针
 * @param width     二维数组行长
 * @param height    二维数组列数
 * @return 转换后的二维数组
*/
uint8_t **ptr_converter(uint8_t *ptr, uint32_t width, uint32_t height)
{
    uint8_t **convertPtr = (uint8_t**)malloc(sizeof(uint8_t*) * height);
    for(uint32_t i = 0; i < height; i++)
    {
        convertPtr[i] = &ptr[width * i];
    } 
    return convertPtr;
}


/**
 * @brief RGB 转灰度
 * @param r R 通道像素值
 * @param g G 通道像素值
 * @param b B 通道像素值
 * @return 灰度像素值
*/
uint8_t rgb2grayscale(uint8_t r, uint8_t g, uint8_t b)
{
    return (r + g + b) / 3;
}


/**
 * @brief 将 bayer BG_GR 转换为灰度图
 * @param bayer bayer 图像缓冲区
 * @param grayscale 灰度图像缓冲区
 * @param image_width 图像宽度
 * @param image_height 图像高度
*/
void bayer2grayscale(uint8_t **bayer, uint8_t **grayscale, uint16_t image_width, uint16_t image_height)
{
    if((image_width < 2) || (image_height < 2))
    {
        return;
    }

    if((image_width % 2 != 0) || (image_height % 2 != 0))
    {
        return;
    }

    // 处理最外围像素
    for(uint16_t row = 0; row < image_height; row++)
    {
        if(row == 0)
        {
            grayscale[0][0] = rgb2grayscale(bayer[1][1], (bayer[0][1] + bayer[1][0]) / 2, bayer[0][0]);
            grayscale[0][image_width - 1] = rgb2grayscale(bayer[1][image_width - 1], bayer[0][image_width - 1], bayer[0][image_width - 2]);
            for(uint16_t col = 1; col < image_width - 1; col++)
            {
                grayscale[0][col] = (col % 2 == 0) ? rgb2grayscale((bayer[1][col - 1] + bayer[1][col + 1]) / 2, (bayer[0][col - 1] + bayer[0][col + 1] + bayer[1][col]) / 3, bayer[0][col]) :
                    rgb2grayscale(bayer[1][col], bayer[0][col], (bayer[0][col - 1] + bayer[0][col + 1]) / 2);
            }
        }
        else if(row == image_height - 1)
        {
            grayscale[image_height - 1][0] = rgb2grayscale(bayer[image_height - 1][1], bayer[image_height - 1][0], bayer[image_height - 2][0]);
            grayscale[image_height - 1][image_width - 1] = rgb2grayscale(bayer[image_height - 1][image_width - 1], (bayer[image_height - 1][image_width - 2] + bayer[image_height - 2][image_width - 1]) / 2, bayer[image_height - 2][image_width - 2]);
            for(uint16_t col = 1; col < image_width - 1; col++)
            {
                grayscale[image_height - 1][col] = (col % 2 == 0) ? rgb2grayscale((bayer[image_height - 1][col - 1] + bayer[image_height - 1][col + 1]) / 2, bayer[image_height - 1][col], bayer[image_height - 2][col]) : 
                    rgb2grayscale(bayer[image_height - 1][col], (bayer[image_height - 1][col - 1] + bayer[image_height - 1][col + 1] + bayer[image_height - 2][col]) / 3, (bayer[image_height - 2][col - 1] + bayer[image_height - 2][col + 1]));
            }
        }
        else
        {
            // 非顶点边界像素
            grayscale[row][0] = (row % 2 == 0) ? rgb2grayscale((bayer[row - 1][1] + bayer[row + 1][1]) / 2, (bayer[row - 1][0] + bayer[row + 1][0] + bayer[row][1]) / 3, bayer[row][0]) :
                rgb2grayscale(bayer[row][1], bayer[row][0], (bayer[row - 1][0] + bayer[row + 1][0]) / 2);
            grayscale[row][image_width - 1] = (row % 2 == 0) ? rgb2grayscale(bayer[row - 1][image_width - 1], bayer[row][image_width - 1], bayer[row][image_width - 2]) :
                rgb2grayscale(bayer[row][image_width - 1], (bayer[row][image_width - 2] + bayer[row - 1][image_width - 1] + bayer[row + 1][image_width - 1]) / 3, (bayer[row - 1][image_width - 2] + bayer[row + 1][image_width - 2]) / 2);
        }
    }

    // 处理内部像素点
    for(uint16_t row = 1; row < image_height - 1; row++)
    {
        if(row % 2 == 0)
        {
            // G
            for(uint16_t col = 1; col < image_width - 1; col += 2)
            {
                grayscale[row][col] = rgb2grayscale((bayer[row - 1][col] + bayer[row + 1][col]) / 2, bayer[row][col], (bayer[row][col - 1] + bayer[row][col + 1]) / 2);
            }
            // B
            for(uint16_t col = 2; col < image_width - 1; col += 2)
            {
                grayscale[row][col] = rgb2grayscale((bayer[row - 1][col - 1] + bayer[row - 1][col + 1] + bayer[row + 1][col - 1] + bayer[row + 1][col + 1]) / 4, (bayer[row - 1][col] + bayer[row][col - 1] + bayer[row][col + 1] + bayer[row + 1][col]) / 4, bayer[row][col]);
            }
        }
        else
        {
            // R
            for(uint16_t col = 1; col < image_width - 1; col += 2)
            {
                grayscale[row][col] = rgb2grayscale(bayer[row][col], (bayer[row][col - 1] + bayer[row][col + 1] + bayer[row - 1][col] + bayer[row + 1][col]) / 4, (bayer[row - 1][col - 1] + bayer[row - 1][col + 1] + bayer[row + 1][col - 1] + bayer[row + 1][col + 1]) / 4);
            }
            // G
            for(uint16_t col = 2; col < image_width - 1; col += 2)
            {
                grayscale[row][col] = rgb2grayscale((bayer[row][col - 1] + bayer[row][col + 1]) / 2, bayer[row][col], (bayer[row - 1][col] + bayer[row + 1][col]) / 2);
            }
        }
    }
}