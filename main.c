#include "stddef.h"

#include "rcc.h"
#include "gpio.h"
#include "syst.h"
#include "main.h"

#define LEDPIN 13		/* PC13 */

void toggle_led(void)
{
  static uint32_t timer = 0;
  static bool on = true;
  struct gpio *gpioc = gpio_init('C', LEDPIN,
				 GPIO_CR_CNF_OUTPUT_OD,
				 GPIO_CR_MODE_OUTPUT_10MHZ);

  if ( syst_timer_expired(&timer, 1000, systick) ) {
    if (on) {
      gpioc->bsrr = GPIO_BSRR_RESET_BIT(LEDPIN);
    } else {
      gpioc->bsrr = GPIO_BSRR_SET_BIT(LEDPIN);
    }

    on ^= true;
  }
}

int
main(void) {

  /* millisecond timer */
  struct syst *syst = SYST;
  syst_init(syst, 1000);

  /* process tasks */
  size_t n = 0;
  void (*tasks[16])(void);
  tasks[0] = toggle_led;
  tasks[1] = NULL;
  
  while(true)
    if (NULL == tasks[n])
      n = 0;
    else
      tasks[n++]();

  return 0; 
}




