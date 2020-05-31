
#include <io/in/kbd.h>
#include <io/conversion.h>
#include <io/log.h>

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
    kbd.init(kbd_log);
    serial.init(serial.id);
    text.init(text.id);
    set_idt_entry(13, gpf_log);
    set_idt_entry(8, double_fault_log);
    install_idt();
    klog("Silicon Kernel loaded.\n", "");
    for (;;)
        asm("hlt");
}
