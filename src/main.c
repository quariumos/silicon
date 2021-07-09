
#include "kernel/cpu/isr.c"
struct idt_entry idt[256];

#include "kernel/io/out/text.c"
#include "kernel/io/in/keyboard.c"
#include "kernel/io/duplex/serial.c"

#ifdef SHOULD_LOG
#include <io/base/macros.h>
#include "logging.c"
#endif

void kmain()
{
    // ISR handling setup
    remap_pic(32, 47);
    mount_idt(idt);

    // IO initialization
    INIT(text, 0);
    INIT(keyboard, 0);

    // Continue ISR handling setup
#ifdef SHOULD_LOG
    SERIAL_INIT(COM1);
    SERIAL_SET(serial_in, serial_out, COM1);
    klog("kernel loaded.\n", "");
#ifdef LOG_MICRO_EVENTS
    keyboard.handler = kbd_log;
#endif
#endif
    // Do nothing, forever
    for (;;)
        asm("hlt");
}
