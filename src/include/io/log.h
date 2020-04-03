#ifndef LOG_H
#define LOG_H

#include <io/kprintf.h>
#include <io/out/text.h>
#include <io/duplex/serial.h>

#define kprintf(format, ...) _raw_kprintf(text.out_device, format, __VA_ARGS__);
#define klog(format, ...)                              \
    _raw_kprintf(serial.out_device, "Log->>> ", NULL); \
    _raw_kprintf(serial.out_device, format, __VA_ARGS__);

#endif