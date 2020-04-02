#ifndef IRQ_H
#define IRQ_H

#include <cpu/int/idt.h>
#include <cpu/int/isr.h>

#ifdef SILICON_SERIAL_LOG
#include <io/kprintf.h>
#include <io/duplex/serial.h>
#endif

typedef void (*irq_handler_t)();

irq_handler_t irq_handler_list[IDT_SIZE] = {
    noop,
};

void set_irq_handler(int vector, irq_handler_t handler)
{
    irq_handler_list[vector] = handler;
}

void global_irq_manager(int n)
{
#ifdef SILICON_SERIAL_LOG
    kprintf(serial.out_device, "Log:IRQ %d\n", n);
#endif
    irq_handler_t f = irq_handler_list[n];
    if (f != noop)
        irq_handler_list[n]();
    eoi(n - 32);
}
#endif