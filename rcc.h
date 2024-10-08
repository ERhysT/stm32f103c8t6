/* Reset and clock control register map RM0008 8.3.13 p156 */
#ifndef RCC_HEADER
#define RCC_HEADER

#include <stdint.h>
#include <assert.h>

/* RCC - real time clock address */
#define RCC ((struct rcc *) 0x40021000)

#define HSICLK 8000000	    /* High speed internal clock */
#define SYSCLK 8000000	    /* System clock */
#define PCLK1  8000000	    /* Peripherial clock 1 */
#define PCLK2  0	    /* Peripherial clock 2 */

/* Reset and clock control register map */
struct rcc {
  volatile uint32_t cr, cfgr, cir, apb2rstr, abp1rstr,
    ahbenr, apb2enr, apb1enr, bdcr, csr, ahbstr, cfgr2;
};

enum { 				/* clock configuration register */
  RCC_CFGR_SW, RCC_CFGR_SWS=2, RCC_CFGR_HPRE=4, RCC_CFGR_PPRE1=8,
  RCC_CFGR_PPRE2=11, RCC_CFGR_ADCPRE=14, RCC_CFGR_PLLSRC=16,
  RCC_CFGR_PLLXTPRE, RCC_CFGR_PLLMUL=18, RCC_CFGR_USBPRE=22,
  RCC_CFGR_MCO=24 
};

enum {	/* advanced peripheral bus 2 reset register */
  RCC_APB2RSTR_AFIORST, RCC_APB2RSTR_IOPARST=2, RCC_APB2RSTR_IOPBRST,
  RCC_APB2RSTR_IOPCRST, RCC_APB2RSTR_IOPDRST, RCC_APB2RSTR_IOPERST,
  RCC_APB2RSTR_ADC1RST=9, RCC_APB2RSTR_ADC2RST, RCC_APB2RSTR_TIM1RST,
  RCC_APB2RSTR_SPI1RST, RCC_APB2RSTR_USART1RST=14
};

enum {     /* advanced peripheral bus 2 enable resister */
 RCC_APB2ENR_AFIOEN, RCC_APB2ENR_IOPAEN=2, RCC_APB2ENR_IOPBEN,
 RCC_APB2ENR_IOPCEN, RCC_APB2ENR_IOPDEN, RCC_APB2ENR_IOPEEN,
 RCC_APB2ENR_ADC1EN=9, RCC_APB2ENR_ADC2EN, RCC_APB2ENR_TIM1EN,
 RCC_APB2ENR_SPI1EN, RCC_APB2ENR_USART1EN=14
};

enum {     /* advanced peripheral bus 1 enable resister */
 RCC_APB1ENR_TIM2EN, RCC_APB1ENR_TIM3EN, RCC_APB1ENR_TIM4EN,
 RCC_APB1ENR_TIM5EN, RCC_APB1ENR_TIM6EN, RCC_APB1ENR_TIM7EN,
 RCC_APB1ENR_TIM12EN, RCC_APB1ENR_TIM13EN, RCC_APB1ENR_TIM14EN, 
 RCC_APB1ENR_WWDEN=11, RCC_APB1ENR_SPI2EN=14, RCC_APB1ENR_SPI3XEN,
 RCC_APB1ENR_USART2EN=17, RCC_APB1ENR_USART3EN,  RCC_APB1ENR_UART4EN,
 RCC_APB1ENR_UART5EN, RCC_APB1ENR_I2C1EN,  RCC_APB1ENR_I2C2EN,
 RCC_APB1ENR_USBEN, RCC_APB1ENR_CANEN=25,  RCC_APB1ENR_BKPEN=27,
 RCC_APB1ENR_PWREN, RCC_APB1ENR_DACEN
};

/* IOPXEN() Enable register bit for a IO bank X, X can be A to E */
#define RCC_APB2ENR_IOPXEN(X) (RCC_APB2ENR_IOPAEN + X - 'A')

#endif	/* RCC_HEADER */
