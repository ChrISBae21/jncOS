/* ___________
* |           |   ^
* |   STACK   |   |
* |___________| 0x80000
* |           |
* |   TEXT    |
* |___________|
* |           |
* |  RODATA   |
* |___________|
* |           |
* |   DATA    |
* |___________|
* |           |
* |    BSS    |
* |___________|
*/




__zero_addr = 0;
__section_start = 0x80000;

ENTRY(_start)


SECTIONS
{
    . = __zero_addr;

    /*----------------------------------------------------------------------------------------
    *                                   Stack segment
    -----------------------------------------------------------------------------------------*/
    .stack (NOLOAD) :
    {
        . += __section_start;  
        __stack_low = .;        /* stack starts at 0x80000 --> 0x0 */
    }

    
    __start = .;    /* start of segments */

    /*----------------------------------------------------------------------------------------
    *                                   Text segment
    -----------------------------------------------------------------------------------------*/
	__text_start = .;   /* start of text segment */
    .text : 
    { 
        KEEP(*(.text.boot))
        *(.text) 
    }
    __text_end = .;     /* end of text segment */

    /*----------------------------------------------------------------------------------------
    *                                 Read-Only segment
    -----------------------------------------------------------------------------------------*/
	__rodata_start = .;
    .rodata : ALIGN(8)
    {
        *(.rodata) 
    }
    __rodata_end = .;

    /*----------------------------------------------------------------------------------------
    *                                   Data segment
    -----------------------------------------------------------------------------------------*/    

	__data_start = .;
    .data : 
    { 
        *(.data) 
    }
    __data_end = .;

    /*----------------------------------------------------------------------------------------
    *                              BSS (unallocated) segment
    -----------------------------------------------------------------------------------------*/

	.bss : ALIGN(16)
    { 
        __bss_start = .;
        *(.bss*) 
        . = ALIGN(16);
        __bss_end = .;

    } 
}