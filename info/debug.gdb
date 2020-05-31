target remote localhost:1234
symbol-file obj/kernel.elf
continue
kilall qemu-system-${ARCH}
quit