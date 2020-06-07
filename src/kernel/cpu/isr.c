#include <types.h>
#include <cpu/port.h>
#include <cpu/isr.h>

void eoi(u16 n)
{
    if (n > 7)
        outb(PIC2, 0x20);
    outb(PIC1, 0x20); //EOI
}

void pic_mask(unsigned char n)
{
    u16 port;
    u8 value;

    if (n < 8)
        port = PIC1_DATA;
    else
    {
        port = PIC2_DATA;
        n -= 8;
    }
    value = inb(port) | (1 << n);
    outb(port, value);
}

void pic_unmask(unsigned char n)
{
    u16 port;
    u8 value;

    if (n < 8)
        port = PIC1_DATA;
    else
    {
        port = PIC2_DATA;
        n -= 8;
    }
    value = inb(port) | ~(1 << n);
    outb(port, value);
}

void remap_pic(u16 start_offset, u16 end_offset)
{
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, start_offset);
    outb(0xA1, end_offset);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}


struct idt_entry idt[IDT_SIZE];


void set_idt_entry(int vector, isr_handler_t handler)
{
    u64 handler_address = (u64)handler;
    idt[vector].offset_lowerbits = handler_address & 0xffff;
    idt[vector].selector = 0x08;
    idt[vector].zero = 0;
    idt[vector].type_attr = 0x8e;
    idt[vector].offset_higherbits = (handler_address & 0xffff0000) >> 16;
}

void stub_isr_handler(struct interrupt_frame*frame)
{
    return;
}

// This has to be called *before* setting entries!
void clear_idt()
{
    for (u32 i = 0; i < 256; i++)
        set_idt_entry(i, stub_isr_handler);
}

void install_idt()
{
    u64 idt_ptr[2];
    u64 idt_address = (u64)idt;
    idt_ptr[0] = (sizeof(struct idt_entry) * 256) + ((idt_address & 0xffff) << 16);
    idt_ptr[1] = idt_address >> 16;

    __asm__("lidt %0" ::"m"(*idt_ptr));
}