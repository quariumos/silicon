#ifndef CONVERSION_H
#define CONVERSION_H
#include <types.h>
char *itoa(u32 n, u32 base, char *buffer)
{
    char *rc, *ptr, *low;
    rc = ptr = buffer;
    // For negative decimal numbers
    if (n < 10 && base == 10)
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