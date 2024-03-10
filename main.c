#include <stddef.h>

#include "rcc.h"
#include "gpio.h"
#include "syst.h"
#include "usart.h"
#include "main.h"

#include <stdio.h>

#define LEDPIN 13		/* PC13 */

void toggle_led(void)
{
  static uint32_t timer = 0;
  static bool on = true;
  static struct gpio *gpioc = NULL;

  if (NULL == gpioc)
    gpioc = gpio_setup('C', LEDPIN,
		       GPIO_CR_MODE_OUTPUT_10MHZ,
		       GPIO_CR_CNF_OUTPUT_OD);

  if ( syst_timer_expired(&timer, 1000, systick) ) {
    if (on) {
      gpioc->bsrr = GPIO_BSRR_RESET_BIT(LEDPIN);
    } else {
      gpioc->bsrr = GPIO_BSRR_SET_BIT(LEDPIN);
    }

    on ^= true;
  }
}

void write_usart(void)
{
  static unsigned baud = 9600;
  static uint32_t timer = 0;
  static char welcome_msg[] = "Starting ERTOS...\r\n";
  static struct usart *usart = NULL;

  if ( NULL == usart) {
    usart = usart_setup(baud);
    puts(welcome_msg);
  }

  // wait for input
  if ( syst_timer_expired(&timer, 1000, systick) ) {

    printf("Data present? [%d]\r\n", usart->sr & (1<<UART_SR_RXNE));
    if ( usart->sr & (1<<UART_SR_RXNE) ) {
      printf("Read '%c'\r\n", 0xFF & usart->dr);
    }

  }
}

void read_adc(void)
{
  return;
}

int main(void) {

  /* millisecond timer */
  struct syst *syst = SYST;
  syst_init(syst, 1000);

  /* setup tasks */
  size_t n = 0;
  void (*tasks[16])(void);
  tasks[0] = toggle_led;
  tasks[1] = write_usart;
  tasks[2] = NULL;
  
  /* process tasks */
  while(true)
    if (NULL == tasks[n])
      n = 0;
    else
      tasks[n++]();

  return 0; 
}
