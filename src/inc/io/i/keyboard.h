#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <def/def.h>

#include <sys/memory/mem.h>

#include <io/o/screen/print.h>

void (*input_handler)(u8 scancode, u8 shift, u8 caps);
u8 caps_on = 0, shfit_on = 0;

// IRQ vector for keyboard
#define KEYBOARD_IRQ 33

void kb_handler(u32 vector)
{
    u8 code = inb(0x60);
    if (code & 0x80) // Check if key was released
    {
        switch (code)
        {
        // Special keys
        // Left and Right shift released
        case 0xAA:
            shfit_on = 0;
            break;
        case 0xB6:
            shfit_on = 0;
            break;
        default:
            break;
        }
    }
    else
    {
        u8 value = 0;
        switch (code)
        {
        // Special keys
        // Caps Lock
        case 0x3A:
            caps_on = !caps_on;
            break;
        // Left and Right shift
        case 0x2A:
            shfit_on = 1;
            break;
        case 0x36:
            shfit_on = 1;
            break;
        default:
            break;
        }
        input_handler(value, shfit_on, caps_on);
    }
}
#endif