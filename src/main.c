#define SILICON_SERIAL_LOG

#include <io/in/kbd.h>
#include <io/conversion.h>
#include <io/log.h>

void kbd_log(u8 data)
{
    text.out_device.write(data);
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
    kbd.init(kbd.id);
    serial.init(serial.id);
    text.init(text.id);
    set_idt_entry(13, gpf_log);
    set_idt_entry(8, double_fault_log);
    install_idt();
    kbd.in_device.stream->subscriber = kbd_log;
    klog("Silicon Kernel loaded.\n", "");
    kprintf("IDT:\n size %d", sizeof(idt));
    for (;;)
        asm("hlt");
}
