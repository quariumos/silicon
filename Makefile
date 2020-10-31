_CC=ccache clang
ARCH?=i386
_CLANG_TRIPLE=${ARCH}-pc-none-bin

FLAGS?=-DSHOULD_LOG -DLOG_MICRO_EVENTS -DLOG_STACK_ON_GPF

_CF= -I src/include -target ${_CLANG_TRIPLE} -DARCH=${ARCH} -ffreestanding -g ${FLAGS}
_EF= -no-reboot -m 2M -serial stdio

DIST=dist

kernel.iso: obj/kernel.elf
	cp $< iso/boot
	grub-mkrescue -d /usr/lib/grub/i386-pc -o $@ iso

run: clean kernel.iso
	qemu-system-${ARCH} ${_EF} -cdrom kernel.iso

obj/ksym.o:
	nm -g obj/kernel.o | grep T | sed -e 's/ T /: /g' > info/kernel.sym
	ld -m elf_i386 -r -b binary -o $@ info/kernel.sym

obj/kernel.elf: obj/multiboot.o obj/start.o obj/kernel_asm.o obj/kernel.o obj/ksym.o
	ld -m elf_i386 -T info/linker.ld -o $@ $^

debug: clean kernel.iso
	qemu-system-${ARCH} ${_EF} -s -S -cdrom kernel.iso & ARCH=${ARCH} gdb --batch -x info/debug.gdb

obj/kernel.o:
	${_CC} -c -o $@ ${_CF} src/main.c

obj/kernel_asm.o:
	nasm -f elf32 src/kernel/*.s -o $@

obj/start.o:
	nasm -f elf32 src/start.s -o $@

obj/multiboot.o:
	nasm -f elf32 src/multiboot2.s -o $@

clean:
	rm -rf kernel.elf kernel.iso iso/boot/*.elf obj/*