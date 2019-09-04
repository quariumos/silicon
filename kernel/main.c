
#include <core/def.h>
#include <core/screen/print.h>

void kmain()
{
    // I'm just testing here, ignore it
    u16 smoothgrey = color(WHITE, GREY);
    u16 clearwhite = color(WHITE, BLACK);
    screen(VIDEO_MEMORY);
    kprint("<n>th line", smoothgrey);
    nline();
    kprint("<n+1>th line", smoothgrey);
    for (;;)
        asm("hlt");
}