#include "gdt.h"

void create_gdt_entry(gdt_layout_t* entry, uint32_t limit, uint32_t base, uint8_t access, uint8_t flags) {
  uint16_t limit_low = limit & 0x0000FFFF;
  uint8_t limit_high = (limit & 0x000F0000)>>16;
  entry->limit_low = limit_low;
  entry->flags_and_limit_high = flags<<4 | limit_high;
  entry->access = access;

  uint16_t base_low = base & 0x0000FFFF;
  uint8_t base_mid = (base & 0x00FF0000)>>16;
  uint8_t base_high = (base & 0xFF000000)>>24;
  entry->base_low = base_low;
  entry->base_mid = base_mid;
  entry->base_high = base_high;
}
