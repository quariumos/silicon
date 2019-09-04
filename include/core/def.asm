[global load_idt]
load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	ret