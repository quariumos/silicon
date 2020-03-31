

#include <io/duplex/serial.h>
#include <io/in/kbd.h>
#include <io/out/text.h>
#include <io/conversion.h>

void kbd_log(u8 data)
{
    serial.out_device.write(data);
    text.out_device.write(data);
}

void kmain()
{
    remap_pic(32, 47);
    install_idt();
    // kprint(PRINTF_TEXT, "Silicon Kernel loaded.\n");
    serial.init();
    kbd.init();
    text.init();
    kbd.in_device.stream->subscribe(kbd_log);
    for (;;)
        asm("hlt");
}