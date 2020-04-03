#ifndef DEVICE_TEXT_H
#define DEVICE_TEXT_H

#include <types.h>
#include <memory.h>
#include <cpu/port.h>
#include <io/device.h>

// Video memory pointer, obviously
#define VIDEO_MEMORY 0xB8000
#define TEXT_FIELD_WIDTH 80
#define TEXT_FIELD_HEIGHT 25
#define VIDEO_MEMORY_SIZE 4000
// Defintions for all the colors availible in text mode
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
#define LIGHT_RED 12
#define LIGHT_PURPLE 13
#define YELLOW 14
#define WHITE 15

#define NILINIL (u16 *)VIDEO_MEMORY
#define TEXT_COLOR(f, b) (b << 4) | (f & 0x0F)
#define DEFAULT_TEXT_COLOR TEXT_COLOR(BLACK, WHITE)
u16 text_y = 0, text_x = -1;

void text_setc(u8 c, u16 color, u32 x, u32 y)
{
    volatile u16 *where = (volatile u16 *)0xB8000 + (y * 80 + x);
    *where = c | (color << 8);
}

void text_outc(u8 c)
{
    text_x++;
    if (text_x > TEXT_FIELD_WIDTH)
        text_y++, text_x = 0;
    switch (c)
    {
    case '\n':
        text_y++;
        text_x = -1;
        break;

    default:
        text_setc(c, DEFAULT_TEXT_COLOR, text_x, text_y);
        break;
    }
}

void init_text(char *id)
{
    for (u32 y = 0; y < TEXT_FIELD_HEIGHT; y++)
        for (u32 x = 0; x < TEXT_FIELD_WIDTH; x++)
            text_setc(' ', DEFAULT_TEXT_COLOR, x, y);
}

generic_io_device text =
    {
        .init = init_text,
        .in_device = {
            .flags = 1,
            .stream = NULL},
        .out_device = {.flags = 0, .write = text_outc},
        .id = "TXT"};

#endif