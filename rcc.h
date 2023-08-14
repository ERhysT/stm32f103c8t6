/* Reset and clock control register map RM0008 8.3.13 p156 */
#ifndef RCC_HEADER
#define RCC_HEADER

#include <stdint.h>

/* RCC - real time clock address */
#define RCC ((struct rcc *) 0x40021000)

/* Reset and clock control register map */
struct rcc {
  volatile uint32_t cr, cfgr, cir, apb2rstr, abp1rstr,
    ahbenr, apb2enr, apb1enr, bdcr, csr, ahbstr, cfgr2;
};

enum {	/* advanced peripheral bus 2 reset register */
  RCC_APB2RSTR_AFIORST, RCC_APB2RSTR_IOPARST=2, RCC_APB2RSTR_IOPBRST,
  RCC_APB2RSTR_IOPCRST, RCC_APB2RSTR_IOPDRST, RCC_APB2RSTR_IOPERST,
  RCC_APB2RSTR_ADC1RST=9, RCC_APB2RSTR_ADC2RST, RCC_APB2RSTR_TIM1RST,
  RCC_APB2RSTR_SPI1RST, RCC_APB2RSTR_USART1RST=14
};

enum {     /* advanced peripheral bus 2 enable resister */
 RCC_APB2ENR_AFIOEN, RCC_APB2ENR_IOPAEN=2, RCC_APB2ENR_IOPBEN,
 RCC_APB2ENR_IOPCEN,RCC_APB2ENR_IOPDEN, RCC_APB2ENR_IOPEEN,
 RCC_APB2ENR_ADC1EN=9, RCC_APB2ENR_ADC2EN, RCC_APB2ENR_TIM1EN,
 RCC_APB2ENR_SPI1EN, RCC_APB2ENR_USART1EN=14
};
/* IOPXEN() Enable register bit for a IO pins bank A to E  */
#define RCC_APB2ENR_IOPXEN(X) (RCC_APB2ENR_IOPAEN + X - 'A')

#endif	/* RCC_HEADER */


  
