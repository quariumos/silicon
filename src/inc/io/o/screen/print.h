#ifndef PRINT_H
#define PRINT_H

#include <def/def.h>

#include "./vid.h"
#include "./crsr.h"

u16 vid_ptr_x = 0, vid_ptr_y = 0;
void nline()
{
    vid_ptr_y += 1;
    vid_ptr_x = 0;
}

void kprintc(u8 c, u16 color)
{
    if (vid_ptr_y > VGA_HEIGHT)
        vid_ptr_y = 0, vid_ptr_x = 0;
    volatile u16 *a = vid_address_get(vid_ptr_x, vid_ptr_y);
    vid_character_set(c, color, a);
    vid_cursor_move(vid_ptr_x, vid_ptr_y);
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
    s8 i = 0;
    while (s[i] != 0)
    {
        kprintc(s[i], color);
        i++;
    }
}

#endif
