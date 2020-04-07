
#include <io/log.h>
#include <cpu/isr.h>

#include <io/duplex/serial.h>
#include <io/in/kbd.h>
#include <io/out/text.h>

void kmain()
{
    isr_init();
    text.init(text.id);
    serial.init(serial.id);
    klog("Silicon Kernel loaded.\n", "");
    for (;;)
        asm("hlt");
}
