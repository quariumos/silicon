add-symbol-file kernel.bin
target remote | qemu-system-i386 -gdb stdio -cdrom kernel.iso