/**
  ******************************************************************************
  * @file    delay.c
  * @brief   SysTick-based delay functions for STM32F103RCT6 @ 72MHz
  ******************************************************************************
  */

#include "delay.h"

static uint8_t  fac_us = 0;   /* us delay multiplier */
static uint16_t fac_ms = 0;   /* ms delay multiplier */

/**
  * @brief  Initialize delay functions using SysTick timer.
  *         Must be called once before using delay_us() or delay_ms().
  *         Assumes SYSCLK = 72MHz (SystemCoreClock = 72000000).
  * @param  None
  * @retval None
  */
void delay_init(void)
{
    /* Use external clock: SysTick clock = HCLK/8 = 9MHz */
    SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;
    fac_us = SystemCoreClock / 8000000;  /* 9 ticks per us */
    fac_ms = (uint16_t)fac_us * 1000;   /* 9000 ticks per ms */
}

/**
  * @brief  Delay for the given number of microseconds.
  * @param  nus: number of microseconds to wait (max ~1864 us before overflow)
  * @retval None
  */
void delay_us(uint32_t nus)
{
    uint32_t temp;
    SysTick->LOAD = nus * fac_us;
    SysTick->VAL  = 0x00;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    do
    {
        temp = SysTick->CTRL;
    } while ((temp & SysTick_CTRL_ENABLE_Msk) && !(temp & SysTick_CTRL_COUNTFLAG_Msk));
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL = 0x00;
}

/**
  * @brief  Delay for the given number of milliseconds.
  * @param  nms: number of milliseconds to wait (max ~1864 ms before overflow)
  * @retval None
  */
void delay_ms(uint16_t nms)
{
    uint32_t temp;
    SysTick->LOAD = (uint32_t)nms * fac_ms;
    SysTick->VAL  = 0x00;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    do
    {
        temp = SysTick->CTRL;
    } while ((temp & SysTick_CTRL_ENABLE_Msk) && !(temp & SysTick_CTRL_COUNTFLAG_Msk));
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL = 0x00;
}
