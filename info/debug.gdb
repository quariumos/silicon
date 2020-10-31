target remote localhost:1234
symbol-file obj/kernel.elf
continue
killall qemu-system-${ARCH}
quit