extern global_isr_manager
section .text

; %1 is ISR number, %2 is gate type
%macro ISR 2
global isr_%1
isr_%1:
push %1
call global_isr_manager
iret
%endmacro