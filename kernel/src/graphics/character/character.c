#include "character.h"
#define FONT8x16_IMPLEMENTATION
#include "font8x16.h"
#include "graphics/framebuffer.h"
#include "core/panic.h"
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
void p_fprint(char c[]) {
    const struct ScreenDimensions d = screen_dimensions();
    if (d.status == FAIL) {
        hcf();
    }

    const uint16_t SCREEN_WIDTH = d.w / 8;
    // const uint16_t SCREEN_HEIGHT = d.h / 16;

    uint16_t printer_location[2] = { 0, 0 };

    uint16_t char_num = 0;

    while (*c != '\0') {
        if (*c == '\n' || char_num >= SCREEN_WIDTH) {
            // Reset the printer location and go to next line
            printer_location[0] = 0;
            printer_location[1] += 16;
            c++;
            char_num = 0;
            continue;
        }
        draw_character(*c, printer_location[0], printer_location[1]);
        printer_location[0] += 8;

        c++;
        char_num++;
    }
}
