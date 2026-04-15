ENTRY(Platform_ResetHandler)

MEMORY
{
	FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 256K

	STACK (rwx) : ORIGIN = 0x20000000, LENGTH = 2K
	RAM   (rwx) : ORIGIN = 0x20000800, LENGTH = 64K - 2K
}

SECTIONS
{
	.text :
	{
		*(.text)
		*(.text.*)
		_isr_base = .;
		KEEP(*(.isr_vector))
		_sidata = .;
		*(.rodata)

		. = ALIGN(4);
	} >FLASH

	.data :
	{
	    . = ALIGN(4);
	    _sdata = .;

	    *(.kernel_data)

	    *(.data)
	    *(.data*)

	    . = ALIGN(4);
	    _edata = .;
	} >RAM AT >FLASH

	.bss (NOLOAD) :
	{
	    . = ALIGN(4);
	    _sbss = .;

	    *(.kernel_bss)

	    *(.bss)
	    *(.bss*)
        *(COMMON)

        . = ALIGN(4);
        _ebss = .;
	} >RAM
}