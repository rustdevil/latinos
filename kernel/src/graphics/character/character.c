#include "graphics/character/character.h"
#include "core/error.h"
#include "graphics/framebuffer.h"
#include "core/panic.h"
#include "graphics/character/font.h"
#include <stdint.h>

extern const unsigned char __font_bitmap__[];
void draw_character(uint8_t c, uint32_t x, uint32_t y, uint32_t color, uint8_t t) {
    const unsigned char *glyph_ptr = &__font_bitmap__[c * 16];
    for (int ly = 0; ly < 16; ly++) {
        uint8_t row = glyph_ptr[ly];

        for (int lx = 7; lx >= 0; lx--) {
            uint8_t mask = (1 << lx);

            if (row & mask) {
                draw_pixel(x + (7 - lx), y + ly, color);
            } else {
                if (t == 0) {
                    draw_pixel(x + (7 - lx), y + ly, 0x00000000);
                }
            }
        }
    }
}

// Primitive print string function that does not acknowledge existing text on screen and just prints.
void p_fprint(char c[], uint32_t color) {
    const struct ScreenDimensions d = screen_dimensions();
    if (d.status == FAIL) {
        panic("Failed to get screen dimensions");
    }

    const uint16_t SCREEN_WIDTH = d.w / 8;

    static uint16_t printer_location[2] = { 0, 0 };
    static uint16_t char_num = 0;

    while (*c != '\0') {
        if (*c == '\n' || char_num >= SCREEN_WIDTH) {
            // Reset the printer location and go to next line
            printer_location[0] = 0;
            printer_location[1] += 16;
            char_num = 0;
            if (*c == '\n') {
                c++; // Only skip the newline character itself
                continue;
            }
        }
        draw_character(*c, printer_location[0], printer_location[1], color, 0);
        printer_location[0] += 8;

        c++;
        char_num++;
    }
}
