#ifndef MATH_H
#define MATH_H
// Not complete at all

int floor(u32 n)
{
    return n - (n % 1);
}

int ceil(u32 n)
{
    return -floor(-n);
}

#endif