#include "core/panic.h"
#include "com/debugcon.h"
#include "graphics/character/character.h"
#include "graphics/framebuffer.h"
#include "string.h"
#include "memory.h"

// Halt and catch fire function.
void hcf(void) {
    for (;;) {
        asm ("hlt");
    }
}

int panic_count = 0;
void panic(char *c) {
    // If we panic while panicking, just halt.
    if (panic_count > 0) {
        hcf();
    }

    panic_count++;
    clear_screen();

    char text[1024] = "*** Fatal Error *** (LatinOS)\nPANIC: ";

    if (strlen(text) + strlen(c) + 1 <= 1024) {
        qprint(strcat(text, c));
        p_fprint(text, 0x00FF0000);
    } else {
        qprint("PANIC: system panicked, too many characters in panic message");
        p_fprint("PANIC: (too many characters)", 0x00FF0000);
    }

    hcf();
}
