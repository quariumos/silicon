#ifndef KPRINTF_H
#define KPRINTF_H

#include <stdarg.h>
#include <types.h>
#include <io/conversion.h>
#include <io/base/types.h>

void _raw_kprintf(generic_io_device device, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    u32 ptr = -1;
    static char *d;
    int n;
    while (format[++ptr] != 0)
    {
        d = "";
        switch (format[ptr])
        {
        case '%':
            switch (format[++ptr])
            {
            case '%': // for escaping %
                device.handler('%');
                break;
            case 's': // for strings
                d = va_arg(ap, char *);
                while (*d != 0)
                    device.handler(*d++);
                break;
            case 'd': // for integers
                n = va_arg(ap, int);
                itoa(n, 10, d);
                while (*d != 0)
                    device.handler(*d++);
                break;
            case 'c': // for characters
                device.handler(va_arg(ap, int));
                break;
            case 'x': // for hexadecimals
                itoa(va_arg(ap, s32), 16, d);
                while (*d != 0)
                    device.handler(*d++);
                break;
            default:
                break;
            }
            break;

        default:
            device.handler(format[ptr]);
            break;
        }
    }
    va_end(ap);
}

#endif