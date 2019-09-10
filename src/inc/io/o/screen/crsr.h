
#ifndef TEXT_H
#define TEXT_H

#include <def/def.h>

u16 crsr_y = 0, crsr_x = 0;

void vid_text_scroll(u16 *vid_text_mem, u16 replace_color)
{
    u16 blank = 0x20 | (0x0F << 8);
    // Move the current text chunk back by a line 
    u8 temp = crsr_y - VGA_HEIGHT + 1;
    memcpy((u8*)vid_text_mem, (u8*)(vid_text_mem + temp * VGA_WIDTH), (VGA_HEIGHT - temp) * VGA_WIDTH * 2);

    // Set last line to 'blank' character 
    memsetw(vid_text_mem + (VGA_HEIGHT - temp) * VGA_WIDTH, blank, VGA_WIDTH);
    crsr_y = 25 - 1;
}

u16 vid_cursor_set(s8 start, s8 end)
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
    crsr_x = x, crsr_y = y;
    u16 a = y * 80 + x;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (a & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, ((a >> 8) & 0x0FF));
}

#endif
