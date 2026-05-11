#include "framebuffer.h"
#include "graphics/character/character.h"
#include "limine.h"
#include "core/panic.h"
#include "com/debugcon.h"
#include "core/memory.h"

#include <stdint.h> // For stuff like uint64_t
#include <stddef.h>
#include <stdbool.h>

__attribute__((used, section(".limine_requests")))
static volatile uint64_t limine_base_revision[] = LIMINE_BASE_REVISION(6);

__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
    .revision = 0
};

struct limine_framebuffer *framebuffer = NULL;

// Start and end markers for the Limine requests.

__attribute__((used, section(".limine_requests_start")))
static volatile uint64_t limine_requests_start_marker[] = LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests_end")))
static volatile uint64_t limine_requests_end[] = LIMINE_REQUESTS_END_MARKER;

void framebuffer_init(void) {
    qprint("Initializing framebuffer...");

    // Ensure bootloader understands our base spec.
    if (!LIMINE_BASE_REVISION_SUPPORTED(limine_base_revision)) {
        panic("Limine base revision unsupported");
    }

    // Ensure we got a framebuffer.
    if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1) {
        panic("No framebuffer");
    }

    framebuffer = framebuffer_request.response->framebuffers[0];
}

void gradient_test(void) {
    qprint("Running gradient test...");

    // Draw gradient on the framebuffer
    volatile uint32_t *fb_ptr = framebuffer->address;

    for (size_t y = 0; y < framebuffer->height; y++) {
        for (size_t x = 0; x < framebuffer->width; x++) {
            uint32_t nX = x * 255 / framebuffer->width;
            uint32_t nY = y * 255 / framebuffer->height;
            fb_ptr[y * (framebuffer->pitch / 4) + x] = ((nY << 8) | nX);
        }
    }
}

void clear_screen(void) {
    memset(framebuffer->address, 0x00000000, framebuffer->width * framebuffer->height * sizeof(uint32_t));
}

// Drawing functions.

void draw_pixel(uint32_t x, uint32_t y, uint32_t color) {
    if (x < framebuffer->width && y < framebuffer->height) {
        volatile uint32_t *fb_ptr = framebuffer->address;
        fb_ptr[(y * (framebuffer->pitch / 4)) + x] = color;
    }
}

// Draw a horizontal line.
void draw_line(uint32_t x, uint32_t y, uint32_t length, uint32_t color) {
    for (uint32_t i = 0; i <= length; i++) {
        draw_pixel(x + i, y, color);
    }
}

// Draw a vertical line.
void draw_v_line(uint32_t x, uint32_t y, uint32_t length, uint32_t color) {
    for (uint32_t i = 0; i <= length; i++) {
        draw_pixel(x, y + i, color);
    }
}

void draw_rect(uint32_t x, uint32_t y, uint32_t length, uint32_t height, uint32_t color) {
    for (uint32_t i = 0; i <= height; i++) {
        draw_line(x, y + i, length, color);
    }
}

// Draw a rect with a border
void draw_3d_rect(uint32_t x, uint32_t y, uint32_t length, uint32_t height) {
    draw_rect(x, y, length, height, 0xFFD0D0D0);

    // Top side
    for (uint32_t i = 0; i < 3; i++) {
        draw_line(x, y + i, length - (i * 2), 0xFFFFFFFF);
    }

    // Left side
    for (uint32_t i = 0; i < 3; i++) {
        draw_v_line(x + i, y + i, height - (i * 2), 0xFFAAAAAA);
    }

    // Bottom side
    for (uint32_t i = 0; i < 3; i++) {
        draw_line(x + i, y + height - i, length - (i * 2), 0xFF505050); // FAAAHHHHHHHH
    }

    // Right side
    for (uint32_t i = 0; i < 3; i++) {
        draw_v_line(x + length - i, y + i, height - (i * 2), 0xFFAAAAAA);
    }
}

void draw_text(char *text, uint32_t x, uint32_t y, uint32_t color) {
    uint32_t offset = 0;
    while (*text != '\0') {
        draw_character(*text, x + offset, y, color, 1);
        offset += 9; // Font width is 8
        text++;
    }
}

void draw_window(uint32_t x, uint32_t y, uint32_t length, uint32_t height, char *title) {
    const int title_y_size = 25;

    draw_3d_rect(x, y, length + 6, height + 6 + title_y_size);
    draw_rect(x + 3, y + 3, length, title_y_size, 0xFF0011BB);
    draw_rect(x + length - 25 + 3, y + 3, 25, 25, 0xFFCC0000); // Close btn
    //draw_3d_rect(x + length - 50 + 3, y + 3, 25, 25); // Minimize btn
    draw_text(title, x + 10, y + 10, 0xFF00115A);
    draw_text(title, x + 10, y + 8, 0xFFFFFFFF);
}

struct ScreenDimensions screen_dimensions() {
    struct ScreenDimensions d;

    if (framebuffer != NULL) {
        d.w = framebuffer->width;
        d.h = framebuffer->height;
        d.status = SUCCESS;

        return d;
    } else {
        d.w = 0;
        d.h = 0;
        d.status = FAIL;

        return d;
    }
}
