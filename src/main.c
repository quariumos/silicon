
#include <io/conversion.h>

#include "kernel/io/out/text.c"
#include "kernel/io/duplex/serial.c"

#include "kernel/io/in/keyboard.c"

#include "kernel/cpu/isr.c"

#include <io/base/macros.h>

#ifdef LOG_MICRO_EVENTS
void kbd_log(u8 data)
{
    klog(ANSI_COLOR_CYAN"key hit: %c\n" ANSI_COLOR_RESET, data);
}
#endif 

void gpf_log(struct interrupt_frame *frame)
{
    // Just wait, it prints too fast otherwise
    WAIT(100000000)
    klog("Error: General Protection fault, %s related, at 0x%x\n", frame->ss == 1 ? "seg." : "not seg.", frame->ip);
}

void double_fault_log(struct interrupt_frame *frame)
{
    // Just wait, it prints too fast otherwise
    WAIT(100000000)
    klog("Error: Double fault\n", "");
}

void kmain()
{
    // ISR handling setup
    remap_pic(32, 47);
    clear_idt();
    // IO initialization
    serial_out.flags = COM1;
    serial_in.flags = COM1;
    SERIAL_INIT(COM1);
    INIT(text, 0);
    INIT(keyboard, 0);
    #ifdef LOG_MICRO_EVENTS
    keyboard.handler = kbd_log;
    #endif
    // Continue ISR handling setup
    install_idt();
    klog("kernel loaded.\n", "");
    for (;;)
        asm("hlt");
}
