#include "core/panic.h"

// Halt and catch fire function.
void hcf(void) {
    for (;;) {
        asm ("hlt");
    }
}
