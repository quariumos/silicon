#ifndef ISR_H
#define ISR_H
#include <types.h>
#include <cpu/port.h>
#define PIC1 0xA0
#define PIC2 0x20
unsigned short int ocw1 = 0xFFFF;   /* short int = 16 bits */

void eoi(u16 n)
{
    if(n>7)
        outb(0xA0, 0x20);
    outb(0x20, 0x20); //EOI
}
void enable_irq(u32 irq)
{
   ocw1 &= ~(1 << irq);
   if (irq < 8)
      outb(PIC1 + 1, ocw1&0xFF);
   else
      outb(PIC2 + 1, ocw1 >> 8);
}
void disable_irq(u32 irq)
{
   ocw1 |= (1 << irq);
   if (irq < 8)
      outb(PIC1 + 1, ocw1&0xFF);
   else
      outb(PIC2 + 1, ocw1 >> 8); 
}
#endif