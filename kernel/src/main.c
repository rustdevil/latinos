#include <stdint.h> // For stuff like uint64_t
#include <stddef.h>
#include <stdbool.h>
#include "string.h"
#include "core/panic.h"
#include "graphics/framebuffer.h"
#include "graphics/character/character.h"
#include "com/debugcon.h"
#include "core/gdt.h"
#include "memory.h" // IWYU pragma: keep

// Kernel's entry point
void kmain(void) {
    framebuffer_init();

    qprint("Initializing GDT");
    gdt_init();

    char src_str[] = "Hello";
    char dest_str[128] = "World";
    qprint(strcat(dest_str, src_str));

    gradient_test();

    char character_set[130];

    qprint("Populating character set with characters");
    int i = 0;
    for (char c = 0x01; c <= 0x7E; c++) {
        character_set[i] = c;
        i++;
    }
    character_set[i] = '\0';

    qprint("Printing character test");
    p_fprint(character_set, 0xFFFFFFFF);
    p_fprint("\n\n\nLatinOS v0.1.0-dev\n", 0xFFFFFFFF);

    draw_3d_rect(650, 150, 400, 250);
    for (int i = 0; i <= 125; i += 25) {
        draw_window(600 + i, 100 + i, 400, 250, "400x250 window");
    }

    draw_window(50, 100, 400, 5000, "Clipping test (height 5000)");

    draw_window(500, 500, 50, 50, "50x50 window Overflow testttttttttttttttttttttttt");
    // draw_rect(203, 128, 400, 250, 0xFFFF0000);

    qprint("\nDone, halted.\n\n");

    // We're done, just hang...
    hcf();
}
