/* Universal synchronous asynchronous receiver transmitter */
#ifndef GAURD_USART_H
#define GAURD_USART_H

#define USART_BAUD 4800
#define USART_WORD_LENGTH 8

#define USART1 ((struct usart *)0x40013800)
#define USART2 ((struct usart *)0x40004400)
#define USART3 ((struct usart *)0x40004800)

struct usart {
  volatile uint32_t sr, dr, brr, cr1, cr2, cr3, gtpr;
};

enum {				/* status register */
  UART_SR_PE, UART_SR_FE, UART_SR_NE, UART_SR_ORE, UART_SR_IDLE,
  UART_SR_RXNE, UART_SR_TC, UART_SR_TXE, UART_SR_LBD, UART_SR_CTS
};

enum {				/* control register 1 */
  USART_CR1_SBK, USART_CR1_RWU, USART_CR1_RE, USART_CR1_TE,
  USART_CR1_IDLEIE, USART_CR1_RXNEIE, USART_CR1_TCIE,
  USART_CR1_TXEIE, USART_CR1_PEIE, USART_CR1_PS, USART_CR1_PCE,
  USART_CR1_WAKE, USART_CR1_M, USART_CR1_UE
};

enum {				/* control register 2 */
  USART_CR2_ADD, USART_CR2_LBDL=5, USART_CR2_LBDIE, USART_CR2_LBCL=8,
  USART_CR2_CPHA, USART_CR2_CPOL, USART_CR2_CLKEN, USART_CR2_STOP,
  USART_CR2_LINEN=14
};

enum {				/* Baud rate register */
  USART_BRR_DIV_FRACTION, USART_BRR_DIV_MANTISSA = 4
};

enum { 				/* Status register */
  USART_SR_PE, USART_SR_FE, USART_SR_NE, USART_SR_ORE, USART_SR_IDLE,
  USART_SR_RXNE, USART_SR_TC, USART_SR_TXE, USART_SR_LBD, USART_SR_CTS
};

/* setup usart2 for full duplex transmission */
struct usart *usart_setup(unsigned baud);

/* write a character to usart */
void usart_write_char(struct usart *h, char c);

#endif /* GAURD_USART_H */
