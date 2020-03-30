
#include <types.h>
#include <memory.h>
#include <cpu/port.h>
#include <cpu/irq/idt.h>
#include <cpu/irq/isr.h>

#define SILICON_IO

#ifdef SILICON_IO
#define IO_PRINT_SERIAL
#define IO_PRINT_TEXT
#include <r/kprint.h>
#endif

__attribute__((interrupt)) void double_fault_handler(struct interrupt_frame *frame)
{
    kprint(PRINTF_TEXT, "!!! Double fault !!!\n");
}

__attribute__((interrupt)) void stub_isr_handler(struct interrupt_frame *frame)
{
    u8 scancode = inb(0x60);
    kprint(PRINTF_TEXT, "Interrupt occured\n");
    eoi(1);
}

void kmain()
{
    remap_pic(32, 47);
    install_idt();
    set_idt_entry(1, double_fault_handler);
    set_idt_entry(33, stub_isr_handler);
    set_idt_entry(40, stub_isr_handler);
    kprint(PRINTF_TEXT, "Silicon Kernel loaded.\n");
    pic_unmask(1);
    asm("sti");
    for (;;)
        asm("hlt");
}