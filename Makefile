_CC=clang
_ARCH?=i386
_CLANG_TRIPLE=${_ARCH}-pc-none-bin

TARGET= ${ARCH}-pc-none-bin

_CF= -I src/headers -target ${_CLANG_TRIPLE} -DSILICON_IS_DEBUG_MODE -ffreestanding
_EF= -no-reboot -serial stdio -net none -m 2M
NAME= r0

run: clean kernel.iso
	qemu-system-${_ARCH} ${_EF} -cdrom kernel.iso

kernel.iso: kernel.bin
	cp kernel.bin iso/boot
	grub-mkrescue -d /usr/lib/grub/i386-pc -o $@ iso

multiboot.o:
	nasm -f elf32 src/multiboot2.s -o $@

kernel.bin: multiboot.o kernel.o
	ld -m elf_i386 -T linker.ld -o $@ $^

kernel.o:
	${_CC} -c -o $@ ${_CF} src/main.c

clean:
	rm -rf *.bin *.o *.iso iso/boot/*.bin