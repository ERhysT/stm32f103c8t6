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

 * Flash memory (64k) layout and symbols

	      0x0800ffff   physical end of flash memory
	      _end         end of flash memory
	      _edata       end of data section
   .data
	      _sdata       start of data section
   .rodata
   .text
   .vectors
	      0x08000000   physical start of flash memory

 * SRAM (20k) layout and symbols

	      0x20005000   physical end of sram/
			   start of stack
   [stack]
	      _estack      end of stack
   [heap]
	      _ebss        end of bss section
   .bss
	      _sbss        start of bss section
   .data
	      _sidata      start of the data section
	      0x20000000
	      
   The symbols are all 32 bit integers

**/

/* Entry point in the ELF header, duplicate the vector table. This is
for the debugger which cannot see the vector table */
ENTRY(_reset);

MEMORY {
  rom(rx)  : ORIGIN = 0x08000000, LENGTH = 64k
  sram(rwx)  : ORIGIN = 0x20000000, LENGTH = 20k - 4k /* 4k for stack */
}
_estack     = ORIGIN(sram) + LENGTH(sram); /* end of the stack */

SECTIONS {
 .vectors  : { KEEP(*(.vectors)) }   > rom
 .text     : { *(.text*) }           > rom
 .rodata   : { *(.rodata*) }         > rom

 .data : {
   _sdata = .;
   *(.data SORT(.data.*))
   _edata = .;
 } > sram AT > rom
 _sidata = LOADADDR(.data);

 .bss : {
   _sbss = .;
   *(.bss SORT(.bss.*) COMMON)
   _ebss = .;
 } > sram

 . = ALIGN(8);
 _end = .;
}
