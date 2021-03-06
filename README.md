# Silicon
This repository contains all the code for the QuariumOS kernel, Silicon.
QuariumOS should be located in another repository somewhere in this organization, but it will likely be so only when the kernel is in it's alpha stage.

## Running the kernel
> Using Ubuntu Linux LTS is optimal
> So far it has only been successfully built on:
1. Ubuntu 16.04, 18.04, 20.04 
2. Clear Linux

Build requirements:
1. **grub-mkrescue** & **xorisso**: `xorriso` on Ubuntu, `libisoburn` on Clear Linux and most other systems
2. **clang** & **ccache** (theoretically a gcc-based cross compiler could work too)
3. **ld**
4. **nasm**
5. **nm**, **grep** & **sed** for symbol extraction

## Progress:
v0.1:
- [x] Text mode driver for debugging
- [x] Proper IDT
- [x] Serial IO
- [x] Fancy virtual device-based IO system
- [x] PS/2 Keyboard input
- [x] Exception handling
- [ ] Kernel, memory allocation

v0.1.5:
- [ ] GUI stubs
- [ ] `write`, `read`, `close` and `device` syscalls
- [ ] TAR format support

v0.2:
- [ ] Kernel Threads
- [ ] FAT16 support

v0.3
- [ ] Executable parsing
