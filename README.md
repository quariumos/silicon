# Silicon
This repository contains all the code for the QuariumOS kernel, Silicon.
QuariumOS should be located in another repository somewhere in this organization, but it will likely be so only when the kernel is in it's alpha stage.
## What you can use it for:
Once it actually gets to be something you want to use, feel free to:
1. Make cool embedded stuff with it
2. Use it as kernel for your own OS
3. Or make it a base for your own kernel

## Progress:
v0.1:
1. Text mode driver for debugging, stub for keyboard driver / done
2. Proper IDT / done
3. Very simplistic bootloader / done
4. Serial IO / done
5. Exception handling / partial, dumped via serial port in DEBUG mode
6. Kernel, memory allocation / TODO

v0.2:
1. Module loading / TODO
2. Kernel Threads / TODO