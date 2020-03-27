
#include <types.h>
#include <memory.h>
#include <cpu/port.h>
#include <io/serial.h>
#include <cpu/gdt.h>


#define SILICON_IO
#define SILICON_INTERRUPTS

#ifdef SILICON_INTERRUPTS
#include <cpu/idt.h>
#endif

#ifdef SILICON_IO
#include <io/tty/print.h>
#endif

// Kernel will only provide(once it's ready to) IPC/Messaging, Memory allocation interface and a basic text mode + keyboard drivers
// All other functionality will be modular, as in modular kernels and microkernels
void kmain()
{
#ifdef SILICON_IO
    u16 whitefore = vid_color(WHITE, BLACK);
    u16 blackfore = vid_color(BLACK, WHITE);
    vid_cursor_set(15, 15);
    vid_clear(NILINIL, whitefore);
#endif
#ifdef SILICON_INTERRUPTS
#endif
    for (u32 i = 0; i < 10; i++)
    {
        kprint(NILINIL, "Silicon Kernel loaded.\n", whitefore);
    }
#ifdef SILICON_IS_DEBUG_MODE
    serial(COM1); // Enable serial port 1
    serial_write_string(COM1, "Kernel Loaded.");
    serial_write(COM1, 10);
#endif
    for (;;)
        asm("hlt");
}