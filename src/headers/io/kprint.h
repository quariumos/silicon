#ifndef PRINT_H
#define PRINT_H

#include <types.h>
#ifdef IO_PRINT_TEXT
#include <io/modes/text.h>
#endif
#ifdef IO_PRINT_SERIAL
#include <io/modes/serial.h>
#endif 

u16 text_ptr_x = 0, text_ptr_y = 0;

enum {
    #ifdef IO_PRINT_SERIAL
    PRINTF_SERIAL = 0,
    #endif
    #ifdef IO_PRINT_TEXT
    PRINTF_TEXT = 1
    #endif
};

u16 default_text_color = text_color(BLACK, WHITE);

void kprintc(u8 c, u32 as)
{
    switch (c)
    {
    // Backspace
    case 8:
        if (text_ptr_x != 0)
            text_ptr_x -= 1;
        break;
    // Tab
    case 9:
        text_ptr_x = (text_ptr_x + 8) & ~(8 - 1);
        break;
    // Carriage Return
    case '\r':
        text_ptr_x = 0;
        break;
    // Newline
    case '\n':
    #ifdef IO_PRINT_SERIAL
        serial_write(COM1, '\n');
    #endif
        text_ptr_x = 0;
        text_ptr_y++;
        break;

    // If printable, but not special
    default:
        if (c >= 32)
        {
            switch (as)
            {
                #ifdef IO_PRINT_SERIAL
            case PRINTF_SERIAL:
                serial_write(COM1, c);
                break;
                #endif
                                #ifdef IO_PRINT_TEXT
            case PRINTF_TEXT:
                        text_character_set(c, default_text_color, NILINIL + (text_ptr_y * 80 + text_ptr_x));
                break;
                                #endif
            default:
                break;
            }
            text_ptr_x++;
        }
        break;
    }
    switch (as)
    {
                #ifdef IO_PRINT_TEXT
    case PRINTF_TEXT:
        if (text_ptr_y > VGA_HEIGHT)
            text_scroll(NILINIL, WHITE);
        if (text_ptr_x > VGA_WIDTH)
            text_ptr_x = 0, text_ptr_y++;
        text_cursor_move(text_ptr_x, text_ptr_y);
        #endif
        break;
                        #ifdef IO_PRINT_SERIAL
    case PRINTF_SERIAL:
    #endif
        break;
    default:
        break;
    }
}

#include <stdarg.h>

#ifdef IO_PRINT_SERIAL
u8 is_serial_initialized = 0;
#endif

#ifdef IO_PRINT_TEXT
u8 is_text_initialized = 0;
#endif

void kprint(u32 as, char *s)
{
    #ifdef IO_PRINT_SERIAL
    if(is_serial_initialized == 0)
            serial_init(COM1), is_serial_initialized = 1;
    #endif
    #ifdef IO_PRINT_TEXT
if(is_text_initialized == 0)
    {
    text_cursor_set(15, 15);
    text_clear(NILINIL, default_text_color);
        is_text_initialized = 1;
    }
#endif

    s8 i = 0;
    while (s[i] != 0)
    {
        kprintc(s[i], as);
        i++;
    }
}

#endif
