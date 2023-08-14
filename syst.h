/* System timer, syst

The processor has a 24-bit system timer, SysTick, that counts down
from the reload value to zero, reloads, that is wraps to, the value in
the SYST_RVR register on the next clock edge, then counts down on
subsequent clocks. When the processor is halted for debugging the
counter does not decrement.

DUI05521 Cortex M3 Generic User Guide 4.4 p150

*/

#ifndef SYST_HEADER
#define SYST_HEADER

#include <stdint.h>

#define SYST ((struct syst *) 0xE000E010)

extern volatile uint32_t syst_counter;	/* timer overflow counter  */

/* syst - processor system timer registers */
struct syst {
  volatile uint32_t csr, rvr, cvr, calib;
};

enum {				/* control and status register */
  SYST_CSR_ENABLE_MSK     = 1UL,
  SYST_CSR_TICKINT_MSK    = 1UL << 1,
  SYST_CSR_CLKSOURCE_MSK  = 1UL << 2, 
  SYST_CSR_COUTFLAG_MSK   = 1UL << 16
};

enum {				/* reload value register */
  SYST_RVR_RELOAD_MSK  = 0x00FFFFFF
};

enum {				/* current value register */
  SYST_CVR_CURRENT_MSK = 0x00FFFFFF
};

enum {				/* calibration value register */
  SYST_CALIB_TENMS_MSK = 0x00FFFFFF,
  SYST_CALIB_SKEW_MSK  = 1UL << 30,
  SYST_CALIB_NOREF_MSK = 1UL << 31
};

void syst_init(struct syst *syst, uint32_t ticks);
void syst_handler(void);
void syst_delay(unsigned ms);

#endif /* SYST_HEADER */
