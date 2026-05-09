#include "core/panic.h"
#include "com/debugcon.h"

// Halt and catch fire function.
void hcf(void) {
    for (;;) {
        asm ("hlt");
    }
}

void panic(char *c) {
    qprint(c);

    hcf();
}
