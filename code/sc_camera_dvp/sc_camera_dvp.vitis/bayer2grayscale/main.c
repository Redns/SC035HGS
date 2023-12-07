#include <stdio.h>
#include "vofa/vofa.h"
#include "delegate/delegate.h"
#include "open_image/open_image.h"

void bayer2gray_test();
void ptr_convert_test();

int main()
{
    // 指针转换测试
    ptr_convert_test();
    
    // Bayer 转灰度测试
    bayer2gray_test();

    /* 委托测试 */
    // delegate_init(delegate_handler);
    // delegate_invoke();
    
    return 0;
}


/**
 * @brief 指针转换测试
 * @return *
*/
void ptr_convert_test()
{
    uint8_t data[] = { 1, 2, 22, 28, 32, 96, 87, 64 };
    uint8_t **dataPtr = ptr_converter(data, 2, 4);
    for(uint8_t i = 0; i < 4; i++)
    {
        for(uint8_t j = 0; j < 2; j++)
        {
            printf("dataPtr[%u][%u] is %u\n", i, j, dataPtr[i][j]);
        }
    }
}


/**
 * @brief Bayer 转灰度测试
 * @return *
*/
void bayer2gray_test()
{
    uint8_t bayer_image[] = { 10, 20, 30, 40 };
    uint8_t grayscale_image[4];
    bayer2grayscale(ptr_converter(bayer_image, 2, 2), ptr_converter(grayscale_image, 2, 2), 2, 2); 
}