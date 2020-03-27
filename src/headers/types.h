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

s8 *_to_decimal(u32 x, s8 *s)
{
    *--s = 0; // Set end to 0
    if (!x) // If equal to 0
        *--s = '0'; // Set end to '0'
    for (; x; x /= 10) // Else, iterate until 0
        *--s = '0' + x % 10; // Convert x->s[n] (s[n] = x mod base + 48('0' ASCII))
    return s;
}

u8 _strlen(s8 *string)
{
    u8 i = 0;
    while (string[i] != 0)
        i++;
    return i;
}

#endif