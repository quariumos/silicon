
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
void stub_isr_handler(struct interrupt_frame *frame)
{
    eoi(1);
}


// Kernel will only provide(once it's ready to) IPC/Messaging, Memory allocation interface and a basic text mode + keyboard drivers
// All other functionality will be modular, as in modular kernels and microkernels
void kmain()
{
    remap_pic(32, 47);
    install_idt();
    set_idt_entry(1, stub_isr_handler);
    kprint(PRINTF_TEXT, "Silicon Kernel loaded.\n");
    asm("int $1");
    for (;;)
        asm("hlt");
}