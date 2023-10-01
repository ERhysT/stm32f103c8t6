#include "rcc.h"
#include "gpio.h"

/* Bit number of IO port */

/* gpio_init() power up gpio pin

   bank: GPIO bank from A to G
   pin:  pin number from 0 to 15
   mode: operating mode from GPIO_CR_MODE flags
   cnf:  configuration from GPIO_CR_CNF flags

 */
struct gpio *
gpio_init(char bank, unsigned pin, uint32_t cnf, uint32_t mode)
{
  /* power up the bank containing the pin */
  struct rcc *rcc = RCC;
  rcc->apb2enr |= 1UL << RCC_APB2ENR_IOPXEN(bank);

  /* separate configuration registers for high and low pins */
  struct gpio *gpio = GPIO(bank);
  volatile uint32_t *cr = (pin > 7) ? &gpio->crh : &gpio->crl;
  *cr |= cnf << GPIO_CR_CNF_BIT(pin);
  *cr |= mode << GPIO_CR_MODE_BIT(pin);

  return gpio;
}
