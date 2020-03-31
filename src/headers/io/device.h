#ifndef OUT_H
#define OUT_H

#include <types.h>
#include <io/stream.h>

typedef struct
{
    u16 flags;
    void (*write)(u8 c);
} out_io_device_t;

typedef struct
{
    u16 flags;
    stream_t *stream;
} in_io_device_t;

typedef struct
{
    void (*init)();
    in_io_device_t in_device;
    out_io_device_t out_device;
    char id[4]; // short device identifier used by the kernel, max 3 chars
} generic_io_device;

#endif