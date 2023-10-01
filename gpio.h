/* General purpose input/output peripheral RM0008 p194*/
#ifndef GPIO_HEADER
#define GPIO_HEADER

#include <stdint.h>

/* Start address of GPIO register for banks A to E. */
#define GPIO(bank) ((struct gpio *) (0x40010800 + 0x400 * (bank - 'A')))

/* gpio peripheral register map */
struct gpio {
  volatile uint32_t crl, crh, idr, odr, bsrr, brr, lckr;
};

/* GPIO configuration low/high registers (crl/crh) */
#define GPIO_CR_MODE_BIT(pin) ((uint32_t)((pin % 8) * 4))
enum { /* GPIO configuration reisters MODE flags */
  GPIO_CR_MODE_INPUT,
  GPIO_CR_MODE_OUTPUT_10MHZ,
  GPIO_CR_MODE_OUTPUT_2MHZ,
  GPIO_CR_MODE_OUTPUT_50MHZ,
};

#define GPIO_CR_CNF_BIT(pin)  ((uint32_t)(GPIO_CR_MODE_BIT(pin) + 2))
enum { /* GPIO configuration registers CNF output flags */
  GPIO_CR_CNF_OUTPUT_PP,
  GPIO_CR_CNF_OUTPUT_OD,
  GPIO_CR_CNF_OUTPUT_AFPP,
  GPIO_CR_CNF_OUTPUT_AFOD
};
enum { /* GPIO configuration registers CNF input flags */
  GPIO_CR_CNF_INPUT_ANALOG,
  GPIO_CR_CNF_INPUT_FLOAT,
  GPIO_CR_CNF_INPUT_PUPD,
};

/* GPIO bit set/reset registers (bsrr) */
#define GPIO_BSRR_RESET_BIT(pin) ((uint32_t)(1 << pin))
#define GPIO_BSRR_SET_BIT(pin)   ((uint32_t)((1 << 16 << pin)))

/* gpio_setup() power up bank and configure a gpio pin

   bank: GPIO bank from A to G
   pin:  pin number from 0 to 15
   mode: operating mode from GPIO_CR_MODE flags
   cnf: configuration from GPIO_CR_CNF flags

   returns handle to the gpio bank register.
 */
struct gpio *gpio_setup(char bank, unsigned pin,
			uint32_t mode, uint32_t cnf);

#endif	/* GPIO_HEADER */





