/**
  ******************************************************************************
  * @file    usart.c
  * @brief   USART1 driver for STM32F103RCT6
  *          PA9  -> USART1_TX
  *          PA10 -> USART1_RX
  *          Baud rate: 115200, 8N1
  ******************************************************************************
  */

#include "usart.h"

/**
  * @brief  Initialize USART1 at the given baud rate (8N1).
  * @param  baudrate: desired baud rate (e.g. 115200)
  * @retval None
  */
void usart1_init(uint32_t baudrate)
{
    uint32_t mantissa, fraction;
    uint32_t apb2_clock;
    float    usartdiv;

    /* 1. Enable clocks: GPIOA and USART1 are on APB2 */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;    /* GPIOA clock */
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;  /* USART1 clock */

    /* 2. Configure PA9 as alternate function push-pull output (TX) */
    /*    CRH bits [7:4] = pin 9 config */
    GPIOA->CRH &= ~(0x0FUL << 4);   /* clear MODE9 and CNF9 */
    GPIOA->CRH |=  (0x0BUL << 4);   /* MODE9 = 11 (50MHz), CNF9 = 10 (AF push-pull) */

    /* 3. Configure PA10 as input with pull-up (RX) */
    /*    CRH bits [11:8] = pin 10 config */
    GPIOA->CRH &= ~(0x0FUL << 8);   /* clear MODE10 and CNF10 */
    GPIOA->CRH |=  (0x08UL << 8);   /* MODE10 = 00 (input), CNF10 = 10 (input with pull-up/down) */
    GPIOA->ODR |=  (1UL << 10);     /* enable pull-up on PA10 */

    /* 4. Calculate and set baud rate */
    /*    APB2 clock = 72MHz (PCLK2 = HCLK when APB2 prescaler = 1) */
    apb2_clock = 72000000;
    usartdiv   = (float)apb2_clock / (16.0f * baudrate);
    mantissa   = (uint32_t)usartdiv;
    fraction   = (uint32_t)((usartdiv - mantissa) * 16 + 0.5f);
    if (fraction >= 16)
    {
        mantissa++;
        fraction = 0;
    }
    USART1->BRR = (uint16_t)((mantissa << 4) | (fraction & 0x0F));

    /* 5. Configure USART1: 8 data bits, no parity, 1 stop bit */
    USART1->CR1 = 0x0000;
    USART1->CR2 = 0x0000;
    USART1->CR3 = 0x0000;

    /* 6. Enable TX and RX, then enable USART */
    USART1->CR1 |= USART_CR1_TE | USART_CR1_RE;
    USART1->CR1 |= USART_CR1_UE;
}

/**
  * @brief  Send a single character via USART1.
  * @param  c: character to send
  * @retval None
  */
void usart1_send_char(char c)
{
    while (!(USART1->SR & USART_SR_TXE))
    {
    }
    USART1->DR = (uint8_t)c;
}

/**
  * @brief  Send a null-terminated string via USART1.
  * @param  str: pointer to the string
  * @retval None
  */
void usart1_send_string(const char *str)
{
    while (*str)
    {
        usart1_send_char(*str++);
    }
}

/**
  * @brief  Redirect printf to USART1 (retarget fputc for Keil MicroLIB).
  *         Enable "Use MicroLIB" in Keil project Target options.
  * @param  ch: character to output
  * @param  f:  file pointer (unused)
  * @retval character sent
  */
int fputc(int ch, FILE *f)
{
    usart1_send_char((char)ch);
    return ch;
}
