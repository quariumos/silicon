#pragma once

#include <types.h>

// GDT descriptor structure
struct gdt_entry {
    u16 limit_low;
    u16 base_low;
    u8 base_middle;
    u8 access;
    u8 granularity;
    u8 base_high;
}__attribute__((packed));

// GDT
struct gdt_entry gdt[3];

void set_gdt_entry(s32 n, u64 base, u64 limit, u8 access, u8 granularity) {
    // Set descriptor's base
    gdt[n].base_low = base & 65535;
    gdt[n].base_middle = (base >> 16) & 255;
    gdt[n].base_high = (base >> 24) & 255;
    // Set descriptor's limits
    gdt[n].limit_low = limit & 65535;
    gdt[n].granularity = ((limit >> 16) & 255) | (granularity & 240);
    // Set access flag
    gdt[n].access = access;
}

void install_gdt(u32 gdt_size) {
    struct table_ptr {
        unsigned short limit;
        unsigned int base;
    }__attribute__((packed)) ptr;
    ptr.limit = (sizeof(struct gdt_entry) * gdt_size) - 1;
    ptr.base = (u32) &gdt;
    asm("lgdt %0"::"m"(*&ptr));
}