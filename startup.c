/* STM32F103C8T6 startup */

void _reset(void);
extern void __libc_init_array();
extern void __stack_end__(void);
extern void main(void);
extern void syst_handler(void);
extern void usart_handler(void);

/* interupt request vector table with 16 standard and 60 device
   specific see table 63 in reference manual*/
__attribute__((section(".vectors")))
void (*const tab[16+60])(void) = {
  [0] = __stack_end__, [1] = _reset, [15] = syst_handler
};

/* reset() the device by copying data from FLASH to SRAM, initialise
   libc and call main function.

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
  extern ldsym __bss_start__, __bss_end__,
    __data_start__, __data_end__, __data_load_start__;

  for (ldsym *src = &__bss_start__;
       src < &__bss_end__;)
     *src++ = 0;
  for (ldsym *src = &__data_start__, *dst = &__data_load_start__;
       src < &__data_end__;)
    *src++ = *dst++;

  __libc_init_array();
  main();             

  for (;;) // in case main() returns
    (void) 0;  
}
