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

#define WAIT(n)                 \
    for (u32 i = 0; i < n; i++) \
        ;

void noop()
{
}

// djb2, not cryptographically reliable but suits our use for now
u64 hash(char *str)
{
    u64 hash = 5381;
    s32 c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return hash;
}

#endif