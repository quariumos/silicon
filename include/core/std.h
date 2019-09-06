#ifndef STD_H
#define STD_H

#include <core/def.h>

u8 strlen(s8 *string)
{
    u8 i = 0;
    while (string[i] != 0)
        i++;
    return i;
}

s32 atoi(char *str)
{
    s32 neg;
    s32 num;
    s32 i;

    i = 0;
    neg = 1;
    num = 0;
    while (str[i] <= ' ')
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            neg *= -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        num = num * 10 + (str[i] - 48);
        i++;
    }
    return (num * neg);
}

s8 *_dec(u32 x, s8 *s)
{
    *--s = 0; // Set end to 0
    if (!x) // If equal to 0
        *--s = '0'; // Set end to '0'
    for (; x; x /= 10) // Else, iterate until 0
        *--s = '0' + x % 10; // Convert x->s[n] (s[n] = x mod base + 48('0' ASCII))
    return s;
}

#endif