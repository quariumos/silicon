#ifndef IO_BASE_TYPES_H
#define IO_BASE_TYPES_H

#include <types.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct
{
    void (*init)();
    u16 flags;
    void *handler;
    char id[4]; // short device identifier used by the kernel, max 3 chars
} generic_io_device;

#endif