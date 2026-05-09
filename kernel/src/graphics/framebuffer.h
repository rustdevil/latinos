#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>
#include "core/error.h"

void framebuffer_init(void);
void gradient_test(void);

void draw_pixel(uint32_t x, uint32_t y, uint32_t color);

struct ScreenDimensions {
    uint32_t w, h;
    enum Status status;
};
struct ScreenDimensions screen_dimensions();

#endif
