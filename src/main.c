
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

#define EX_IRQ(n) extern void handler_##n();

EX_IRQ(1)

void main_irq_handler(int n)
{
    switch (n)
    {
    case 1:
        kprint(PRINTF_SERIAL, "Keyboard interrupt");
        break;

    default:
        break;
    }
    eoi(n);
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
    remap_pic(32, 47);
    install_idt();
    set_idt_entry(1, handler_1);
    kprint(PRINTF_TEXT, "Silicon Kernel loaded.\n");
    outb(0x21, 0xfd);
    outb(0xa1, 0xff);
    asm("sti");
    for (;;)
        asm("hlt");
}