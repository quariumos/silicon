#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <def/def.h>
#include <sys/idt.h>

#include <sys/memory/mem.h>

#include <io/o/screen/print.h>

void(*input_handler)(u32 input);

// IRQ vector for keyboard
#define KEYBOARD_IRQ 33
void kb_handler(u32 vector)
{
    u8 code = inb(0x60);
    if (code & 0x80) // Check if key was released
    {
    }
    else
    {
        u8 value = 0;
        switch (code)
        {
	case 0x1E:
        value = 'A' + 32;
        break;
	case 0x30:
        value = 'B' + 32;
        break;
	case 0x2E:
        value = 'C' + 32;
        break;
	case 0x20:
        value = 'D' + 32;
        break;
	case 0x12:
        value = 'E' + 32;
        break;
	case 0x21:
        value = 'F' + 32;
        break;
	case 0x22:
        value = 'G' + 32;
        break;
	case 0x23:
        value = 'H' + 32;
        break;
	case 0x17:
        value = 'I' + 32;
        break;
	case 0x24:
        value = 'J' + 32;
        break;
	case 0x25:
        value = 'K' + 32;
        break;
	case 0x26:
        value = 'L' + 32;
        break;
	case 0x32:
        value = 'M' + 32;
        break;
	case 0x31:
        value = 'N' + 32;
        break;
	case 0x18:
        value = 'O' + 32;
        break;
	case 0x19:
        value = 'P' + 32;
        break;
	case 0x10:
        value = 'Q' + 32;
        break;
	case 0x13:
        value = 'R' + 32;
        break;
	case 0x1F:
        value = 'S' + 32;
        break;
	case 0x14:
        value = 'T' + 32;
        break;
	case 0x16:
        value = 'U' + 32;
        break;
	case 0x2F:
        value = 'V' + 32;
        break;
	case 0x11:
        value = 'W' + 32;
        break;
	case 0x2D:
        value = 'X' + 32;
        break;
	case 0x15:
        value = 'Y' + 32;
        break;
	case 0x2C:
        value = 'Z' + 32;
        break;
	case 0x0B:
        value = '0';
        break;
	case 0x02:
        value = '1';
        break;
	case 0x03:
        value = '2';
        break;
	case 0x04:
        value = '3';
        break;
	case 0x05:
        value = '4';
        break;
	case 0x06:
        value = '5';
        break;
	case 0x07:
        value = '6';
        break;
	case 0x08:
        value = '7';
        break;
	case 0x09:
        value = '8';
        break;
	case 0x0A:
        value = '9';
        break;
	case 0x29:
        value = '~';
        break;
	case 0x0C:
        value = '-';
        break;
	case 0x0D:
        value = '=';
        break;
	case 0x2B:
        value = '\\';
        break;
	case 0x1A:
        value = '[';
        break;
	case 0x1B:
        value = ']';
        break;
	case 0x27:
        value = ';';
        break;
	case 0x28:
        value = '\'';
        break;
	case 0x33:
        value = ',';
        break;
	case 0x34:
        value = '.';
        break;
	case 0x35:
        value = '/';
        break;
        default:
            break;
        }
        input_handler(value);
    }
    eoi(1);
}

// Enable keyboard handler
void keyboard(void(*input_handler_arg)(u32 input))
{
    input_handler = input_handler_arg;
    if (!has_isr(KEYBOARD_IRQ))
    {
        outb(0x21, 0xfd);
        outb(0xa1, 0xff);
        isr(KEYBOARD_IRQ, kb_handler);
    }
}
#endif