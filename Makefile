
CC= clang
ACC= gcc
BOOTLOADER= quarz

INCLUDE= include/

EMUFLAGS= -serial stdio -net none -m 1G -fda
CFLAGS= -ffreestanding -I${INCLUDE} -m32 -Wno-attributes
LDFLAGS= -m elf_i386 -nostdlib -T linker.ld

NAME= quar

run: clean ${NAME}.iso
	qemu-system-i386 ${EMUFLAGS} ${NAME}.iso

${NAME}.iso: ${BOOTLOADER} ${NAME}
	rm -rf ${NAME}.iso
	cat $^ > $@

${BOOTLOADER}: clean
	nasm boot/${BOOTLOADER}/x86.asm -f bin -o $@

entry.o:
	${ACC} ${CFLAGS} -o entry.o -c kernel/entry.c

kernel.o:
	${CC} ${CFLAGS} -o $@ -c kernel/main.c

x86.o:
	nasm -f elf include/sys/asm/x86.asm -o $@

${NAME}: entry.o kernel.o x86.o
	ld ${LDFLAGS} -o $@ $^

clean:
	rm -rf *.o *.tmp *.iso ${NAME} ${BOOTLOADER}