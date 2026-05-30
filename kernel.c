#include "types.h"
#include "gdt.h"

typedef struct {
  uint8_t value;
  uint8_t color;
} vga_entry_t;

#define VGA_MEMORY 0xB8000
#define VGA_COLOR 0x0F
#define VGA_CLEAR 0x00
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

void vga_buffer_init(uint16_t* vga) {
  uint16_t size = VGA_WIDTH * VGA_HEIGHT;
  for (uint16_t i = 0; i < size; i++) {
    vga[i] = ' ' | VGA_COLOR << 8;
  }
}

void kernel_main(void) {
  uint16_t* vga = (uint16_t*)VGA_MEMORY;
  vga_buffer_init(vga);

  unsigned char message[] = "Hello ZeroOS!";

  uint8_t i = 0;
  while(message[i] != '\0') {
    vga[i] = message[i] | VGA_COLOR << 8;
    i++;
  }

  gdt_layout_t gdt[3];
  create_gdt_entry(&gdt[0], GDT_NULL_LIMIT, GDT_BASE, GDT_NULL_ACCESS_BYTE, GDT_NULL_FLAGS); // Null descriptor.
  create_gdt_entry(&gdt[1], GDT_LIMIT, GDT_BASE, GDT_KERNEL_CODE_ACCESS_BYTE, GDT_FLAGS);    // Kernel code descriptor.
  create_gdt_entry(&gdt[2], GDT_LIMIT, GDT_BASE, GDT_KERNEL_DATA_ACCESS_BYTE, GDT_FLAGS);    // Kernel data descriptor.

  gdt_ptr gdt_register;
  gdt_register.limit = (3 * 8) - 1;              // TODO: Move this into a length check utils func.
  gdt_register.base = (uint32_t)&gdt;
  gdt_load(&gdt_register);

  while (1) {}
}

