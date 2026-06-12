ENTRY(Platform_ResetHandler)

MEMORY
{
	FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 512K

	STACK (rwx) : ORIGIN = 0x20000000, LENGTH = 1K
	RAM   (rwx) : ORIGIN = 0x20000400, LENGTH = 128K - 1K
}

SECTIONS
{
	.text :
	{
		KEEP(*(.isr_vector))

		*(.text .text.*)
		*(.rodata .rodata.*)

		. = ALIGN(4);
		_sidata = .;
	} >FLASH

	.data :
	{
	    . = ALIGN(4);
	    _sdata = .;

	    *(.kernel_data)
	    *(.data .data.*)

	    . = ALIGN(4);
	    _edata = .;
	} >RAM AT >FLASH

	.bss (NOLOAD) :
	{
	    . = ALIGN(4);
	    _sbss = .;

	    *(.kernel_bss)
	    *(.bss .bss.*)
        *(COMMON)

        . = ALIGN(4);
        _ebss = .;
	} >RAM

	.after :
    {
        . = ALIGN(4);
        _after_code = .;
    } >FLASH
}