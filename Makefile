
CC= clang-3.9
AS= nasm

BOOTLOADER= quarz

TARGET= i386-pc-none-bin

CF= -nostdlib -ffreestanding -Isrc/inc -target ${TARGET}
EF= -serial stdio -net none -m 1G
NAME= sil

run: clean ${NAME}.iso
	qemu-system-i386 ${EF} -cdrom ${NAME}.iso

${NAME}.iso: ${NAME}.bin
	cp $< iso/boot/kernel.bin
	grub-mkrescue -o $@ iso

${NAME}.bin: bootg.o kernel.o
	${CC} -T linker.ld -o $@ ${CF} $^

bootg.o:
	nasm -f elf32 src/bootg.asm -o bootg.o

kernel.o:
	${CC} ${CF} src/main.c -c -o $@

check: ${NAME}.bin
	if grub-file --is-x86-multiboot ${NAME}.bin; then echo IS Multiboot; else echo IS not multiboot; fi

clean:
	rm -rf iso/boot/kernel.bin
	rm -rf *.bin *.o