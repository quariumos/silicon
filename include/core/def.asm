[extern isr_manager]

%macro IRQ 1
[global irq%1]
irq%1:
pusha
push %1
call isr_manager
pop eax
popa
iret
%endmacro

%macro EXC 1
[global exc%1]
exc%1:
pusha
push %1
call isr_manager
pop eax
popa
iret
%endmacro

IRQ 32
IRQ 33
IRQ 34
IRQ 35
IRQ 36
IRQ 37
IRQ 38
IRQ 39
IRQ 40
IRQ 41
IRQ 42
IRQ 43
IRQ 44
IRQ 45
IRQ 46
IRQ 47

EXC 0
EXC 1
EXC 2
EXC 3
EXC 4
EXC 5
EXC 6
EXC 7
EXC 8
EXC 10
EXC 11
EXC 12
EXC 13
EXC 14
; exc9 and exc15 were excluded, 9 is deprecated, 15 is reserved,
; there are actually more exceptions but only these are going to be 
; implemented in the alpha


[global load_idt]
load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	ret