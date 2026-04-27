#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

/*
 * LED connections on STM32F103RCT6 minimum system board:
 *   LED0 -> PA8  (active low)
 *   LED1 -> PD2  (active low)
 */

/* Macros for controlling LED0 (PA8) */
#define LED0_ON()    (GPIOA->BRR  = (1UL << 8))   /* PA8 low  -> LED on  */
#define LED0_OFF()   (GPIOA->BSRR = (1UL << 8))   /* PA8 high -> LED off */
#define LED0_TOGGLE() (GPIOA->ODR ^= (1UL << 8))

/* Macros for controlling LED1 (PD2) */
#define LED1_ON()    (GPIOD->BRR  = (1UL << 2))   /* PD2 low  -> LED on  */
#define LED1_OFF()   (GPIOD->BSRR = (1UL << 2))   /* PD2 high -> LED off */
#define LED1_TOGGLE() (GPIOD->ODR ^= (1UL << 2))

void led_init(void);

#endif /* __LED_H */
