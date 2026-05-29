#include "types.h"

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

  while (1) {}
}


