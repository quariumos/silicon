#ifndef EXC_H
#define EXC_H

#include <core/def.h>

#ifdef DEBUG
#include <core/serial.h>
// When in DEBUG mode it uses serial port
void generic_exception_handler(u32 vector)
{
    char s[2];
    serial_write_string(COM1, "Interrupt occurred. EXC");
    serial_write_string(COM1, _dec(vector, s));
    serial_write(COM1, 10);
}
#else
// Otherwise it does nothing
void generic_exception_handler(u32 vector)
{
}
#endif

#endif