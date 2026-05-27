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

build/kernel.o: init kernel.c
	i686-elf-gcc -c kernel.c -o build/kernel.o -ffreestanding -Wall -Wextra

build/kernel.bin: build/boot.o build/kernel.o
	i686-elf-gcc -T linker.ld -o build/kernel.bin -ffreestanding -O2 -nostdlib build/boot.o build/kernel.o -lgcc
