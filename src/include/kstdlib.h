#ifndef KSTDLIB_H
#define KSTDLIB_H
#include <ktypes.h>
#include <cpu/base/ports.h>
#include <io/base/types.h>

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

char *itoa(u32 n, u32 base, char *buffer)
{
    char *rc, *ptr, *low;
    rc = ptr = buffer;
    // For negative decimal numbers
    if (n < 0 && base == 10)
        *ptr++ = '-';
    // Remember the start position
    low = ptr;
    char magiclist[] = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz";
    do
    {
        // Convert another char
        // If value is negative - modulo is negative
        *ptr++ = magiclist[35 + n % base];
        n /= base; // Remove the digit
    } while (n);   // while not null
    // Termintate by setting last char to 0
    *ptr-- = '\0';
    // Invert the string (because the conversion returns characters end-to-start)
    char tmp;
    while (low < ptr)
    {
        tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
    return rc;
}
#endif