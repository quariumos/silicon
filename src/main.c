
#include <types.h>
#include <memory.h>
#include <cpu/port.h>
#include <cpu/gdt.h>

#define SILICON_IO
#define SILICON_INTERRUPTS

#ifdef SILICON_INTERRUPTS
#include <cpu/idt.h>
#endif

#ifdef SILICON_IO
#define IO_PRINT_SERIAL
#define IO_PRINT_TEXT
#include <io/kprint.h>
#endif


__attribute__ ((interrupt))
void stub_exception_handler(struct interrupt_frame *frame)
{
    kprint(PRINTF_SERIAL, "uh oh, an exception occured\n");
}

// Kernel will only provide(once it's ready to) IPC/Messaging, Memory allocation interface and a basic text mode + keyboard drivers
// All other functionality will be modular, as in modular kernels and microkernels
void kmain()
{
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
#endif
#ifdef SILICON_INTERRUPTS
#endif
    kprint(PRINTF_TEXT, "Silicon Kernel loaded.\n");
#ifdef SILICON_IS_DEBUG_MODE
    dbg("Kernel loaded");
#endif
    for (;;)
        asm("hlt");
}