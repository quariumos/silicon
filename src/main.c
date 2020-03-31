

#include <io/duplex/serial.h>
#include <io/in/kbd.h>

void kmain()
{
    remap_pic(32, 47);
    install_idt();
    // kprint(PRINTF_TEXT, "Silicon Kernel loaded.\n");
    serial.init();
    kbd.init();
    serial.out_device.write('C');
    for (;;)
        asm("hlt");
}