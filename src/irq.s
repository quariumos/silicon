extern main_irq_handler
%macro IRQ 1
global handler_%1
handler_%1:
pusha
push %1
call main_irq_handler
popa
iret
%endmacro

IRQ 1