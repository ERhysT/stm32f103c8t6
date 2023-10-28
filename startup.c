/* STM32F103C8T6 startup */

void _reset(void);
extern void main(void);
extern void _estack(void);	   /* from stm32f103c8t6.ld */
extern void syst_handler(void);
extern void usart_handler(void);

/* interupt request vector table with 16 standard and 60 device
   specific see table 63 in reference manual*/
__attribute__((section(".vectors")))
void (*const tab[16+60])(void) = {
  [0] = _estack, [1] = _reset, [15] = syst_handler
};

/* reset() the device by copying data from FLASH to SRAM and calling
   main

   Initialise the following sections in SRAM using boundries
   determined in the linker script:

  .bss  - statically allocated uninitialised variables so set to zero

  .data - global and static local variables so copy from flash 
*/
__attribute__((naked, noreturn))
void
_reset(void)
{
  typedef long ldsym;		/* linker symbols */
  extern ldsym _sbss, _ebss, _sdata, _edata, _sidata;

  for (ldsym *src = &_sbss; src < &_ebss;)
     *src++ = 0;
  for (ldsym *src = &_sdata, *dst = &_sidata; src < &_edata;)
    *src++ = *dst++;

  main();             
  for (;;)
    (void) 0;  // in case main() returns
}
