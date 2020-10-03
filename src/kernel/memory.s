
struc address_range
        .BaseLow resb 4
        .BaseHigh resb 4
        .LenLow resb 4
        .LenHigh resb 4
        .Type resb 4
endstruc

section .rodata
_memory_k_820_struct_size equ address_range-$
ssssss db 'Fred is an idiot', 13, 0

section .text
global _get_memory_k_820
extern gpf_log

_get_memory_k_820:
mov eax, 59521 ; E820h
mov ebx, [esp+4]
mov di, [esp+8]
mov ecx, [_memory_k_820_struct_size]
mov edx, 'SMAP'
int 15h
mov eax, 1
ret