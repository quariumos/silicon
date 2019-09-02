
#include <core/irq.h>

void kmain()
{
    idt_init();
    out_byte(0x21, 0xfd);
    out_byte(0xa1, 0xff);
    asm("sti");
    for (;;)
        asm("hlt");
}