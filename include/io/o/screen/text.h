#ifdef DEBUG
#ifndef TEXT_H
#define TEXT_H

#include <core/def.h>

// video memory pointer, obviously
#define VIDEO_MEMORY 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VIDEO_MEMORY_SIZE 4000
// defintions for all the colors
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

// possible display states
typedef enum
{
    DISPLAY_TYPE_NONE = 0x00,
    DISPLAY_TYPE_COLOUR = 0x20,
    DISPLAY_TYPE_MONOCHROME = 0x30,
} display_type;

typedef enum
{
    COLOR = 8,
    CHARACTER = 0
} which_type;

display_type display()
{
    const u16 *ptr = (const u16 *)0x410;
    return (display_type)(*ptr & 0x30);
}

u16 cursor(s8 start, s8 end)
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

void cursor_move(u16 address)
{
    u16 pos = address;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, ((pos >> 8) & 0x0FF));
}

#define NILINIL (volatile u16 *)VIDEO_MEMORY

u32 vid_mem = VIDEO_MEMORY;

volatile u16 *address(u8 x, u8 y)
{
    volatile u16 *where = (volatile u16 *)vid_mem + (y * VGA_WIDTH + x);
    return where;
}

void screen(u32 address)
{
    vid_mem = address;
}

void character(s8 character, u16 color, volatile u16 *where)
{
    *where = character | (color << 8);
}

u16 color(u32 fore, u32 back)
{
    u16 attr = (back << 4) | (fore & 0x0F);
    return attr;
}

u16 which(which_type type, volatile u16 *where)
{
    return (*where | type) >> type;
}

#endif
#endif