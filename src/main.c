#include "kernel/io/out/text.c"
#include "kernel/io/in/keyboard.c"
#include "kernel/io/duplex/serial.c"

#include "kernel/cpu/isr.c"

#ifdef SHOULD_LOG
#include <io/base/macros.h>
#include "logging.c"
#endif

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
