#ifndef KTYPES_H
#define KTYPES_H

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

#define WAIT(n)                 \
    for (u32 i = 0; i < n; i++) \
        ;

void noop()
{
}

#endif