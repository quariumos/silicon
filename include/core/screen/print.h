#ifndef PRINT_H
#define PRINT_H

#include <core/def.h>
#include <core/std.h>
#include <core/screen/text.h>

u16 vid_ptr_x = 0;
u16 vid_ptr_y = 0;

void kprintc(u8 c, u16 color)
{
    character(c, color, address(vid_ptr_x, vid_ptr_y));
    if (vid_ptr_x < VGA_WIDTH)
        vid_ptr_x += 1;
    else
    {
        vid_ptr_y += 1;
        vid_ptr_x = 0;
    }
}

void nline()
{
    vid_ptr_y += 1;
    vid_ptr_x = 0;
}

void kprint(char *s, u16 color)
{
    u32 l = strlen(s), j = 0;
    volatile u16 *a = address(vid_ptr_x, vid_ptr_y);
    while (j < l)
    {
        character(s[j], color, a);
        j++;
        if (j % VGA_WIDTH == 0)
            vid_ptr_y += 1, vid_ptr_x = 0;
        else
            vid_ptr_x += 1;
        a += 1;
    }
}

#endif