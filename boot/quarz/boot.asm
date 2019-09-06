; Define values
KERNEL_SIZE equ 36
KERNEL_ADDRESS equ 0x1000
; Set up the offset
[org 0x7c00]
xor ax, ax
mov ds, ax
cld 
    ; Reset video mode
    mov ah, 00h
    mov al, 3
    int 10h

    mov ah, 0x02      ; Read disk BIOS call 
    mov cl, 0x02      ; sector to start reading from
    mov al, KERNEL_SIZE ; number of sectors that will be read (modify if your second stage grows)
    mov ch, 0x00      ; cylinder number
    mov dh, 0x00      ; head number
    xor bx, bx
    mov es, bx        ; es=0x0000
    mov bx, KERNEL_ADDRESS    ; es:bx(0x0000:0x8000) forms complete address to read sectors to
    int 0x13          ; Make BIOS disk services call (int 0x13/ah=2) to read sectors

    ; Try enabling A20 line, this does not guarantee anything though
    in al,0xee

    jmp init_pm

start_gdt: ; don't remove the labels, they're needed to compute sizes and jumps
    ; the GDT starts with a null 8-byte
    dd 0x0 ; 4 byte
    dd 0x0 ; 4 byte

; GDT for code segment
code: 
    dw 0xffff    ; segment length, bits 0-15
    dw 0x0       ; segment base, bits 0-15
    db 0x0       ; segment base, bits 16-23
    db 10011010b ; flags (8 bits)
    db 11001111b ; flags (4 bits) + segment length, bits 16-19
    db 0x0       ; segment base, bits 24-31

; GDT for data segment
data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

end_gdt:

; GDT descriptor
gdt_desc:
    dw end_gdt - start_gdt - 1 
    dd start_gdt ; Start address

CODE equ code - start_gdt
DATA equ data - start_gdt

[bits 16]
init_pm:
    cli ; Disable all interrupts
    lgdt [gdt_desc] ; Load the GDT
    mov eax, cr0
    or eax, 0x1 ; Get to protected mode
    mov cr0, eax
    jmp CODE:pm

    hlt ; never executed
    
[bits 32]
pm: ; In protected mode now
    call KERNEL_ADDRESS

; Padding 
    times 510-($-$$) db 0 
    db 0x55
    db 0xAA