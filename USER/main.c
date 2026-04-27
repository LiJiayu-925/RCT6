/**
  ******************************************************************************
  * @file    main.c
  * @brief   Main program for STM32F103RCT6 minimum system board
  *
  *  Features demonstrated:
  *    - System clock: 72MHz (HSE 8MHz + PLL x9)
  *    - LED0 (PA8) and LED1 (PD2) blinking (alternating)
  *    - USART1 @ 115200 baud sending status messages (PA9=TX, PA10=RX)
  *    - SysTick-based millisecond delay
  *
  *  Connections:
  *    LED0 -> PA8  (active low, on-board indicator)
  *    LED1 -> PD2  (active low, on-board indicator)
  *    USART1 TX -> PA9  (connect to USB-UART adapter to view messages)
  *    USART1 RX -> PA10
  ******************************************************************************
  */

#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "usart.h"
#include "sys.h"
#include <stdio.h>

int main(void)
{
    uint32_t count = 0;

    /* Configure NVIC priority group 2: 2 bits pre-emption, 2 bits sub-priority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    /* Initialize SysTick-based delay (depends on 72MHz SystemCoreClock) */
    delay_init();

    /* Initialize LEDs (PA8, PD2) */
    led_init();

    /* Initialize USART1 at 115200 baud */
    usart1_init(115200);

    /* Print startup banner */
    printf("\r\n========================================\r\n");
    printf(" STM32F103RCT6 Minimum System Demo\r\n");
    printf(" SYSCLK = 72MHz (HSE 8MHz x PLL 9)\r\n");
    printf(" LED0 -> PA8  (active low)\r\n");
    printf(" LED1 -> PD2  (active low)\r\n");
    printf("========================================\r\n\r\n");

    while (1)
    {
        /* LED0 on, LED1 off */
        LED0_ON();
        LED1_OFF();
        delay_ms(500);

        /* LED0 off, LED1 on */
        LED0_OFF();
        LED1_ON();
        delay_ms(500);

        count++;
        printf("Blink count: %lu\r\n", count);
    }
}
