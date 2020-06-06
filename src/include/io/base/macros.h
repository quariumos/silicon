#ifndef IO_BASE_MACROS_H
#define IO_BASE_MACROS_H

#include <io/kprintf.h>
#include <io/base/types.h>

extern generic_io_device serial;

#define klog(format, ...)                                                            \
    _raw_kprintf(serial, ANSI_COLOR_BLUE "log: " ANSI_COLOR_RESET, NULL); \
    _raw_kprintf(serial, format, __VA_ARGS__);

#define INIT(io, arg) \
    io.init(arg);   \
    klog("initialized: %s\n", io.id);

#endif