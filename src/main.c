#define SILICON_SERIAL_LOG

#include <io/in/kbd.h>
#include <io/conversion.h>
#include <io/log.h>

void kbd_log(u8 data)
{
    serial.out_device.write(data);
    text.out_device.write(data);
}

void gpf_log(struct interrupt_frame *frame)
{
    // Just wait, it prints too fast otherwise
    for (u32 i = 0; i < 100000000; i++)
        ;
    klog("Error: General Protection fault, %s related, at 0x%x", frame->ss == 1 ? "seg." : "not seg.", frame->ip);
}

__attribute__((interrupt))
void int_stub_log(struct interrupt_frame *frame)
{
}

void kmain()
{
    remap_pic(32, 47);
    serial.init(serial.id);
    kbd.init(kbd.id);
    text.init(text.id);
    set_idt_entry(13, gpf_log);
    install_idt();
    klog("Silicon Kernel loaded.", "");
    kprintf("IDT:\n size %d", sizeof(idt));
    for (;;)
        asm("hlt");
}