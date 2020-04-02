_CC=clang
ARCH?=i386
_CLANG_TRIPLE=${ARCH}-pc-none-bin

_CF= -I src/include -target ${_CLANG_TRIPLE} -DARCH=${ARCH} -ffreestanding -g
_EF= -no-reboot -m 2M -serial stdio

run: clean kernel.iso
	qemu-system-${ARCH} ${_EF} -cdrom kernel.iso

debug: clean kernel.iso
	qemu-system-${ARCH} ${_EF} -s -S -cdrom kernel.iso & gdb -x kernel.gdb

kernel.iso: kernel.elf
	cp kernel.elf iso/boot
	grub2-mkrescue -d /usr/lib/grub/i386-pc -o $@ iso

irq.o:
	nasm -f elf32 src/isr.s -o $@

start.o:
	nasm -f elf32 src/start.s -o $@

multiboot.o:
	nasm -f elf32 src/multiboot2.s -o $@

kernel.elf: multiboot.o start.o irq.o kernel.o
	ld -m elf_i386 -T linker.ld -o $@ $^

kernel.o:
	${_CC} -c -o $@ ${_CF} src/main.c

clean:
	rm -rf *.o *.iso iso/boot/*.elf