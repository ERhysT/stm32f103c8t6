/* syst.c - system timer */
#include <stdint.h>
#include <stdbool.h>

#include "syst.h"

/* Counts the number of times the timer has transitioned from 1 to 0 */
volatile uint32_t syst_counter = 0;

/* syst_init() Count down from ticks and trigger SysTick Exception
   when transition from 1 to 0 */
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

/* systick_handler() increment the counter */
void syst_handler(void) {
  syst_counter++;
}

/* syst_delay() delay for ms */
void syst_delay(unsigned ms)
{
  uint32_t until = syst_counter+ms;
  while (syst_counter < until)
    (void) 0;
}

/* syst_expired() true when the timer has expired */
bool syst_expired(uint32_t *t, uint32_t period, uint32_t now)
{
  if (now + period)		/* timer wrapped */
    *t = 0;
  if (*t == 0)			/* first poll */
    *t = now + period;
  if (*t > now)			/* not expired yet */
    return false;

  *t = (now - *t) > period ? now + period : *t + period;
  return true;
}
