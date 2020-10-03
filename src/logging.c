
#include <kstdlib.h>
#include <cpu/isr.h>

void kbd_log(u8 data)
{
    klog(ANSI_COLOR_CYAN"key hit: %c\n" ANSI_COLOR_RESET, data);
    text_setc(data);
}

void gpf_log(struct interrupt_frame *frame)
{
    // Just wait, it prints too fast otherwise
    WAIT(100000000)
    klog("Error: General Protection fault, %s related, at 0x%x\n", frame->ss == 1 ? "seg." : "not seg.", frame->ip);
    #ifdef LOG_STACK_ON_GPF

    #endif
}

void double_fault_log(struct interrupt_frame *frame)
{
    // Just wait, it prints too fast otherwise
    WAIT(100000000)
    klog("Error: Double fault\n", "");
}