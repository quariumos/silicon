
CC= clang
ACC= gcc
KERNEL_START= 0x2000
BOOTLOADER= quarz

INCLUDE= include/

EMUFLAGS= -serial stdio -net none -m 1G -fda
CFLAGS= -ffreestanding -I${INCLUDE} -m32 -Wno-attributes
LDFLAGS= -m elf_i386 -nostdlib -Ttext ${KERNEL_START}

NAME= quar

run: clean ${NAME}.iso
	qemu-system-i386 ${EMUFLAGS} ${NAME}.iso

quar.iso: ${BOOTLOADER} ${NAME}
	cat $^ > $@

${BOOTLOADER}: clean
	nasm boot/${BOOTLOADER}/boot.asm -f bin -o $@

entry.o:
	${ACC} ${CFLAGS} -o entry.o -c kernel/entry.c

kernel.o:
	${CC} ${CFLAGS} -o $@ -c kernel/main.c

x86.o:
	nasm -f elf include/sys/assembly/x86.asm -o $@

${NAME}: entry.o kernel.o x86.o
	ld ${LDFLAGS} -o $@ $^

clean:
	rm -rf *.iso *.o *.tmp ${NAME} ${BOOTLOADER}