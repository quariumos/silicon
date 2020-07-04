#include "kernel/io/out/text.c"
#include "kernel/io/in/keyboard.c"
#include "kernel/io/duplex/serial.c"

#include "kernel/cpu/isr.c"

#include <multiboot2.h>

#ifdef SHOULD_LOG
#include <io/base/macros.h>
#include "logging.c"
#endif

void kmain(unsigned long magic, unsigned long addr)
{
    struct multiboot_tag *tag;
    unsigned size;

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

    // Multiboot 2 checks
    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC)
        klog("invalid bootloader magic: 0x%x\n", (unsigned)magic);
    if (addr & 7)
        klog("invalid mbi: 0x%x\n", addr);
    for (;;)
        asm("hlt");
}
