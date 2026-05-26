MAGIC    equ 0x1BADB002
FLAGS    equ 0x0
CHECKSUM equ -(MAGIC + FLAGS)

global _start

section .text
  dd MAGIC
  dd FLAGS
  dd CHECKSUM

  _start:
    mov esp, stack_top
    call kernel_main

  _loop:
    hlt
    jmp _loop

section .bss
  stack_bottom:
    resb 8192
  stack_top:
