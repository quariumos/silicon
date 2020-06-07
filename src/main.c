
#include <io/conversion.h>

#include "kernel/io/out/text.c"
#include "kernel/io/duplex/serial.c"

#include "kernel/cpu/isr.c"

#include <io/base/macros.h>

void kbd_log(u8 data)
{
    klog("%c\n", data);
}

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
    remap_pic(32, 47);
    clear_idt();
    serial_out.flags = COM1;
    serial_in.flags = COM1;
    SERIAL_INIT(COM1);
    text.init(text.id);
    klog("kernel loaded.\n", "");
    for (;;)
        asm("hlt");
}
