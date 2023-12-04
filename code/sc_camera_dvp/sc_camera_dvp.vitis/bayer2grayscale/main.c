#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <string.h>


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

void test(uint8_t n);
uint32_t get_num_length(uint32_t n);
uint8_t* num2str(uint32_t n);
uint8_t rgb2grayscale(uint8_t r, uint8_t g, uint8_t b);
uint8_t **ptr_converter(uint8_t *ptr, uint32_t width, uint32_t height);
void bayer2grayscale(uint8_t **bayer, uint8_t **grayscale, uint16_t image_width, uint16_t image_height);
char* generate_image_front_frame(uint32_t image_id, uint32_t image_size, uint32_t image_width, uint32_t image_height, Image_Format image_format);


int main()
{
    // 指针转换测试 ---------------------------------------------------
    // uint8_t data[] = { 1, 2, 22, 28, 32, 96, 87, 64 };
    // uint8_t **dataPtr = ptr_converter(data, 2, 4);
    // for(uint8_t i = 0; i < 4; i++)
    // {
    //     for(uint8_t j = 0; j < 2; j++)
    //     {
    //         printf("dataPtr[%u][%u] is %u\n", i, j, dataPtr[i][j]);
    //     }
    // }

    // Bayer 转灰度测试 -----------------------------------------------
    // uint8_t bayer_image[] = { 10, 20, 30, 40 };
    // uint8_t grayscale_image[4];
    // bayer2grayscale(ptr_converter(bayer_image, 2, 2), ptr_converter(grayscale_image, 2, 2), 2, 2); 
    
    // uint32_t n = 12345;
    // printf("The length of n is %d\n", get_num_length(n));
    // printf("Convert n to string: %s\n", num2str(n));

    printf("0x%02x", 0x1);
    // char *str = generate_image_front_frame(0, 64, 8, 8, Format_Grayscalec8);
    // printf("[str] %s", str);
    // printf("[sizeof] %d\n", sizeof(str));
    // printf("[strlen] %d", strlen(str));

    test(7);

    time_t timep;

    struct tm *p;

    char time1[28];

    time (&timep);

    p=gmtime(&timep);

    printf("%d\t",p->tm_sec); /*获取当前秒*/

    printf("%d\t",p->tm_min); /*获取当前分*/

    printf("%d\t",8+p->tm_hour);/*获取当前时,这里获取西方的时间,刚好相差八个小时*/

    printf("%d\t",p->tm_mday);/*获取当前月份日数,范围是1-31*/

    printf("%d\t",1+p->tm_mon);/*获取当前月份,范围是0-11,所以要加1*/

    printf("%d\t",1900+p->tm_year);/*获取当前年份,从1900开始，所以要加1900*/

    printf("%d\n",p->tm_yday); /*从今年1月1日算起至今的天数，范围为0-365*/

    //将它们合成一个字符串

    sprintf(time1,"%d年%d月%d日 %d:%d:%d",1900+p->tm_year,1+p->tm_mon,p->tm_mday,8+p->tm_hour,p->tm_min,p->tm_sec);

    printf("当前时间为：%s\n",time1);
    
    return 0;
}


void test(uint8_t n)
{
    while(n--)
    {
        printf("[INFO] %u\n", n);
    }
}


/**
 * @brief 获取数字长度
 * @param n 待分析的数字
 * @return 数字长度
*/
uint32_t get_num_length(uint32_t n)
{
    uint32_t num_length = 0;
    while(n > 0)
    {
        n /= 10;
        num_length++;
    }
    return num_length;
}


/**
 * @brief 数字转字符串
 * @param n 待转换的数字
 * @return 转换后的字符串 
*/
uint8_t* num2str(uint32_t n)
{
    uint32_t str_length = get_num_length(n);
    uint8_t *str = (uint8_t*)malloc(sizeof(uint8_t) * str_length + 1);
    for(int i = str_length - 1; i >= 0; i--)
    {
        str[i] = (n % 10) + '0';
        n /= 10;
    }
    str[str_length] = 0;
    return str;
}


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
