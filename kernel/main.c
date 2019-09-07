
#define DEBUG

#include <core/def.h>
#include <core/sys/idt.h>
#include <core/sys/exc.h>


// Kernel will only provide(once it's ready to) IPC/Messaging, Memory allocation interface and a basic text mode + keyboard drivers
// All other functionality will be modular, as in modular kernels and microkernels
void kmain()
{
    idt();
#ifdef DEBUG
    screen(VIDEO_MEMORY);
#endif
    // Generic handler stubs for exceptions, for now
    for (u32 i = 0; i < 14; i++)
    {
        isr(i, generic_exception_handler);
    }
    asm("sti");
    for (;;)
        asm("hlt");
}