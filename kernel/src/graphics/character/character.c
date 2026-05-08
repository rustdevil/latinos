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

// Primitive print string function that does not acknowledge existing text on screen and just prints.
void primitive_fprint(char c[]) {
    const uint16_t SCREEN_WIDTH = screen_dimensions('w') / 8;
    const uint16_t SCREEN_HEIGHT = screen_dimensions('h') / 16;

    uint16_t printer_location[2] = { 0, 0 };

    uint16_t char_num = 0;
    while (*c != '\0') {
        if (*c == '\n') {
            // Reset the printer location and go to next line
            printer_location[0] = 0;
            printer_location[1] += 16;
            c++;
            continue;
        }
        draw_character(*c, printer_location[0], printer_location[1]);
        printer_location[0] += 8;

        c++;
    }
}
