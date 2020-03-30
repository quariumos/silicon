#ifndef SERIAL_H
#define SERIAL_H

#include <types.h>
#include <cpu/port.h>
#include <io/device.h>

#define COM1 0x3f8

typedef enum
{
    RECIEVED = 1,
    EMPTY = 32
} SERIAL_STATE;

#define SERIAL_INIT(port)                                             \
    {                                                                 \
        outb(port + 1, 0);    /* Disable interrupts */                \
        outb(port + 3, 0x80); /* Baud Rate Divisor Setting enabled */ \
        outb(port + 0, 3);    /* Divisor / Low Byte */                \
        outb(port + 1, 0);    /* High Byte */                         \
        outb(port + 3, 3);    /* Set control options */               \
        outb(port + 2, 0xC7); /* Enable FIFO(FirstInFirstOut) */      \
        outb(port + 4, 0x0B); /* Enable interrupts */                 \
    }

#define SERIAL_CHECK(port, state) (inb(port + 5) & state)

STREAM(serial_stream, ARRAY(NOSUB, NOSUB, NOSUB))

void serial_in(u32 port)
{
    while (SERIAL_CHECK(port, RECIEVED) == 0)
        ;
    serial_stream.write(inb(port));
}

void serial_write(u32 port, s8 value)
{
    while (SERIAL_CHECK(port, EMPTY) == 0)
        ;
    outb(port, value);
}

generic_io_device serial =
    {
        .in_device = {
            .flags = 0,
            .stream = serial_stream},
        .out_device = {
            .flags = 0,
            .f = serial_out
        }};

#endif