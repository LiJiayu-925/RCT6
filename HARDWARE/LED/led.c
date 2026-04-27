/**
  ******************************************************************************
  * @file    led.c
  * @brief   LED driver for STM32F103RCT6 minimum system board
  *          LED0 -> PA8  (active low)
  *          LED1 -> PD2  (active low)
  ******************************************************************************
  */

#include "led.h"

/**
  * @brief  Initialize GPIO pins for LED0 (PA8) and LED1 (PD2).
  *         Both pins configured as output push-pull, 50MHz.
  * @param  None
  * @retval None
  */
void led_init(void)
{
    /* Enable GPIOA and GPIOD clocks */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;  /* GPIOA clock enable */
    RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;  /* GPIOD clock enable */

    /* Configure PA8 as output push-pull, 50MHz */
    /* CRH bits [3:0] control pin 8: MODE8[1:0] + CNF8[1:0] */
    GPIOA->CRH &= ~(0x0FUL << 0);   /* clear MODE8 and CNF8 */
    GPIOA->CRH |=  (0x03UL << 0);   /* MODE8 = 11 (50MHz output), CNF8 = 00 (push-pull) */

    /* Configure PD2 as output push-pull, 50MHz */
    /* CRL bits [11:8] control pin 2: MODE2[1:0] + CNF2[1:0] */
    GPIOD->CRL &= ~(0x0FUL << 8);   /* clear MODE2 and CNF2 */
    GPIOD->CRL |=  (0x03UL << 8);   /* MODE2 = 11 (50MHz output), CNF2 = 00 (push-pull) */

    /* Turn off both LEDs initially (pins high = LED off for active-low) */
    LED0_OFF();
    LED1_OFF();
}
