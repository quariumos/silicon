#ifdef DEBUG
#ifndef PRINT_H
#define PRINT_H

#include <core/def.h>
#include <core/std.h>

#include "./text.h"

u16 vid_ptr_x = 0;
u16 vid_ptr_y = 0;
void nline()
{
    vid_ptr_y += 1;
    vid_ptr_x = 0;
}

void resetscreen(u16 x, u16 y)
{
    vid_ptr_x = x;
    vid_ptr_y = y;
}

void kprintc(u8 c, u16 color)
{
    if (vid_ptr_y > VGA_HEIGHT)
        vid_ptr_y = 0, vid_ptr_x = 0;
    character(c, color, address(vid_ptr_x, vid_ptr_y));
    if (vid_ptr_x < VGA_WIDTH)
        vid_ptr_x += 1;
    else
    {
        vid_ptr_y += 1;
        vid_ptr_x = 0;
    }
}

void kprint(char *s, u16 color)
{
    u32 l = strlen(s);
    for (u32 i = 0; i < l; i++)
    {
        kprintc(s[i], color);
    }
}

#endif
#endif