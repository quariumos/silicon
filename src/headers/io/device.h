#ifndef OUT_H
#define OUT_H

#include <types.h>
#include <io/stream.h>

typedef struct
{
    u16 flags;
    void(*f)(u8 c);
} out_io_device_t;

typedef struct
{
    u16 flags;
    stream_t stream;
} in_io_device_t;

typedef struct
{
    in_io_device_t in_device;
    out_io_device_t out_device;
    char id[6]; // short device identifier used by the kernel, max 5 chars
} generic_io_device;

#endif