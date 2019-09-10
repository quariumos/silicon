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

#endif