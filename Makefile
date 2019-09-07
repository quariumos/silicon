
CC= clang
ACC= gcc
KERNEL_START= 0x2000
BOOTLOADER= quarz

INCLUDE= include/

EMUFLAGS= -d int -net none -m 1G -fda
CFLAGS= -ffreestanding -I${INCLUDE} -m32 -Wno-attributes
LDFLAGS= -m elf_i386 -nostdlib -Ttext ${KERNEL_START}
NAME= quar

run: ${NAME}.iso
	qemu-system-i386 ${EMUFLAGS} $<

quar.iso: ${BOOTLOADER} ${NAME}.tmp
	cat $^ > $@

${BOOTLOADER}: clean
	nasm boot/${BOOTLOADER}/boot.asm -f bin -o $@

${NAME}.tmp:
	nasm -f elf include/core/sys/assembly/idt.asm -o idt.o
	${ACC} ${CFLAGS} -o entry.o -c kernel/entry.c
	${CC} ${CFLAGS} -o ${NAME}.o -c kernel/main.c
	ld ${LDFLAGS} -o $@ entry.o ${NAME}.o idt.o 

clean:
	rm -rf *.iso *.o *.tmp ${BOOTLOADER}