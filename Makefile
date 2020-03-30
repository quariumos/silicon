_CC=clang
_ARCH?=i386
_CLANG_TRIPLE=${_ARCH}-pc-none-bin

TARGET= ${ARCH}-pc-none-bin

_CF= -I src/headers -target ${_CLANG_TRIPLE} -DSILICON_IS_DEBUG_MODE -ffreestanding
_EF= -serial stdio -net none -m 2M
NAME= r0

run: clean kernel.bin
	qemu-system-${_ARCH} ${_EF} -kernel kernel.bin

kernel.bin: boot.o kernel.o
	ld -m elf_i386 -T linker.ld -o $@ $^

boot.o:
	nasm -f elf32 iso/base.asm -o $@

kernel.o:
	${_CC} -c -o $@ ${_CF} src/main.c

clean:
	rm -rf *.bin *.o *.iso