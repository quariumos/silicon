#ifndef RTC_H
#define RTC_H
#include <cpu/port.h>
void enable_rtc()
{
    outb(0x70, 0x8B);        // select register B, and disable NMI
    s8 prev = inb(0x71);     // read the current value of register B
    outb(0x70, 0x8B);        // set the index again (a read will reset the index to register D)
    outb(0x71, prev | 0x40); // write the previous value ORed with 0x40. This turns on bit 6 of register B
}
#endif