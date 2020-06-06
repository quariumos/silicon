#ifndef CPU_PORT_H
#define CPU_PORT_H

#include <types.h>

u8 inb(u16 port)
{
    u8 result;
    __asm__("in %%dx, %%al"
    : "=a"(result)
    : "d"(port));
    return result;
}

void outb(u16 port, u8 data)
{
    __asm__("out %%al, %%dx"
    :
    : "a"(data), "d"(port));
}

#endif