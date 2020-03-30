#ifndef ISR_H
#define ISR_H
#include <types.h>
#include <cpu/port.h>

void eoi(u16 n)
{
    if(n>=8)
        outb(0xA0, 0x20);
    outb(0x20, 0x20); //EOI
}
#endif