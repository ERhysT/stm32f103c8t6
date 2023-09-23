/* STM32F103C8T6 Linker script */

/* Entry point in the ELF header, duplicate the vector table. This is
for the debugger which cannot see the vector table */
ENTRY(_reset);
	
MEMORY {
  flash(rx)  : ORIGIN = 0x08000000, LENGTH = 64k
  sram(rwx)  : ORIGIN = 0x20000000, LENGTH = 20k - 4k /* 4k for stack */
}
_estack     = ORIGIN(sram) + LENGTH(sram);    /* stack points to end of SRAM */

SECTIONS {
 .vectors  : { KEEP(*(.vectors)) }   > flash
 .text     : { *(.text*) }           > flash
 .rodata   : { *(.rodata*) }         > flash

 .data : {
   _sdata = .;                 /* .data section start */
   *(.first_data)
   *(.data SORT(.data.*))
   _edata = .;                 /* .data section end */
 } > sram AT > flash
 _sidata = LOADADDR(.data);

 .bss : {
   _sbss = .;                  /* .bss section start */
   *(.bss SORT(.bss.*) COMMON)
   _ebss = .;                  /* .bss section end */
 } > sram

 . = ALIGN(8);
 _end = .;                     /* for cmsis_gcc.h  */
}