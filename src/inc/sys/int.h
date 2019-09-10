#ifndef IDT_H
#define IDT_H

#include <def/def.h>
#include <def/serial.h>

struct IDT_entry
{
    unsigned short int offset_lowerbits;
    unsigned short int selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short int offset_higherbits;
};

#define IDT_SIZE 256
struct IDT_entry IDT[IDT_SIZE];

void (*isr_handlers[IDT_SIZE])(u32 vector) = {};

u32 isr_manager(u32 vector)
{
#ifdef DEBUG
    char s[2];
    // Send debug info through host terminal/serial console
    serial_write_string(COM1, "Interrupt occurred. IRQ");
    serial_write_string(COM1, _dec(vector, s));
    serial_write(COM1, 10);
#endif
    void (*h)(u32 vector) = isr_handlers[vector];
    if (h != NULL)
        h(vector);
    else
    {
#ifdef DEBUG
        serial_write_string(COM1, "No Handler IRQ/EXC");
        serial_write_string(COM1, _dec(vector));
#endif
    }
    outb(0x20, 0x20);
    if (vector > 7)
        outb(0xA0, 0x20);
    return 0;
}

struct interrupt_frame
{
    u64 ip;
    u64 cs;
    u64 flags;
    u64 sp;
    u64 ss;
};

void install_isr(u32 vector, void (*handler)(u32 vector))
{
    isr_handlers[vector] = handler;
}

s8 has_isr(u32 vector)
{
    void (*h)(u32 vector) = isr_handlers[vector];
    return h != NULL;
}

#define EXC(vector)                                                            \
    __attribute__((interrupt)) void exc##vector(struct interrupt_frame *frame) \
    {                                                                          \
        isr_manager(vector);                                                   \
    };

#define IRQ(vector)                                                            \
    __attribute__((interrupt)) void irq##vector(struct interrupt_frame *frame) \
    {                                                                          \
        isr_manager(vector);                                                   \
    };

#define DEF_IRQ(vector)                                      \
    u64 _address_irq##vector = (u64)irq##vector;             \
    IDT[0].offset_lowerbits = _address_irq##vector & 0xffff; \
    IDT[0].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */ \
    IDT[0]                                                   \
        .zero = 0;                                           \
    IDT[0]                                                   \
        .type_attr = 0x8e; /* INTERRUPT_GATE */              \
    IDT[0]                                                   \
        .offset_higherbits = (_address_irq##vector & 0xffff0000) >> 16;

#define DEF_EXC(vector)                                      \
    u64 _address_exc##vector = (u64)exc##vector;             \
    IDT[0].offset_lowerbits = _address_exc##vector & 0xffff; \
    IDT[0].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */ \
    IDT[0]                                                   \
        .zero = 0;                                           \
    IDT[0]                                                   \
        .type_attr = 0x8e; /* INTERRUPT_GATE */              \
    IDT[0]                                                   \
        .offset_higherbits = (_address_exc##vector & 0xffff0000) >> 16;

EXC(0)
EXC(1)
EXC(2)
EXC(3)
EXC(4)
EXC(5)
EXC(6)
EXC(7)
EXC(8)
EXC(10)
EXC(11)
EXC(12)
EXC(13)
EXC(14)

IRQ(32)
IRQ(33)
IRQ(34)
IRQ(35)
IRQ(36)
IRQ(37)
IRQ(38)
IRQ(39)
IRQ(40)
IRQ(41)
IRQ(42)
IRQ(43)
IRQ(44)
IRQ(45)
IRQ(46)
IRQ(47)

void install_idt()
{

    u64 idt_address;
    u64 idt_ptr[2];

    /* remapping the PIC */
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 40);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x20, 0x00);
    outb(0xA0, 0x00);

    // Exceptions here
    DEF_EXC(0)
    DEF_EXC(1)
    DEF_EXC(2)
    DEF_EXC(3)
    DEF_EXC(4)
    DEF_EXC(5)
    DEF_EXC(6)
    DEF_EXC(7)
    DEF_EXC(8)
    DEF_EXC(10)
    DEF_EXC(11)
    DEF_EXC(12)
    DEF_EXC(13)
    DEF_EXC(14)

    // Hardware Interrupts here
    DEF_IRQ(32)

    DEF_IRQ(33)

    DEF_IRQ(34)

    DEF_IRQ(35)

    DEF_IRQ(36)

    DEF_IRQ(37)

    DEF_IRQ(38)

    DEF_IRQ(39)

    DEF_IRQ(40)

    DEF_IRQ(41)

    DEF_IRQ(42)

    DEF_IRQ(43)

    DEF_IRQ(44)

    DEF_IRQ(45)

    DEF_IRQ(46)

    DEF_IRQ(47)
    /* fill the IDT descriptor */
    idt_address = (u64)IDT;
    idt_ptr[0] = (sizeof(struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
    idt_ptr[1] = idt_address >> 16;

    __asm__("lidt %0"
            :
            : "m"(idt_ptr));
}

#endif