
#define DEBUG

#include <core/def.h>
#include <core/sys/idt.h>
#include <core/sys/exc.h>

#ifdef KIO
#include <io/i/keyboard.h>
#include <io/o/screen/print.h>
#endif

// Kernel will only provide(once it's ready to) IPC/Messaging, Memory allocation interface and a basic text mode + keyboard drivers
// All other functionality will be modular, as in modular kernels and microkernels
void kmain()
{
    idt();
    // Generic handler stubs for exceptions, for now
    for (u32 i = 0; i < 14; i++)
    {
        isr(i, generic_exception_handler);
    }
    asm("sti");
#ifdef KIO
    screen(VIDEO_MEMORY);
    keyboard();
#endif
#ifdef DEBUG
    serial(COM1); // Enable serial port 1
#endif
    for (;;)
        asm("hlt");
}