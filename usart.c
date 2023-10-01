#include <stdbool.h>

#include "rcc.h"
#include "gpio.h"
#include "usart.h"

static bool usart_tx_empty(struct usart *h);

/* usart_setup() for full duplex transmission 

   1. Clock UART1 peripherial using rcc register
   
   UART2 is clocked as shown below		    
                                                 
   SYSCLK -> AHB Prescaler -> APB2 Prescaler -> PCLK2
   8MHz     /1                /1             -> 8MHz

  2. Setup the correct gpio bank and select the correct modes for
  alternate function on tx and rx pins.

  4.Program the M bit in USART_CR1 to define the word length.

  5.Program the number of stop bits in USART_CR2.

  6. Select the desired baud rate using the USART_BRR register.

  3. Enable the USART by writing the UE bit in USART_CR1 register to 1.
*/

struct usart *usart_setup(void)
{
  //assert(PCLK1 == 8000000, "Expected PCLK1 at 8MHz")

  /* Enable bank A gpio pins in correct mode */
  struct rcc *rcc = RCC;

  rcc->apb1enr |= (1<<RCC_APB1ENR_USART2EN); 
  rcc->apb2enr |= (1<<RCC_APB2ENR_IOPAEN);
    //rcc->apb1enr |= 0x20000;           // 0b 0000 0000 0000 0010 0000 0000 0000 0000
  //rcc->apb2enr |= 0x4;

  /* tx Pin 2A Full duplex requires PP */
  struct gpio *gpio = GPIO('A');
  //gpio->crl |= 0x900;               // Set PA2 as TX pin (AF)
  gpio->crl |= (1<<8) | (1<<11); 

  struct usart *usart = USART2;
  usart->brr = (0x34<<4) | 1;




  //usart->brr  = 0xEA6;              // Setting Baudrate to 9600 @8 MHz.
  usart->cr1 |= 0x00008;            // Enable TX only
  usart->cr1 |= 0x02000;            // Enable USART module 

  /* usart->cr1 = 0; */
  /* usart->cr1 |= (1<<USART_CR1_UE);   /\* enable *\/ */
  /* usart->cr1 &= ~(1<<USART_CR1_M);   /\* 8 bit words *\/ */
  /* usart->cr2 |= (1<<USART_CR2_STOP); /\* 1 stop bit *\/ */


  /* enable transmit and recieve last so nothing happens during setup */
  /* usart->cr1 |= (1<<USART_CR1_TE); */
  //usart->cr1 |= (1<<USART_CR1_RE);

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

/* TRUE when data has been transmitted to the shift register.

   Cleared by a write to the DR register.
 */
static bool usart_tx_empty(struct usart *h)
{
  return h->sr & (1<<USART_SR_TXE);
}

