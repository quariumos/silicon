_CC=clang
_ARCH?=i386
_CLANG_TRIPLE=${_ARCH}-pc-none-bin

TARGET= ${ARCH}-pc-none-bin

_CF= -I src/headers -target ${_CLANG_TRIPLE} -DSILICON_IS_DEBUG_MODE -ffreestanding -g
_EF= -no-reboot -net none -m 2M
NAME= r0

run: clean kernel.iso
	qemu-system-${_ARCH} ${_EF} -cdrom kernel.iso

kernel.iso: kernel.bin
	cp kernel.bin iso/boot
	grub-mkrescue -d /usr/lib/grub/i386-pc -o $@ iso

start.o:
	nasm -f elf32 src/start.asm -o $@

multiboot.o:
	nasm -f elf32 src/multiboot2.s -o $@

kernel.bin: multiboot.o start.o kernel.o
	ld -m elf_i386 -T linker.ld -o $@ $^

kernel.o:
	${_CC} -c -o $@ ${_CF} src/main.c

clean:
	rm -rf *.bin *.o *.iso iso/boot/*.bin