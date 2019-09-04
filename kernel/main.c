
#include <core/def.h>
#include <core/tables/idt.h>
#include <core/screen/print.h>

void kmain()
{
    // I'm just testing here, ignore it
    asm("cli");
    idt_init();
    outb(0x21, 0xfd);
    outb(0xa1, 0xff);
    asm("sti");
    screen(VIDEO_MEMORY);
    for (;;)
        asm("hlt");
}