

#include <io/duplex/serial.h>
#include <io/in/kbd.h>
#include <io/out/text.h>
#include <io/conversion.h>
#include <io/kprintf.h>

void kbd_log(u8 data)
{
    serial.out_device.write(data);
    text.out_device.write(data);
}

void kmain()
{
    remap_pic(32, 47);
    install_idt();
    serial.init(serial.id);
    kbd.init(kbd.id);
    text.init(text.id);
    kbd.in_device.stream->subscribe(kbd_log);
    kprintf(text.out_device, ">> Silicon Kernel loaded.\n");
    for (;;)
        asm("hlt");
}