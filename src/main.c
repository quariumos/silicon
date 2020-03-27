
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

__attribute__ ((interrupt))
void stub_exception_handler(struct interrupt_frame *frame)
{
    serial_write_string(COM1, "uh oh, an exception occured\n");
}

// Kernel will only provide(once it's ready to) IPC/Messaging, Memory allocation interface and a basic text mode + keyboard drivers
// All other functionality will be modular, as in modular kernels and microkernels
void kmain()
{
    serial_init(COM1);
    // NULL descriptor
    set_gdt_entry(0, 0, 0, 0, 0);

    // Code segment
    set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    // Data segment
    set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    install_gdt(3);
    for (s32 i = 0; i < 32; ++i)
    {
        set_idt_entry(i, stub_exception_handler);
    }
    remap_pic(32, 47);
    install_idt();
#ifdef SILICON_IO
    u16 whitefore = vid_color(WHITE, BLACK);
    u16 blackfore = vid_color(BLACK, WHITE);
    vid_cursor_set(15, 15);
    vid_clear(NILINIL, whitefore);
#endif
#ifdef SILICON_INTERRUPTS
#endif
    kprint(NILINIL, "Silicon Kernel loaded.\n", whitefore);
#ifdef SILICON_IS_DEBUG_MODE
    serial_write_string(COM1, "Kernel Loaded.");
    serial_write(COM1, 10);
#endif
    for (;;)
        asm("hlt");
}