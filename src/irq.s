extern global_irq_manager
%macro IRQ 1
global irq_%1
irq_%1:
pusha
push %1
call global_irq_manager
popa
iret
%endmacro

IRQ 33