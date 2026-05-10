#include "core/panic.h"
#include "com/debugcon.h"
#include "string.h"

// Halt and catch fire function.
void hcf(void) {
    for (;;) {
        asm ("hlt");
    }
}

void panic(char *c) {
    char text[1024] = "PANIC: ";

    if (strlen(text) + strlen(c) + 1 <= 1024) {
        qprint(strcat(text, c));
    } else {
        qprint("PANIC: system panicked, too many characters in panic message");
    }

    hcf();
}
