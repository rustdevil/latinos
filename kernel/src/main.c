#include <stdint.h> // For stuff like uint64_t
#include <stddef.h>
#include <stdbool.h>
#include "panic.h"
#include "graphics/framebuffer.h"
#include "graphics/character/character.h"
#include "com/debugcon.h"

// Memory functions.

// Copy memory from src to destination.
// restrict means we trust that dest and src do not overlap.
void *memcpy(void *restrict dest, const void *restrict src, size_t n) {
    uint8_t *restrict pdest = dest;
    const uint8_t *restrict psrc = src;

    for (size_t i = 0; i < n; i++) {
        pdest[i] = psrc[i];
    }

    return dest;
}

void *memset(void *dest, int value, size_t n) {
    uint8_t *pdest = dest;

    for (size_t i = 0; i < n; i++) {
        pdest[i] = (uint8_t)value;
    }

    return dest;
}

void *memmove(void *dest, const void *src, size_t n) {
    uint8_t *pdest = dest;
    const uint8_t *psrc = src;

    if ((uintptr_t)src > (uintptr_t)dest) {
        for (size_t i = 0; i < n; i++) {
            pdest[i] = psrc[i];
        }
    } else if ((uintptr_t)src < (uintptr_t)dest) {
        for (size_t i = n; i > 0; i--) {
            pdest[i-1] = psrc[i-1];
        }
    }

    return dest;
}

int memcmp(const void *s1, const void *s2, size_t n) {
    const uint8_t *p1 = s1;
    const uint8_t *p2 = s2;

    for (size_t i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] < p2[i] ? -1 : 1;
        }
    }

    return 0;
}

// Kernel's entry point
void kmain(void) {
    framebuffer_init();

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
    p_fprint(character_set);
    p_fprint("\n\n\nLatinOS v0.1.0-dev\n");

    qprint("\nDone, halted.\n\n");

    // We're done, just hang...
    hcf();
}
