_CC=clang
ARCH?=i386
_CLANG_TRIPLE=${ARCH}-pc-none-bin

_CF= -I src/include -target ${_CLANG_TRIPLE} -DARCH=${ARCH} -ffreestanding -g
_EF= -no-reboot -m 2M -serial stdio

DIST=dist

run: clean kernel.iso sym remove_obj
	qemu-system-${ARCH} ${_EF} -cdrom kernel.iso

sym:
	objdump --syms ${DIST}/kernel.elf > ${DIST}/kernel.sym

debug: clean kernel.iso
	qemu-system-${ARCH} ${_EF} -s -S -cdrom kernel.iso & gdb --batch -x kernel.gdb

kernel.iso: kernel.elf
	cp ${DIST}/kernel.elf iso/boot
	grub2-mkrescue -d /usr/lib/grub/i386-pc -o ${DIST}/$@ iso

start.o:
	nasm -f elf32 src/start.s -o $@

multiboot.o:
	nasm -f elf32 src/multiboot2.s -o $@

kernel.elf: multiboot.o start.o kernel.o
	ld -m elf_i386 -T linker.ld -o ${DIST}/$@ $^

kernel.o:
	${_CC} -c -o $@ ${_CF} src/main.c

remove_obj:
	rm -rf *.o ${DIST}/*.elf

clean:
	rm -rf ${DIST} iso/boot/*.elf
	mkdir ${DIST}