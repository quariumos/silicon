; taken from https://os.phil-opp.com/multiboot-kernel/

section .multiboot
header_start:
    dd 0xe85250d6                ; magic number (multiboot 2)
    dd 0                         ; architecture 0 (protected mode i386)
    dd header_end - header_start ; header length
    ; checksum
    dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))

    ; insert optional multiboot tags here
    align 8 ; needed for GRUB to load it correctly 

    dw 4  ; type, flags tag
    dw 0  ; flags
    dd 12 ; size
    dd 0  ; kernel does not require a console

    align 8

    ; required end tag
    dw 0    ; type
    dw 0    ; flags
    dd 8    ; size
header_end: