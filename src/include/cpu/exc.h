#ifndef EXC_H
#define EXC_H
#include <cpu/isr.h>
// exception handlers
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

void exc_handler_init()
{
    set_idt_entry(13, gpf_log);
    set_idt_entry(8, double_fault_log);
}
#endif