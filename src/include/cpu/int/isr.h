#ifndef ISR_H
#define ISR_H
#include <types.h>
#include <cpu/port.h>

#define PIC1 0x20 // Base address of master PIC
#define PIC2 0xA0 // Base address of slave PIC
#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1 + 1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA (PIC2 + 1)

struct interrupt_frame
{
   u16 ip;
   u16 cs;
   u16 flags;
   u16 sp;
   u16 ss;
};

void eoi(u16 n)
{
   if (n > 7)
      outb(PIC2, 0x20);
   outb(PIC1, 0x20); //EOI
}
void pic_mask(unsigned char n)
{
   u16 port;
   u8 value;

   if (n < 8)
   {
      port = PIC1_DATA;
   }
   else
   {
      port = PIC2_DATA;
      n -= 8;
   }
   value = inb(port) | (1 << n);
   outb(port, value);
}

void pic_unmask(unsigned char n)
{
   u16 port;
   u8 value;

   if (n < 8)
   {
      port = PIC1_DATA;
   }
   else
   {
      port = PIC2_DATA;
      n -= 8;
   }
   value = inb(port) | ~(1 << n);
   outb(port, value);
}
#endif