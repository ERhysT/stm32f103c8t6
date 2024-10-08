#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "rcc.h"
#include "gpio.h"
#include "usart.h"

static bool usart_tx_empty(struct usart *h);
static inline bool usart_rx_full(struct usart *h);
static uint16_t baudtobrr(unsigned baud, unsigned f);

/** usart_setup() for full duplex transmission 9600 baud

 * Clock USART1 peripherial using rcc register
   
 USART2 is clocked as shown below		    
                                                 
 SYSCLK -> AHB Prescaler -> APB2 Prescaler -> PCLK2
 8MHz     /1                /1             -> 8MHz

 * Setup the gpio bank and the modes for alternate function on tx and
 rx pins.

 * Select the desired baud rate using the brr register, the format of
 the baud rate is in the reference manual page 798.

 * Enable the USART by writing the UE bit in USART_CR1 register to 1.

**/
struct usart *usart_setup(unsigned baud)
{
  /* assert(PCLK1 == 8000000, "Expected PCLK1 at 8MHz") */

  struct rcc *rcc = RCC;
  rcc->apb1enr |= (1<<RCC_APB1ENR_USART2EN); 

  /* Configure GPIO */
  const char bank = 'A';
  const unsigned tx = 2, rx = 3;
  gpio_setup(bank, tx, GPIO_CR_MODE_OUTPUT_10MHZ,
	     GPIO_CR_CNF_OUTPUT_AFPP);
  gpio_setup(bank, rx, GPIO_CR_MODE_INPUT,
	     GPIO_CR_CNF_INPUT_PUPD);

  /* Enable USART set baudrate and enable tx and rx */
  struct usart *usart = USART2;
  usart->brr = baudtobrr(baud, PCLK1);
  usart->cr1 = (1<<USART_CR1_TE) | (1<<USART_CR1_RE);
  usart->cr2 = 0;

  /* Enable USART last so no interupts before fully configured */
  usart->cr1 |= (1<<USART_CR1_UE);

  return usart;
}

/* write character and wait until it is transmitted to shift
   register */
void usart_write_char(struct usart *h, char c)
{
  h->dr = c & 0x1FF;
  while ( !usart_tx_empty(h) )
    ;
}

void usart_write_str(struct usart *h, const char *s, size_t len)
{
  for (const char *cur = s; *cur != '\0' && cur-s < len; cur++)
    usart_write_char(h, *cur);
}

/* read and return character from usart data register or return -1
   if there is none present. */
int usart_read_char(struct usart *h)
{
  return usart_rx_full(h) ? h->dr : -1;
}

/* TRUE when data has been transmitted to the shift register.

   Cleared by a write to the DR register.
 */
static inline bool usart_tx_empty(struct usart *h)
{
  return h->sr & (1<<USART_SR_TXE);
}

/* True if character to be read is present in dr */
static inline bool usart_rx_full(struct usart *h)
{
  return h->sr & (1<<USART_SR_RXNE);
}

/* Calulate baud rate register value from baud and clock frequency

   The USART samples at 16x the clock speed

   baud     = f / 16*USARTDIV
   USARTDIV = f / 16*baud

   e.g. for f=8MHz, baud=9600
        USARTDIV = 8MHz / 16*9600 = 52.083

   Becuase of the oversampling USARTDIV must be greater than 16.

   USART div is written to the brr register in 12.4 fixed point
   notation.
   
   mantissa = 52 => 0x34
   fraction = 0.83 * 16 = 1.33 => 1 => 0xF

   USARTDIV(12.4) = 0x341
   
   There is a bug whan the fractional part overflows, the mantissa is
   not increased, I think there must be a better way to do this.
*/
static inline uint16_t baudtobrr(unsigned baud, unsigned f)
{
  uint32_t oversampling = 16;
  uint32_t sample_rate = oversampling * baud;

  uint32_t mantissa = f / sample_rate;
  uint32_t fraction = ((((f<<5) / sample_rate)+1)>>1) ^ (mantissa<<4);
  
  return (mantissa<<4) | fraction;
}
