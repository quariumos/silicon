
ENTRY(kmain)
 
SECTIONS
{

	. = 0x1000;

	.text BLOCK(0x2000) : ALIGN(4K)
	{
		*(.text)
	}
 
	.data BLOCK(0x3000) : ALIGN(4K)
	{
		*(.data)
	}
 
	.bss BLOCK(0x4000) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}

}