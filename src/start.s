extern kmain
gdt:

gdt_null:
   dq 0
gdt_code:
dw 0FFFFh
dw 0
db 0
db 10011010b
db 11001111b
db 0
gdt_data:
   dw 0FFFFh
   dw 0
db 0
db 10010010b
db 11001111b
db 0
gdt_end:

gdt_desc:
   dw gdt_end - gdt - 1
   dd gdt
global _start

_start:
cli ;block interrupts
;we must load gdt
lgdt [gdt_desc]
jmp 0x0008:fix_cs
fix_cs:
mov ax, 0x0010
mov ds, ax
mov es, ax
mov fs, ax
mov gs, ax
mov ss, ax
call kmain
jmp $   ;halt the CPU