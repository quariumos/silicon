#pragma once

#include <types.h>
#include <cpu/port.h>

struct interrupt_frame {
    u16 ip;
    u16 cs;
    u16 flags;
    u16 sp;
    u16 ss;
};

struct idt_entry {
    unsigned short int offset_lowerbits;
    unsigned short int selector;
    u8 zero;
    u8 type_attr;
    unsigned short int offset_higherbits;
} __attribute__((packed));

#define IDT_SIZE 256
struct idt_entry idt[IDT_SIZE];

void set_idt_entry(u32 vector, void(*handler)()) {
    u64 handler_address = (u64) handler;
    idt[vector].offset_lowerbits = handler_address & 0xffff;
    idt[vector].selector = 0x08;
    idt[vector].zero = 0;
    idt[vector].type_attr = 0x8e;
    idt[vector].offset_higherbits = (handler_address & 0xffff0000) >> 16;
}

void remap_pic(u16 start_offset, u16 end_offset) {
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

void install_idt() {
    u64 idt_ptr[2];
    u64 idt_address = (u64)idt;
    idt_ptr[0] = (sizeof(struct idt_entry) * 256) + ((idt_address & 0xffff) << 16);
    idt_ptr[1] = idt_address >> 16;

    __asm__("lidt %0" ::"m"(*idt_ptr));
}
