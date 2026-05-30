all: build/kernel.bin

.PHONY: all clean init run

init:
	mkdir -p build/

clean:
	rm -rf build/

run: build/kernel.bin
	qemu-system-i386 -kernel build/kernel.bin

build/boot.o: init boot.asm
	nasm -f elf32 boot.asm -o build/boot.o

build/gdt_asm.o: init gdt.asm
	nasm -f elf32 gdt.asm -o build/gdt_asm.o

build/kernel.o: init kernel.c
	i686-elf-gcc -c kernel.c -o build/kernel.o -ffreestanding -Wall -Wextra

build/gdt.o: init gdt.c
	i686-elf-gcc -c gdt.c -o build/gdt.o -ffreestanding -Wall -Wextra

build/kernel.bin: build/boot.o build/kernel.o build/gdt_asm.o build/gdt.o
	i686-elf-gcc -T linker.ld -o build/kernel.bin -ffreestanding -O2 -nostdlib build/boot.o build/kernel.o build/gdt_asm.o build/gdt.o -lgcc
