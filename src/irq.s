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
cli ; disable interrupts
; calculate offset_lowerbits
mov eax, irq_%1
and eax, 0xffff
; calculate offset_higherbits
mov ebx, irq_%1
and ebx, 0xffff0000
shr ebx, 16
; set the entry
mov [idt+%1*idt_entry_size], eax
mov byte [idt+%1*idt_entry_size+16], 0x08
mov byte [idt+%1*idt_entry_size+32], 0
mov byte [idt+%1*idt_entry_size+40], 0x8e
mov [idt+%1*idt_entry_size+48], ebx
sti ; enable interrupts
irq_%1:
pusha
push %1
call global_irq_manager
popa
iret
%endmacro

IRQ 33

global load_idt
load_idt:
cli  ; disable interrupts
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
sti ; enable interrupts
ret