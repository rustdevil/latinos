#include "gdt.h"
#include "com/debugcon.h"
#include <stdint.h>
#include <sys/cdefs.h>

struct GDT gdt;
struct GDTPointer gdt_ptr;

void gdt_set_entry(int i, uint8_t access, uint8_t flags) {
    gdt.entries[i].limit_low = 0;
    gdt.entries[i].base_low = 0;
    gdt.entries[i].base_middle = 0;
    gdt.entries[i].access = access;
    gdt.entries[i].flags = flags;
    gdt.entries[i].base_high = 0;
}

void gdt_init() {
    qprint("Initializing GDT...\n");
    gdt_set_entry(0, 0, 0); // Null descriptor
    gdt_set_entry(1, 0x9A, 0x20);
    gdt_set_entry(2, 0x92, 0x00);

    gdt_ptr.size = sizeof(gdt) - 1;
    gdt_ptr.addr = (uint64_t)&gdt;

    gdt_load(&gdt_ptr);
}
