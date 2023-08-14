#include "rcc.h"
#include "gpio.h"
#include "syst.h"
#include "main.h"

static inline void spin(volatile uint32_t count)
{
  while (count--)
    (void) 0;
}

#define LEDPIN 13		/* PC13 */

int
main(void) {
  struct syst *syst = SYST;

  /* PC13 onboard LED */

  struct gpio *gpioc = gpio_init('C', LEDPIN,
				 GPIO_CR_CNF_OUTPUT_OD,
				 GPIO_CR_MODE_OUTPUT_10MHZ);
  /* Blink */
  for (;;)  {
    gpioc->bsrr = GPIO_BSRR_RESET_BIT(LEDPIN);
    spin(999999);
    gpioc->bsrr = GPIO_BSRR_SET_BIT(LEDPIN);
    spin(999999);
  }

  return 0; 
}




