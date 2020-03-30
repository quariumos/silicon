
#include <types.h>
#include <memory.h>
#include <cpu/port.h>
#include <cpu/gdt.h>

#define SILICON_IO
#define SILICON_INTERRUPTS

#ifdef SILICON_INTERRUPTS
#include <cpu/irq/idt.h>
#include <cpu/irq/isr.h>
#endif

#ifdef SILICON_IO
#define IO_PRINT_SERIAL
#define IO_PRINT_TEXT
#include <io/kprint.h>
#endif


__attribute__ ((interrupt))
void stub_interrupt_handler(struct interrupt_frame *frame)
{
    kprint(PRINTF_TEXT, "Interrupt occured\n");
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
        set_idt_entry(i, stub_interrupt_handler);
    }
    remap_pic(32, 47);
    install_idt();
    kprint(PRINTF_TEXT, "Silicon Kernel loaded.\n");
    char *i[6];
    kprint(PRINTF_TEXT, _to_decimal(sizeof(idt), i));
    for (;;)
        asm("hlt");
}