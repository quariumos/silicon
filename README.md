### Warning
If the resulting .iso file fails to run properly, try compiling it on Ubuntu,
for an unknown reason Clang-10 produces faulty code on other distributions of Linux (particularly Fedora),
you can also try using older versions of Clang.

# Silicon
This repository contains all the code for the QuariumOS kernel, Silicon.
QuariumOS should be located in another repository somewhere in this organization, but it will likely be so only when the kernel is in it's alpha stage.

## Running the kernel
> Using Ubuntu Linux is optimal
> So far it has only been successfully built on Ubuntu 16.04, 18.04, 20.04 and Clear Linux
Build requirements:
1. grub-mkrescue and xorisso: `xorriso` on Ubuntu, `libisoburn` on Clear Linux
2. clang (theoretically a gcc-based cross compiler could work too), ld and nasm
3. nm, grep and sed for symbol extraction (optional, set PARSE_SYMBOLS to 0 disable)

## Progress:
v0.1:
- [x] Text mode driver for debugging
- [x] Proper IDT
- [x] Serial IO
- [x] Fancy virtual device-based IO system
- [x] PS/2 Keyboard input
- [x] Exception handling
- [ ] Kernel, memory allocation

v0.1,5:
- [ ] GUI stubs
- [ ] `write`, `read`, `close` and `device` syscalls
- [ ] TAR format support

v0.2:
- [ ] Kernel Threads
- [ ] FAT16 support

v0.3
- [ ] Executable parsing
