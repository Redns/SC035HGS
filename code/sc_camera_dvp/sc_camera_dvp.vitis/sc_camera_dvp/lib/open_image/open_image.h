#ifndef __OPEN_IMAGE_H__
#define __open_image_H__

#include <stdint.h>
#include <malloc.h>

uint8_t **ptr_converter(uint8_t *ptr, uint32_t width, uint32_t height);
void bayer2grayscale(uint8_t **bayer, uint8_t **grayscale, uint16_t image_width, uint16_t image_height);

#endif