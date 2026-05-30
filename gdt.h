#pragma once

#include "types.h"

#define GDT_BASE 0
#define GDT_NULL_LIMIT 0x00000000
#define GDT_NULL_ACCESS_BYTE 0x00
#define GDT_NULL_FLAGS 0x0
#define GDT_KERNEL_CODE_ACCESS_BYTE 0x9A
#define GDT_KERNEL_DATA_ACCESS_BYTE 0x92
#define GDT_LIMIT 0xFFFFF
#define GDT_FLAGS 0xC

typedef struct {
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t base_mid;
  uint8_t access;
  uint8_t flags_and_limit_high;
  uint8_t base_high;
} __attribute__((packed)) gdt_layout_t;

typedef struct {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) gdt_ptr;

extern void gdt_load(gdt_ptr* ptr);
extern void create_gdt_entry(gdt_layout_t* entry, uint32_t limit, uint32_t base, uint8_t access, uint8_t flags);
