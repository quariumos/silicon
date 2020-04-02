#ifndef MEMORY_H
#define MEMORY_H
#include <types.h>

void *memmove(u8 *dst, u8 *src, u32 size)
{
    if (dst < src)
        for (u32 i = 0; i < size; i++)
            dst[i] = src[i];
    else
        for (u32 i = size; i != 0; i--)
            dst[i - 1] = src[i - 1];
    return dst;
}
u32 memcmp(u8 *a, u8 *b, u32 size)
{
    for (u32 i = 0; i < size; i++)
        if (a[i] < b[i])
            return -1;
        else if (b[i] < a[i])
            return 1;
    return 0;
}
void *memset(u8 *buf, u32 value, u32 size)
{
    for (u32 i = 0; i < size; i++)
        buf[i] = (unsigned char)value;
    return buf;
}
void *memsetw(u16 *buf, u32 value, u32 size)
{
    for (u32 i = 0; i < size; i++)
        buf[i] = (unsigned short)value;
    return buf;
}
void *memcpy(u8 *dst, u8 *src, u32 size)
{
    for (u32 i = 0; i < size; i++)
        dst[i] = src[i];
    return dst;
}
#endif