/* STM32F103C8T6 Linker script

 *  Memory layout overview

   ROM    | SRAM
   =======|======
   data   | stack  <- largest address
   rodata | heap
   text   | bss
   vectors| data   <- smallest address

   vectors  vector table at the start of flash memory (rom)
   text     program code in flash memory
   rodata   read-only data in flash memory
   data     initialized data, loaded from flash to SRAM
   bss	    uninitialized data section in SRAM
   heap     heap space located between bss and the stack in SRAM
   stack    stack space grows downward, starting from the top of SRAM

 * RAM - (20k) layout and symbols

	      0x20005000   	    physical end of sram/
			   	    start of stack
   [stack]
	      __stack_end__ 	    end of stack
   [heap]
	      __bss_end__      	    end of bss section
   .bss
	      __bss_start__   	    start of bss section
   .data
	      __data_load_start__   start of the data section
	      0x20000000
	      
 * ROM - Flash memory (64k) layout and symbols

	      0x0800ffff   	    flash memory
	      __data_end__    	    end of data section
   .data
	      __data_start__  	    start of data section
   .rodata
   .text
   .vectors
	      0x08000000   	    physical start of flash memory

**/

/* Entry point in the ELF header, duplicate the vector table. This is
for the debugger which cannot see the vector table */
ENTRY(_reset);

MEMORY {
  rom(rx)  : ORIGIN = 0x08000000, LENGTH = 64k
  sram(rwx)  : ORIGIN = 0x20000000, LENGTH = 20k - 4k /* 4k for stack */
}
__stack_end__ = ORIGIN(sram) + LENGTH(sram); /* end of the stack */

SECTIONS {
  .vectors : {
    KEEP(*(.vectors))
  }					> rom
 
  .text : {
     *(.text*)
     *(.init)
     *(.fini)
  }					> rom
 
  .rodata : {
    *(.rodata*)
  }					> rom
 
  .data : {
    __data_start__ = .;
    *(.data SORT(.data.*))
    __data_end__ = .;
  }					> sram AT > rom
  __data_load_start__ = LOADADDR(.data);
 
  .bss : {
    __bss_start__ = .;
    *(.bss SORT(.bss.*) COMMON)
    . = ALIGN(8);
    __bss_end__ = .;
 
    end = .;
  }					> sram

}
