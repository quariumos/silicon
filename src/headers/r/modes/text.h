#ifndef TTY_TEXT_H
#define TTY_TEXT_H

#include <types.h>
#include <memory.h>
#include <cpu/port.h>

// Video memory pointer, obviously
#define VIDEO_MEMORY 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VIDEO_MEMORY_SIZE 4000
// Defintions for all the colors
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define PURPLE 5
#define BROWN 6
#define GREY 7
#define DARK_GREY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_CYAN 11
#define LIGhT_RED 12
#define LIGHT_PURPLE 13
#define YELLOW 14
#define WHITE 15

typedef enum
{
    COLOR = 8,
    CHARACTER = 0
} which_type;

#define NILINIL (u16 *)VIDEO_MEMORY
#define text_color(f,b) (b << 4) | (f & 0x0F)
u16 crsr_y = 0, crsr_x = 0;

void text_character_set(s8 character, u16 color, u16 *where)
{
    *where = character | (color << 8);
}

u16 text_which(which_type type, u16 *where)
{
    return (*where | type) >> type;
}

void text_scroll(u16 *vid_text_mem, u16 replace_color)
{
    // Move the current text chunk back by a line 
    u8 temp = crsr_y - VGA_HEIGHT + 1;
    memcpy((u8*)vid_text_mem, (u8*)(vid_text_mem + temp * VGA_WIDTH), (VGA_HEIGHT - temp) * VGA_WIDTH * 2);

    // Set last line to 'blank' character 
    memsetw(vid_text_mem + (VGA_HEIGHT - temp) * VGA_WIDTH, replace_color, VGA_WIDTH);
    crsr_y = 25 - 1;
}

u16 text_cursor_set(s8 start, s8 end)
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

void text_cursor_move(u16 x, u16 y)
{
    crsr_x = x, crsr_y = y;
    u16 a = y * 80 + x;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (a & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, ((a >> 8) & 0x0FF));
}

void text_clear(u16* text_mem, u16 color)
{
    u8 text_ptr_x = 0, text_ptr_y = 0;
    for (u32 i = 0; i < VIDEO_MEMORY_SIZE; i++)
    {
        text_character_set(' ', color, (text_mem + i));
    }
}

#endif