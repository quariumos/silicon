#ifndef KBD_H
#define KBD_H
#include <cpu/port.h>
#include <cpu/irq/isr.h>
#include <cpu/irq/idt.h>
#include <io/device.h>
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
__attribute__((interrupt)) void keyboard_interrupt_handler(struct interrupt_frame *frame)
{
    u8 scancode = inb(0x60);
    u8 c = kbdus[scancode];
    keyboard_stream.write(c);
    eoi(1);
}
void kbd_log(u8 data)
{
    serial.out_device.write(data);
}
void init_kbd()
{
    init_keyboard_stream(kbd_log);
    set_idt_entry(33, keyboard_interrupt_handler);
    pic_unmask(1);
    asm("sti");
}
generic_io_device kbd =
    {
        .init = init_kbd,
        .in_device = {
            .flags = 0,
            .stream = &keyboard_stream},
        .out_device = {.flags = 1}};

#endif