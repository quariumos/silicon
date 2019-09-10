#ifndef PRINT_H
#define PRINT_H

#include <def/def.h>
#include <sys/memory/mem.h>

#include "./vid.h"
#include "./crsr.h"

u16 vid_ptr_x = 0, vid_ptr_y = 0;

void kprintc(u16 *vid_mem, u8 c, u16 color)
{
    switch (c)
    {
    // Backspace
    case 8:
        if (vid_ptr_x != 0)
            vid_ptr_x -= 1;
        break;
    // Tab
    case 9:
        vid_ptr_x = (vid_ptr_x + 8) & ~(8 - 1);
        break;
    // Carriage Return
    case '\r':
        vid_ptr_x = 0;
        break;
    // Newline
    case '\n':
        vid_ptr_x = 0;
        vid_ptr_y++;
        break;

    // If printable, but not special
    default:
        if (c >= 32)
        {
            u16 *where = vid_mem + (vid_ptr_y * 80 + vid_ptr_x);
            vid_character_set(c, color, where);
            vid_ptr_x++;
        }
        break;
    }
    if (vid_ptr_y > VGA_HEIGHT)
        vid_text_scroll(NILINIL, color);
    if (vid_ptr_x > VGA_WIDTH)
        vid_ptr_x = 0, vid_ptr_y++;
    vid_cursor_move(vid_ptr_x, vid_ptr_y);
}

void kprint(u16 *vid_mem, char *s, u16 color)
{
    s8 i = 0;
    while (s[i] != 0)
    {
        kprintc(vid_mem, s[i], color);
        i++;
    }
}

void vid_clear(u16 vid_mem, u16 color)
{
    vid_ptr_x = 0, vid_ptr_y = 0;
    for (u32 i = 0; i < VIDEO_MEMORY_SIZE; i++)
    {
        vid_character_set(' ', color, vid_mem + i);
    }
}

#endif
