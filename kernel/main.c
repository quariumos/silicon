
#include <core/sys/mem.h>
#include <core/def.h>
#include <core/sys/idt.h>
#include <core/screen/print.h>
#include <core/input/keyboard.h>

void generic_exception_handler(u32 vector)
{
    u16 *whitefore = color(WHITE, BLACK);
    char s[2];
    kprint("Exception occured: ", whitefore);
    kprint(_dec(vector, s), whitefore);
}

// Kernel will only provide(once it's ready to) IPC/Messaging, Memory allocation interface and a basic text mode + keyboard drivers
// All other functionality will be modular, as in modular kernels and microkernels
void kmain()
{
    // I'm just testing here, ignore it
    asm("cli");
    idt_init();
    outb(0x21, 0xfd);
    outb(0xa1, 0xff);
    asm("sti");
    screen(VIDEO_MEMORY);
    register_isr(33, kb_handler);
    // Generic handler stubs for exceptions, for now
    for (u32 i = 0; i < 14; i++)
    {
        register_isr(i, generic_exception_handler);
    }
    for (;;)
        asm("hlt");
}