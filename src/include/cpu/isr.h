#ifndef CPU_ISR_H
#define CPU_ISR_H
#include <types.h>
// IDT part
struct idt_entry
{
    unsigned short int offset_lowerbits;
    unsigned short int selector;
    u8 zero;
    u8 type_attr;
    unsigned short int offset_higherbits;
} __attribute__((packed));

struct interrupt_frame
{
    u16 ip;
    u16 cs;
    u16 flags;
    u16 sp;
    u16 ss;
};
#define IDT_SIZE 256
// PIC part
#define PIC1 0x20 // Base address of master PIC
#define PIC2 0xA0 // Base address of slave PIC
#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1 + 1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA (PIC2 + 1)
typedef void (*isr_handler_t)(struct interrupt_frame *);

extern void eoi(u16 n);
extern void set_idt_entry(int vector, isr_handler_t handler);
extern void pic_mask(unsigned char n);
extern void pic_unmask(unsigned char n);
#endif