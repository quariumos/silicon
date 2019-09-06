#ifndef IDT_H
#define IDT_H

#include <core/def.h>

struct IDT_entry
{
    unsigned short int offset_lowerbits;
    unsigned short int selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short int offset_higherbits;
};

#include <core/screen/print.h>

#define IDT_SIZE 256
struct IDT_entry IDT[IDT_SIZE];

void idt_init()
{
    extern int exc0();
    extern int exc1();
    extern int exc2();
    extern int exc3();
    extern int exc4();
    extern int exc5();
    extern int exc6();
    extern int exc7();
    extern int exc8();
    extern int exc10();
    extern int exc11();
    extern int exc12();
    extern int exc13();
    extern int exc14();

    extern int irq32();
    extern int irq33();
    extern int irq34();
    extern int irq35();
    extern int irq36();
    extern int irq37();
    extern int irq38();
    extern int irq39();
    extern int irq40();
    extern int irq41();
    extern int irq42();
    extern int irq43();
    extern int irq44();
    extern int irq45();
    extern int irq46();
    extern int irq47();

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
    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    // Exceptions here
    u64 exc0_address = (u64)exc0;
    IDT[0].offset_lowerbits = exc0_address & 0xffff;
    IDT[0].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[0].zero = 0;
    IDT[0].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[0].offset_higherbits = (exc0_address & 0xffff0000) >> 16;

    u64 exc1_address = (u64)exc1;
    IDT[1].offset_lowerbits = exc1_address & 0xffff;
    IDT[1].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[1].zero = 0;
    IDT[1].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[1].offset_higherbits = (exc1_address & 0xffff0000) >> 16;

    u64 exc2_address = (u64)exc2;
    IDT[2].offset_lowerbits = exc2_address & 0xffff;
    IDT[2].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[2].zero = 0;
    IDT[2].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[2].offset_higherbits = (exc2_address & 0xffff0000) >> 16;

    u64 exc3_address = (u64)exc3;
    IDT[3].offset_lowerbits = exc3_address & 0xffff;
    IDT[3].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[3].zero = 0;
    IDT[3].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[3].offset_higherbits = (exc3_address & 0xffff0000) >> 16;

    u64 exc4_address = (u64)exc4;
    IDT[4].offset_lowerbits = exc4_address & 0xffff;
    IDT[4].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[4].zero = 0;
    IDT[4].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[4].offset_higherbits = (exc4_address & 0xffff0000) >> 16;

    u64 exc5_address = (u64)exc5;
    IDT[5].offset_lowerbits = exc5_address & 0xffff;
    IDT[5].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[5].zero = 0;
    IDT[5].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[5].offset_higherbits = (exc5_address & 0xffff0000) >> 16;

    u64 exc6_address = (u64)exc6;
    IDT[6].offset_lowerbits = exc6_address & 0xffff;
    IDT[6].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[6].zero = 0;
    IDT[6].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[6].offset_higherbits = (exc6_address & 0xffff0000) >> 16;

    u64 exc7_address = (u64)exc7;
    IDT[7].offset_lowerbits = exc7_address & 0xffff;
    IDT[7].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[7].zero = 0;
    IDT[7].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[7].offset_higherbits = (exc7_address & 0xffff0000) >> 16;

    u64 exc8_address = (u64)exc8;
    IDT[8].offset_lowerbits = exc8_address & 0xffff;
    IDT[8].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[8].zero = 0;
    IDT[8].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[8].offset_higherbits = (exc8_address & 0xffff0000) >> 16;

    u64 exc10_address = (u64)exc10;
    IDT[9].offset_lowerbits = exc10_address & 0xffff;
    IDT[9].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[9].zero = 0;
    IDT[9].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[9].offset_higherbits = (exc10_address & 0xffff0000) >> 16;

    u64 exc11_address = (u64)exc11;
    IDT[10].offset_lowerbits = exc11_address & 0xffff;
    IDT[10].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[10].zero = 0;
    IDT[10].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[10].offset_higherbits = (exc11_address & 0xffff0000) >> 16;

    u64 exc12_address = (u64)exc12;
    IDT[11].offset_lowerbits = exc12_address & 0xffff;
    IDT[11].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[11].zero = 0;
    IDT[11].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[11].offset_higherbits = (exc12_address & 0xffff0000) >> 16;

    u64 exc13_address = (u64)exc13;
    IDT[12].offset_lowerbits = exc13_address & 0xffff;
    IDT[12].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[12].zero = 0;
    IDT[12].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[12].offset_higherbits = (exc13_address & 0xffff0000) >> 16;

    u64 exc14_address = (u64)exc14;
    IDT[13].offset_lowerbits = exc14_address & 0xffff;
    IDT[13].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[13].zero = 0;
    IDT[13].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[13].offset_higherbits = (exc14_address & 0xffff0000) >> 16;

    // Exceptions 9 and 15 have no handlers,
    // 9 is deprecated and 15 is reserved

    // Hardware Interrupts here

    u64 irq0_address = (u64)irq32;
    IDT[32].offset_lowerbits = irq0_address & 0xffff;
    IDT[32].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[32].zero = 0;
    IDT[32].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[32].offset_higherbits = (irq0_address & 0xffff0000) >> 16;

    u64 irq1_address = (u64)irq33;
    IDT[33].offset_lowerbits = irq1_address & 0xffff;
    IDT[33].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[33].zero = 0;
    IDT[33].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[33].offset_higherbits = (irq1_address & 0xffff0000) >> 16;

    u64 irq2_address = (u64)irq34;
    IDT[34].offset_lowerbits = irq2_address & 0xffff;
    IDT[34].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[34].zero = 0;
    IDT[34].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[34].offset_higherbits = (irq2_address & 0xffff0000) >> 16;

    u64 irq3_address = (u64)irq35;
    IDT[35].offset_lowerbits = irq3_address & 0xffff;
    IDT[35].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[35].zero = 0;
    IDT[35].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[35].offset_higherbits = (irq3_address & 0xffff0000) >> 16;

    u64 irq4_address = (u64)irq36;
    IDT[36].offset_lowerbits = irq4_address & 0xffff;
    IDT[36].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[36].zero = 0;
    IDT[36].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[36].offset_higherbits = (irq4_address & 0xffff0000) >> 16;

    u64 irq5_address = (u64)irq37;
    IDT[37].offset_lowerbits = irq5_address & 0xffff;
    IDT[37].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[37].zero = 0;
    IDT[37].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[37].offset_higherbits = (irq5_address & 0xffff0000) >> 16;

    u64 irq6_address = (u64)irq38;
    IDT[38].offset_lowerbits = irq6_address & 0xffff;
    IDT[38].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[38].zero = 0;
    IDT[38].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[38].offset_higherbits = (irq6_address & 0xffff0000) >> 16;

    u64 irq7_address = (u64)irq39;
    IDT[39].offset_lowerbits = irq7_address & 0xffff;
    IDT[39].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[39].zero = 0;
    IDT[39].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[39].offset_higherbits = (irq7_address & 0xffff0000) >> 16;

    u64 irq8_address = (u64)irq40;
    IDT[40].offset_lowerbits = irq8_address & 0xffff;
    IDT[40].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[40].zero = 0;
    IDT[40].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[40].offset_higherbits = (irq8_address & 0xffff0000) >> 16;

    u64 irq9_address = (u64)irq41;
    IDT[41].offset_lowerbits = irq9_address & 0xffff;
    IDT[41].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[41].zero = 0;
    IDT[41].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[41].offset_higherbits = (irq9_address & 0xffff0000) >> 16;

    u64 irq10_address = (u64)irq42;
    IDT[42].offset_lowerbits = irq10_address & 0xffff;
    IDT[42].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[42].zero = 0;
    IDT[42].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[42].offset_higherbits = (irq10_address & 0xffff0000) >> 16;

    u64 irq11_address = (u64)irq43;
    IDT[43].offset_lowerbits = irq11_address & 0xffff;
    IDT[43].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[43].zero = 0;
    IDT[43].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[43].offset_higherbits = (irq11_address & 0xffff0000) >> 16;

    u64 irq12_address = (u64)irq44;
    IDT[44].offset_lowerbits = irq12_address & 0xffff;
    IDT[44].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[44].zero = 0;
    IDT[44].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[44].offset_higherbits = (irq12_address & 0xffff0000) >> 16;

    u64 irq13_address = (u64)irq45;
    IDT[45].offset_lowerbits = irq13_address & 0xffff;
    IDT[45].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[45].zero = 0;
    IDT[45].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[45].offset_higherbits = (irq13_address & 0xffff0000) >> 16;

    u64 irq14_address = (u64)irq46;
    IDT[46].offset_lowerbits = irq14_address & 0xffff;
    IDT[46].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[46].zero = 0;
    IDT[46].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[46].offset_higherbits = (irq14_address & 0xffff0000) >> 16;

    u64 irq15_address = (u64)irq47;
    IDT[47].offset_lowerbits = irq15_address & 0xffff;
    IDT[47].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[47].zero = 0;
    IDT[47].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[47].offset_higherbits = (irq15_address & 0xffff0000) >> 16;

    /* fill the IDT descriptor */
    idt_address = (u64)IDT;
    idt_ptr[0] = (sizeof(struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
    idt_ptr[1] = idt_address >> 16;

    extern void load_idt(u64 *);
    load_idt(idt_ptr);
}

void(*isr_handlers[IDT_SIZE])(u32 vector) = {};

u32 isr_manager(u32 vector)
{
    void (*h)(u32 vector) = isr_handlers[vector];
    if (h != NULL)
        h(vector);
    else
        kprint("No handler provided", color(WHITE, BLACK));
    if (vector > 14)
        eoi(vector);
    return 0;
}

void register_isr(u32 vector, void (*handler)(u32 vector))
{
    isr_handlers[vector] = handler;
}

#endif