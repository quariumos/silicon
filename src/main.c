
#include "kernel/cpu/isr.c"

#include "kernel/io/out/text.c"
#include "kernel/io/in/keyboard.c"
#include "kernel/io/duplex/serial.c"

#ifdef SHOULD_LOG
#include <io/base/macros.h>
#include "logging.c"
#endif

long _k_820_continuation = 0;
typedef struct
{
    long int BaseLow;
    long int BaseHigh;
    long int LenLow;
    long int LenHigh;
    long int Type;
} _k_820_memory_range;

extern int _get_memory_k_820(long continuation, _k_820_memory_range *buffer);

void kmain()
{
    // ISR handling setup
    remap_pic(32, 47);
    clear_idt();
// IO initialization
#ifdef SHOULD_LOG
    SERIAL_INIT(COM1);
    SERIAL_SET(serial_in, serial_out, COM1);
#ifdef LOG_MICRO_EVENTS
    keyboard.handler = kbd_log;
#endif
#endif
    INIT(text, 0);
    INIT(keyboard, 0);
    // Continue ISR handling setup
    install_idt();
#ifdef SHOULD_LOG
    klog("kernel loaded.\n", "");
#endif
    for (;;)
        asm("hlt");
}
