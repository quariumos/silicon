#ifndef DEF_H
#define DEF_H

typedef unsigned long u64;
typedef long s64;
typedef unsigned int u32;
typedef int s32;
typedef unsigned short u16;
typedef short s16;
typedef unsigned char u8;
typedef char s8;

typedef u64 size_t;
typedef u64 uintptr_t;

#define NULL (void *)0

// Read a byte from the port specified
u8 inb(u16 port)
{
    u8 result;
    __asm__("in %%dx, %%al"
            : "=a"(result)
            : "d"(port));
    return result;
}

// Write a byte to the port specified
void outb(u16 port, u8 data)
{
    __asm__("out %%al, %%dx"
            :
            : "a"(data), "d"(port));
}

void eoi(s32 i)
{
    if (i <= 7)
        outb(0x20, 0x20);
    outb(0xA0, 0x20);
}

#ifdef DEBUG
#include <io/i/keyboard.h>
#include <io/o/screen/print.h>
#endif

#endif