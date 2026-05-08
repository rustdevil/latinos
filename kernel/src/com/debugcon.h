#ifndef DEBUGCON_H
#define DEBUGCON_H

static inline void qemu_putc(char c) {
    asm volatile("outb %0, %1" : : "a"(c), "Nd"(0xe9));
}

static inline void qprint(const char *s) {
    qemu_putc('\n');
    while (*s != '\0') {
        qemu_putc(*s);
        s++;
    }
}

#endif
