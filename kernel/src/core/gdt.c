#include "gdt.h"
#include <stdint.h>

struct GdtEntry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute((packed))__;
