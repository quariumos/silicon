
CC= tcc
KERNEL_START= 0x2000
BOOTLOADER= quarz

INCLUDE= include/

CFLAGS= -ffreestanding -I${INCLUDE} -m32 -masm=intel
LDFLAGS= -m elf_i386 -nostdlib -Ttext ${KERNEL_START}
NAME= quar

run: ${NAME}.iso
	qemu-system-i386 -net none -m 1G -fda $<

quar.iso: ${BOOTLOADER} ${NAME}.tmp
	cat $^ > $@

${BOOTLOADER}: clean
	nasm boot/${BOOTLOADER}/boot.asm -f bin -o $@

${NAME}.tmp:
	nasm -f elf include/core/def.asm -o def.o
	${CC} ${CFLAGS} -o entry.o -c kernel/entry.c
	${CC} ${CFLAGS} -o ${NAME}.o -c kernel/main.c
	ld ${LDFLAGS} -o $@ entry.o def.o ${NAME}.o

clean:
	rm -rf *.iso *.o *.tmp ${BOOTLOADER}