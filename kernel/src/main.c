#include <stddef.h>
#include <stdbool.h>
#include "core/panic.h"
#include "graphics/framebuffer.h"
#include "com/debugcon.h"
#include "core/gdt.h"
#include "core/memory.h" // IWYU pragma: keep

// Kernel's entry point
void kmain(void) {
    framebuffer_init();
    gdt_init();

    gradient_test();

    // Window tests

    for (int i = 0; i <= 125; i += 25) {
        draw_window(600 + i, 100 + i, 400, 250, "LatinOS 400x250 window");
    }
    draw_window(50, 100, 400, 5000, "Clipping test (height 5000)");
    draw_window(500, 500, 50, 50, "50x50 window Overflow testttttttttttttttttttttttt");

    // We're done, just hang...
    qprint("\nHanging\n\n");
    hcf();
}
