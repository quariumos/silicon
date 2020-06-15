_CC=clang
ARCH?=i386
_CLANG_TRIPLE=${ARCH}-pc-none-bin

FLAGS?=-DLOG_MICRO_EVENTS

_CF= -I src/include -target ${_CLANG_TRIPLE} -DARCH=${ARCH} -ffreestanding -g ${FLAGS}
_EF= -no-reboot -m 2M -serial stdio

DIST=dist

run: clean kernel.iso
	qemu-system-${ARCH} ${_EF} -cdrom kernel.iso

sym:
	nm -g obj/kernel.elf > info/kernel.sym

debug: clean kernel.iso
	qemu-system-${ARCH} ${_EF} -s -S -cdrom kernel.iso & ARCH=${ARCH} gdb --batch -x info/debug.gdb

kernel.iso: obj/kernel.elf
	cp $< iso/boot
	grub-mkrescue -d /usr/lib/grub/i386-pc -o $@ iso

obj/kernel.elf: obj/multiboot.o obj/start.o obj/kernel.o
	ld -m elf_i386 -T info/linker.ld -o $@ $^

obj/kernel.o:
	${_CC} -c -o $@ ${_CF} src/main.c

obj/start.o:
	nasm -f elf32 src/start.s -o $@

obj/multiboot.o:
	nasm -f elf32 src/multiboot2.s -o $@

clean:
	rm -rf kernel.elf kernel.iso iso/boot/*.elf obj/*