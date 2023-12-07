#ifndef __OPEN_IMAGE_H__
#define __OPEN_IMAGE_H__

#include <stdint.h>

uint8_t rgb2grayscale(uint8_t r, uint8_t g, uint8_t b);
uint8_t **ptr_converter(uint8_t *ptr, uint32_t width, uint32_t height);
void bayer2grayscale(uint8_t **bayer, uint8_t **grayscale, uint16_t image_width, uint16_t image_height);

#endif