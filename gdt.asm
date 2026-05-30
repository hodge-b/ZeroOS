global gdt_load

section .text
  gdt_load:
    mov eax, [esp + 4]
    lgdt [eax]

  reload_segments:
    jmp 0x08:reload_cs

  reload_cs:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret
