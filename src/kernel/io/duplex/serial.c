
#include <types.h>
#include <cpu/port.h>
#include <io/base/types.h>

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

extern void serial_outc(u8 c);

generic_io_device serial_out = {.init = NULL,
                                .flags = 0,
                                .handler = (void *)serial_outc,
                                .id = "SRL"};

void serial_outc(u8 c)
{
    while (SERIAL_CHECK(serial_out.flags, EMPTY) == 0)
        ;
    outb(serial_out.flags, c);
}

extern u8 serial_inc();

generic_io_device serial_in = {.init = NULL,
                               .flags = 0,
                               .handler = (void *)serial_inc,
                               .id = "SRL"};

u8 serial_inc()
{
    while (SERIAL_CHECK(serial_in.flags, RECIEVED) == 0)
        ;
    return inb(serial_in.flags);
}

#define SERIAL_SET(in, out, port) \
    out.flags = port;             \
    in.flags = port;