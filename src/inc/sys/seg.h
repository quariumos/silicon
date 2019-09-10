#ifndef SEG_H
#define SEG_H

#include <def/def.h>

struct gdt_entry
{
	u16 limit_low;
	u16 base_low;
	u8 base_middle;
	u8 access;
	u8 granularity;
	u8 base_high;
} __attribute__((packed));

struct gdt_ptr
{
	u16 limit;
	u32 base;
} __attribute__((packed));

struct gdt_entry gdt[3];

void gdt_set_gate(int num, unsigned long base, unsigned long limit,
                           unsigned char access, unsigned char gran)
{
    // Set base address
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    // Set the descriptor limits
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    // Set the granularity and access flags
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

void install_gdt()
{
    // Set all data to be used with ldgdt
    u64 gdt_ptr[2];
    gdt_ptr[0] = (sizeof(struct gdt_entry) * 3) - 1;
    gdt_ptr[1] = (u64)&gdt;

    // NULL descriptor
    gdt_set_gate(0, 0, 0, 0, 0);

    // Code Segment, it's base is
    //0, limit is 4GB and it has 4KB granularity,
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    // Same, but for data
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    __asm__("lgdt %0"
            :
            : "m"(gdt_ptr));
}

#endif