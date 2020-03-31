#ifndef KPRINTF_H
#define KPRINTF_H

#include <stdarg.h>
#include <types.h>
#include <io/device.h>
#include <io/conversion.h>

void kprintf(out_io_device_t device, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    u32 ptr = -1;
    char *d;
    while (format[++ptr] != 0)
    {
        switch (format[ptr])
        {
        case '%':
            switch (format[ptr++])
            {
            case '%': // for escaping %
                device.write('%');
                break;
            case 's': // for strings
                d = va_arg(ap, char *);
                while (*d != 0)
                    device.write(*d++);
                break;
            case 'd': // for integers
                itoa(va_arg(ap, s32), 10, d);
                while (*d != 0)
                    device.write(*d++);
                break;
            case 'x': // for hexadecimals
                itoa(va_arg(ap, s32), 16, d);
                while (*d != 0)
                    device.write(*d++);
                break;
            default:
                break;
            }
            break;

        default:
            device.write(format[ptr]);
            break;
        }
    }
    va_end(ap);
}

#endif