#ifndef DEVICE_SERIAL_H
#define DEVICE_SERIAL_H

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

STREAM(serial_stream)

#define DEFAULT_COM_PORT COM1

void serial_in()
{
    while (SERIAL_CHECK(DEFAULT_COM_PORT, RECIEVED) == 0)
        ;
    serial_stream.write(inb(DEFAULT_COM_PORT));
}

void serial_outc(u8 c)
{
    while (SERIAL_CHECK(DEFAULT_COM_PORT, EMPTY) == 0)
        ;
    outb(DEFAULT_COM_PORT, c);
}

void init_serial(char *id)
{
    SERIAL_INIT(DEFAULT_COM_PORT);
    init_serial_stream(NULL);
}

generic_io_device serial =
    {
        .init = init_serial,
        .in_device = {
            .flags = 0,
            .stream = &serial_stream},
        .out_device = {.flags = 0, .write = serial_outc},
        .id = "SRL"};

#endif