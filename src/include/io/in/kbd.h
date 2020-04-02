#ifndef DEVICE_KBD_H
#define DEVICE_KBD_H
#include <cpu/port.h>
#include <cpu/isr.h>
#include <io/device.h>

#ifdef SILICON_SERIAL_LOG
#include <io/kprintf.h>
#include <io/duplex/serial.h>
#include <io/out/text.h>
#endif

// Sample keymap (US layout), taken from a tutorial by Bran
u8 kbdus[128] =
    {
        0, 27, '1', '2', '3', '4', '5', '6', '7', '8',    /* 9 */
        '9', '0', '-', '=', '\b',                         /* Backspace */
        '\t',                                             /* Tab */
        'q', 'w', 'e', 'r',                               /* 19 */
        't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',     /* Enter key */
        0,                                                /* 29   - Control */
        'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */
        '\'', '`', 0,                                     /* Left shift */
        '\\', 'z', 'x', 'c', 'v', 'b', 'n',               /* 49 */
        'm', ',', '.', '/', 0,                            /* Right shift */
        '*',
        0,   /* Alt */
        ' ', /* Space bar */
        0,   /* Caps lock */
        0,   /* 59 - F1 key ... > */
        0, 0, 0, 0, 0, 0, 0, 0,
        0, /* < ... F10 */
        0, /* 69 - Num lock*/
        0, /* Scroll Lock */
        0, /* Home key */
        0, /* Up Arrow */
        0, /* Page Up */
        '-',
        0, /* Left Arrow */
        0,
        0, /* Right Arrow */
        '+',
        0, /* 79 - End key*/
        0, /* Down Arrow */
        0, /* Page Down */
        0, /* Insert Key */
        0, /* Delete Key */
        0, 0, 0,
        0, /* F11 Key */
        0, /* F12 Key */
        0, /* All other keys are undefined */
};
STREAM(keyboard_stream)
void keyboard_interrupt_handler()
{
    u8 scancode = inb(0x60);
    u8 c = kbdus[scancode];
    kprintf(text.out_device, "%c", c);
}
void init_kbd(char *id)
{
#ifdef SILICON_SERIAL_LOG
    kprintf(serial.out_device, "'%s' initialized\n", id);
#endif
    init_keyboard_stream(NULL);
    IRQ(1, keyboard_interrupt_handler);
    asm("sti");
}
generic_io_device kbd =
    {
        .init = init_kbd,
        .in_device = {
            .flags = 0,
            .stream = &keyboard_stream},
        .out_device = {.flags = 1, .write = NULL},
        .id = "KBD"};

#endif