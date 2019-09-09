
#ifndef TEXT_H
#define TEXT_H

#include <def/def.h>

u16 crsr_y = 0, crsr_x = 0;

u16 vid_cursor_set_size(s8 start, s8 end)
{
    u16 pos = 0;
    outb(0x3D4, 0x0A);
    switch (start)
    {
    case -1:
        outb(0x3D4, 0x0F);
        pos |= inb(0x3D5);
        outb(0x3D4, 0x0E);
        pos |= ((unsigned short)inb(0x3D5)) << 8;
        break;
    case -2:
        outb(0x3D5, 0x20);
        break;
    default:
        outb(0x3D5, (inb(0x3D5) & 0xC0) | start);
        outb(0x3D4, 0x0B);
        outb(0x3D5, (inb(0x3D5) & 0xE0) | end);
        break;
    }
    return pos;
}

void vid_cursor_move(u16 x, u16 y)
{
    u16 a = y * 80 + x;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (a & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, ((a >> 8) & 0x0FF));
}


#endif
