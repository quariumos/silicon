extern global_isr_manager
%define IDT_SIZE 256
section .bss
struc idt_entry
     offset_lowerbits   resb 2
     selector resb 2
     zero   resb 1
     type_attr resb 1
     offset_higherbits resb 2
endstruc
idt resb idt_entry_size * IDT_SIZE
idt_ptr resb 8 * 2
section .text
%macro ISR 1
global isr_%1
isr_%1:
push %1
call global_isr_manager
iret
mov eax, isr_%1
and eax, 0xffff
mov [idt+%1*idt_entry_size], ax
mov byte [idt+%1*idt_entry_size+2], 0x08
mov byte [idt+%1*idt_entry_size+3], 0
mov byte [idt+%1*idt_entry_size+4], 0x8e
mov ebx, isr_%1
and ebx, 0xffff0000
shr ebx, 16
mov [idt+%1*idt_entry_size+6], bx
%endmacro

ISR 33 ; enable PS/2 keyboard interrupt for testing purposes

global load_idt
load_idt:
; save used registers
push eax
push ebx
; calculate first entry
mov eax, idt_entry_size
imul eax, IDT_SIZE
mov ebx, idt
and ebx, 0xffff
shl ebx, 16
add eax, ebx
; place first entry
mov [idt_ptr], eax
; calculate second entry
mov eax, idt
shr eax, 16
; place second entry
mov [idt_ptr+8], eax
; load idt
lidt [idt_ptr]
; restore used registers
pop ebx
pop eax
ret