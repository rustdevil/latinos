#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>

void framebuffer_init(void);
void gradient_test(void);

void draw_pixel(uint32_t x, uint32_t y, uint32_t color);

#endif
