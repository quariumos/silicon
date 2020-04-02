#pragma once

#include <types.h>
#include <cpu/port.h>
extern void global_irq_manager(int n);
extern void load_idt();
typedef struct
{
    unsigned short int offset_lowerbits;
    unsigned short int selector;
    u8 zero;
    u8 type_attr;
    unsigned short int offset_higherbits;
} __attribute__((packed)) idt_entry_t;
#define IDT_SIZE 256
extern idt_entry_t idt[IDT_SIZE];
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