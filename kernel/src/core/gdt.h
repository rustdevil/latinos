#ifndef GDT_H
#define GDT_H

#include <stdint.h>

struct GDTEntry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t flags;
    uint8_t base_high;
} __attribute__((packed));

struct GDT {
    struct GDTEntry entries[3];
} __attribute__((packed));

struct GDTPointer {
    uint16_t size;
    uint64_t addr;
} __attribute__((packed));

extern struct GDT gdt;
extern struct GDTPointer gdt_ptr;

void gdt_init();
extern void gdt_load(struct GDTPointer* ptr);

#endif
