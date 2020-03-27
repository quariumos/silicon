#ifndef VID_H
#define VID_H

#include <types.h>

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

void vid_character_set(s8 character, u16 color, u16 *where)
{
    *where = character | (color << 8);
}

u16 vid_color(u32 fore, u32 back)
{
    u16 attr = (back << 4) | (fore & 0x0F);
    return attr;
}

u16 vid_which(which_type type, u16 *where)
{
    return (*where | type) >> type;
}

#endif