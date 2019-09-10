#ifndef MATH_H
#define MATH_H
// Not complete at all

#include <def/def.h>

u32 floor(u32 n)
{
    return n - (n % 1);
}

u32 ceil(u32 n)
{
    return -floor(-n);
}

u32 fmul(u32 a, u32 b)
{
    u32 r = 0, l = 0;
    while (b > 0)
    {
        l = b & 1;
        if (l > 0)
            r = r + a;
        a = a << 1, b = b >> 1;
    }
    return r;
}

#endif