### Warning
If the resulting .iso file fails to run properly, try compiling it on Ubuntu,
for an unknown reason Clang-10 produces faulty code on other distributions of Linux
(you can also try using older versions of Clang)

# Silicon
This repository contains all the code for the QuariumOS kernel, Silicon.
QuariumOS should be located in another repository somewhere in this organization, but it will likely be so only when the kernel is in it's alpha stage.
## What you can use it for:
Once it actually gets to be something you want to use, feel free to:
1. Make cool embedded stuff with it
2. Use it as kernel for your own OS
3. Or make it a base for your own kernel

## Running the kernel
Build requirements:
1. grub-mkrescue and xorisso
2. clang (theoretically a gcc-based cross compiler could work too) (tested on Ubuntu 20.04, not guaranteed to work anywhere else)
3. ld
4. nasm

## Progress:
v0.1:
- [x] Text mode driver for debugging
- [x] Proper IDT
- [x] Serial IO
- [x] Fancy virtual device-based IO system
- [ ] Keyboard driver
- [ ] Exception handling
- [ ] Kernel, memory allocation

v0.2:
- [ ] Kernel Threads
- [ ] FAT16 support

v0.3
- [ ] Executable parsing
