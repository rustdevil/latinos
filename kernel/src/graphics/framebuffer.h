#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>
#include "core/error.h"

void framebuffer_init(void);
void gradient_test(void);

void draw_pixel(uint32_t x, uint32_t y, uint32_t color);
void draw_line(uint32_t x, uint32_t y, uint32_t length, uint32_t color);
void draw_rect(uint32_t x, uint32_t y, uint32_t length, uint32_t height, uint32_t color);
void draw_3d_rect(uint32_t x, uint32_t y, uint32_t length, uint32_t height);
void draw_text(char *text, uint32_t x, uint32_t y, uint32_t color);
void draw_window(uint32_t x, uint32_t y, uint32_t length, uint32_t height, char *title);

struct ScreenDimensions {
    uint32_t w, h;
    enum Status status;
};
struct ScreenDimensions screen_dimensions();

#endif
