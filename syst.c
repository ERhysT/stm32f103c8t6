/* syst.c - system timer */
#include <stdint.h>
#include <stdbool.h>

#include "syst.h"

/* Counts the number of times the timer has transitioned from 1 to 0 */
volatile uint32_t systick = 0;

/* syst_handler() increment the counter on interupt

   Function handler should be added to the interrupt vector table. */
void syst_handler(void) {
  systick++;
}

/* syst_init() Count down from ticks and trigger SysTick Exception
   when transition from 1 to 0

  Reset value is set to ticks, current value is cleared and the timer
  is configured to raise an exception on transition from 1 to 0.

  For a millisecond timer:

  HSI -> SYSCLK -> AHB prescaler 0x00 -> /8   -> Cortex Sytem Timer
  8MHz   8MHz      8MHz                  1MHz    1MHz
     
  So we will get 1e6 ticks per second, we want 1e3 ticks per second
  (/ 8e6 8 1000) ;1000.0
*/
void syst_init(struct syst* syst, uint32_t ticks)
{
  /* Size of the reload value resister determines the maximum number
     of ticks */
  if (ticks > SYST_RVR_RELOAD_MSK)
    return;

  syst->rvr |= (uint32_t)(SYST_RVR_RELOAD_MSK & ticks);
  syst->cvr &= (uint32_t)(~SYST_CVR_CURRENT_MSK); 
  syst->csr |= (uint32_t)(SYST_CSR_ENABLE_MSK | SYST_CSR_TICKINT_MSK);
}

/* syst_delay() delay for ms */
void syst_delay(unsigned ms)
{
  uint32_t until = systick + ms;
  while (systick < until)
    (void) 0;
}

/* syst_timer_expired() */
bool
syst_timer_expired(uint32_t *t, uint32_t prd, uint32_t now)
{
  if (now + prd < *t)		/* wrapped */
    *t = 0;
  if (*t == 0)			/* initialise */
    *t = now + prd;
  if (now < *t)			/* not expired */
    return false;

  *t = now + prd;		/* reset, expired */
  return true;
}
