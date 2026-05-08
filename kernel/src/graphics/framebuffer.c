#include "framebuffer.h"
#include "../limine.h"
#include "../panic.h"
#include "../com/debugcon.h"

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
        hcf();
    }

    // Ensure we got a framebuffer.
    if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1) {
        hcf();
    }

    framebuffer = framebuffer_request.response->framebuffers[0];
}

void gradient_test(void) {
    qprint("Running gradient test...");

    // Draw gradient on the framebuffer
    volatile uint32_t *fb_ptr = framebuffer->address;
    uint8_t intensity = 0;
    while (intensity < UINT8_MAX) {
        for (size_t y = 0; y < framebuffer->height; y++) {
            for (size_t x = 0; x < framebuffer->width; x++) {
                uint32_t nX = x * intensity / framebuffer->width;
                uint32_t nY = y * intensity / framebuffer->height;
                fb_ptr[y * (framebuffer->pitch / 4) + x] = ((nY << 8) | nX);
            }
        }
        intensity += 5;
    }
}

void draw_pixel(uint32_t x, uint32_t y, uint32_t color) {
    volatile uint32_t *fb_ptr = framebuffer->address;

    fb_ptr[(y * (framebuffer->pitch / 4)) + x] = color;
}

int screen_dimensions(char d) {
    if (d == 'w') {
        return framebuffer->width;
    } else if (d == 'h') {
        return framebuffer->height;
    } else {
        return -1;
    }
}
