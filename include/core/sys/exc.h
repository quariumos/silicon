#ifndef EXC_H
#define EXC_H

#include <core/def.h>

void generic_exception_handler(u32 vector)
{
    #ifdef DEBUG
    u16 whitefore = color(WHITE, BLACK);
    char s[2];
    kprint("Exception occured: ", whitefore);
    kprint(_dec(vector, s), whitefore);
    #endif
    // If DEBUG is not defined, it just does nothing
    return;
}

#endif