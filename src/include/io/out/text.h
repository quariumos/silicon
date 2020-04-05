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
#define TEXT_FIELD_MEMORY_SIZE 4000
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

void text_fill(u8 c, u16 color, u32 start_x, u32 start_y, u32 stop_x, u32 stop_y)
{
    volatile u16 *start_addr = (volatile u16 *)0xB8000 + (start_y * 80 + start_x);
    volatile u16 *end_addr = (volatile u16 *)0xB8000 + (stop_y * 80 + stop_x);
    while (start_addr < end_addr)
        *(start_addr++) = c | (color << 8);
}

void move_cursor(u16 addr)
{
    outb(0x3D4, 0x0F);
    outb(0x3D5, (u8)(addr & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (u8)((addr >> 8) & 0xFF));
}

u16 text_x = 0, text_y = 0;
u16 text_color = DEFAULT_TEXT_COLOR;

void text_new_line()
{
    text_y++, text_x = 0; // move to next line and set x to first text cell on the line
                          // (------
                          // *-----)
    u16 line_start = text_y * 80 + text_x;
    move_cursor(line_start);
}

// this function accept *relative* values
void text_move(u16 x, u16 y)
{
    if (text_x == TEXT_FIELD_WIDTH)
        text_x = 0, text_y++; // move to new line, obviously
    text_x += x;
    text_y += y;
    if (text_x < 0)
        text_x = 0;
    if (text_y < 0)
        text_y = 0;
    move_cursor(text_y * 80 + text_x); // update cursor position
}

void text_setc(u8 c)
{
    u16 addr = text_y * 80 + text_x;
    volatile u16 *where = (volatile u16 *)0xB8000 + addr;
    switch (c)
    {
    case '\n':
        text_move(-text_x, 1); // move to new line
        c = ' ';
        break;
    case '\b':
        text_move(-1, 0); // move one character back
        c = ' ';
        break;
    default:
        // move one character further
        text_move(1, 0);
        break;
    }
    *where = c | (text_color << 8); // place character
}

void init_text(char *id)
{
    u8 cursor_start = 0, cursor_end = 15;
    // enable the cursor
    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
    outb(0x3D4, 0x0B);
    outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
    text_fill(' ', DEFAULT_TEXT_COLOR, 0, 0, TEXT_FIELD_WIDTH, TEXT_FIELD_HEIGHT);
}

generic_io_device text =
    {
        .init = init_text,
        .in_device = {
            .flags = 1,
            .stream = NULL},
        .out_device = {.flags = 0, .write = text_setc},
        .id = "TXT"};

#endif