#ifdef DEBUG
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <core/def.h>
#include <core/sys/idt.h>
#include "../o/screen/print.h"	

// IRQ vector for keyboard
#define KEYBOARD_IRQ 33
void kb_handler(u32 vector)
{
    u8 code = inb(0x60);
    eoi(1);
}
// Enable keyboard handler
void keyboard()
{
    if (!has_isr(KEYBOARD_IRQ))
    {
        outb(0x21, 0xfd);
        outb(0xa1, 0xff);
        isr(KEYBOARD_IRQ, kb_handler);
    }
}
#endif
#endif