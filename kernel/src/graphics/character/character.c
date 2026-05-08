#include "character.h"
#define FONT8x16_IMPLEMENTATION
#include "font8x16.h"
#include "../framebuffer.h"
#include <stdint.h>

void draw_character(uint8_t c, uint32_t x, uint32_t y) {
    for (int ly = 0; ly < 16; ly++) {
        uint8_t row = font8x16[c][ly];

        for (int lx = 7; lx >= 0; lx--) {
            uint8_t mask = (1 << lx);

            if (row & mask) {
                draw_pixel(x + (7 - lx), y + ly, 0xFFFFFFFF);
            } else {
                draw_pixel(x + (7 - lx), y + ly, 0x00000000);
            }
        }
    }
}
