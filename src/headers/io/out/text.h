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
u16 text_y = 0, text_x = 0;

void text_setc(u8 character, u16 color, u16 *where)
{
    *where = character | (color << 8);
}

void text_outc(u8 c)
{
    text_setc(c, DEFAULT_TEXT_COLOR, NILINIL);
}

void init_text()
{
    u16 *ptr = NILINIL - 1;
    for (u32 i = 0; i < TEXT_FIELD_HEIGHT * TEXT_FIELD_WIDTH; i++)
    {
        ptr++;
        text_setc(' ', DEFAULT_TEXT_COLOR, ptr);
    }
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