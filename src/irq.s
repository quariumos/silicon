extern global_irq_manager
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
%macro IRQ 1
global irq_%1
s_%1:
irq_%1:
push %1
call global_irq_manager
iret
mov word [idt+%1*idt_entry_size], (irq_%1 - s_%1) & 0xffff ; convincing NASM to AND the label, result is offset_lowerbits
mov byte [idt+%1*idt_entry_size+16], 0x08
mov byte [idt+%1*idt_entry_size+32], 0
mov byte [idt+%1*idt_entry_size+40], 0x8e
mov word [idt+%1*idt_entry_size+48], (irq_%1 - s_%1) & 0xffff0000 >> 16 ; convincing NASM to do a little bit more magic, result is offset_higherbits
%endmacro

IRQ 33 ; enable PS/2 keyboard interrupt for testing purposes

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