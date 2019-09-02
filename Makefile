
CC = clang
KERNEL_START= 0x2000
BOOTLOADER= quarz

CFLAGS= -ffreestanding
LDFLAGS= -nostdlib  -Ttext ${KERNEL_START} 
NAME= quar


run: quar.iso
	qemu-system-i386 -net none -m 1G -fda $<

quar.iso: ${BOOTLOADER} ${NAME}.tmp
	cat $^ > $@

${BOOTLOADER}: clean
	nasm boot/${BOOTLOADER}/boot.asm -f bin -o $@

${NAME}.tmp:
	${CC} ${CFLAGS} -o ${NAME}.o -c kernel/main.c
	${CC} ${LDFLAGS} -o $@ ${NAME}.o

clean:
	rm -rf *.iso *.o *.tmp ${BOOTLOADER}