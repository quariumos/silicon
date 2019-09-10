
#include <def/def.h>
#include <def/serial.h>

#define KIO
#define DEBUG
#define INT

#ifdef INT
#include <sys/int.h>
#include <sys/exc.h>
#include <sys/seg.h>
#endif

#ifdef KIO
#include <io/i/keyboard.h>
#include <io/o/screen/print.h>
#endif

#ifdef KIO

void on_input(u8 value, u8 shift, u8 caps)
{
    // It just does nothing right now
    return;
}

#endif

// Kernel will only provide(once it's ready to) IPC/Messaging, Memory allocation interface and a basic text mode + keyboard drivers
// All other functionality will be modular, as in modular kernels and microkernels
void kmain()
{
#ifdef KIO
    u16 whitefore = vid_color(WHITE, BLACK);
    u16 blackfore = vid_color(BLACK, WHITE);
    vid_cursor_set(15, 15);
    vid_clear(NILINIL, whitefore);
#endif
#ifdef INT
#endif
    for (u32 i = 0; i < 10; i++)
    {
        kprint(NILINIL, "Silicon Kernel loaded.\n", whitefore);
    }
#ifdef DEBUG
    serial(COM1); // Enable serial port 1
    serial_write_string(COM1, "Kernel Loaded.");
    serial_write(COM1, 10);
#endif
    for (;;)
        asm("hlt");
}