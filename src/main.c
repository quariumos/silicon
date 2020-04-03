#define SILICON_SERIAL_LOG

#include <io/duplex/serial.h>
#include <io/in/kbd.h>
#include <io/out/text.h>
#include <io/conversion.h>
#include <io/kprintf.h>

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
    kprintf(serial.out_device, "Error: General Protection fault, %s related, at %x\n", frame->ss == 1 ? "seg." : "not seg.", frame->ip);
}

void kmain()
{
    remap_pic(32, 47);
    serial.init(serial.id);
    kbd.init(kbd.id);
    text.init(text.id);
    set_idt_entry(13, gpf_log);
    install_idt();
    kprintf(text.out_device, ">> Silicon Kernel loaded.\n");
    kprintf(text.out_device, "IDT:\n size %d\n", sizeof(idt));
    for (;;)
        asm("hlt");
}