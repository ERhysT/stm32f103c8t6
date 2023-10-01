#include "rcc.h"
#include "gpio.h"

/** GPIO configuration low/high registers (crl/crh)

   Pins 0-7 are in the configuration register LOW (crl) and pins 8-15
   are in configuration register HIGH (crh).

   Macros are defined to determine both the control register and the
   bit number of the mode and configuration bits within a control
   register.
**/

/* GPIO_CRX() address of correct (high/low) configuration register for
   provided pin number*/
#define GPIO_CRX(gpio, pin) ((uint32_t *)((pin > 7) ? &gpio->crh : &gpio->crl))

/* GPIO_CR_MODE_BIT() bit number of mode flags in configuration
   register for provided pin number*/
#define GPIO_CR_MODE_BIT(pin) ((uint32_t)((pin % 8) * 4))

/* GPIO_CR_MODE_BIT() bit number of configuration flags in
   configuration register for provided pin number */
#define GPIO_CR_CNF_BIT(pin)  ((uint32_t)(GPIO_CR_MODE_BIT(pin) + 2))

/** gpio_setup() Setup and configure a gpio pin
 
 * Clock the pin bank using the rcc register.

 * Determine the configuration register for the pin, which is split
   into high and low about 7.

 * Apply the provided mode and configuration values.

**/

struct gpio *
gpio_setup(char bank, unsigned pin, uint32_t mode, uint32_t cnf)
{
  struct rcc *rcc = RCC;
  rcc->apb2enr |= (1<<RCC_APB2ENR_IOPXEN(bank));

  struct gpio *gpio = GPIO(bank);
  volatile uint32_t *cr = GPIO_CRX(gpio, pin);
  *cr |= (cnf<<GPIO_CR_CNF_BIT(pin)) | (mode<<GPIO_CR_MODE_BIT(pin));

  return gpio;
}
