#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <core/def.h>
#include <core/screen/print.h>

void kb_handler(u32 vector)
{
    u8 code = inb(0x60);
    kprintc(code, color(WHITE, BLACK));
    eoi(1);
}

#endif