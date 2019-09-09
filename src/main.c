
#include <def/def.h>
#include <sys/int.h>
#include <sys/exc.h>

#define KIO
#define DEBUG

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

// Enable keyboard handler
void keyboard(void (*input_handler_arg)(u8 scancode, u8 shift, u8 caps))
{
    input_handler = input_handler_arg;
    if (!has_isr(KEYBOARD_IRQ))
    {
        outb(0x21, 0xfd);
        outb(0xa1, 0xff);
        isr(KEYBOARD_IRQ, kb_handler);
    }
}

#endif

// Kernel will only provide(once it's ready to) IPC/Messaging, Memory allocation interface and a basic text mode + keyboard drivers
// All other functionality will be modular, as in modular kernels and microkernels
void kmain()
{
    u16 whitefore = vid_color(WHITE, BLACK);
    u16 blackfore = vid_color(BLACK, WHITE);
    vid_cursor_set_size(15, 15);
    for (u32 i = 0; i < VIDEO_MEMORY_SIZE; i++)
    {
        vid_character_set(' ', whitefore, NILINIL + i);
    }

#ifdef INT
    idt();
    // Generic handler stubs for exceptions, for now
    for (u32 i = 0; i < 14; i++)
    {
        isr(i, generic_exception_handler);
    }
    asm("sti");
#endif
#ifdef KIO
    keyboard(on_input);
#endif
    kprint("Checking how the cursor moves!", whitefore);
#ifdef DEBUG
    serial(COM1); // Enable serial port 1
    serial_write_string(COM1, "Kernel Booted.");
    serial_write(COM1, 10);
#endif
    for (;;)
        asm("hlt");
}