#include "core/panic.h"
#include "com/debugcon.h"
#include "graphics/character/character.h"
#include "graphics/framebuffer.h"

// Halt and catch fire function.
void hcf(void) {
    asm ("cli"); // Disable interrupts
    for (;;) {
        asm ("hlt");
    }
}


void panic(char *msg) {
    asm volatile ("cli");

    static int nesting = 0;
    if (nesting > 0) hcf();
    nesting++;

    qprint("\nPANIC: ");
    qprint(msg);

    if (has_a_framebuffer()) {
        p_fprint("*** Kernel Panic ***\n", 0xFFFFFFFF);
        p_fprint("panic: ", 0xFFFF1111);
        p_fprint(msg, 0xFFFFFFFF);
    }

    hcf();
}
