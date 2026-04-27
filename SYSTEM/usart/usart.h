#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"
#include <stdio.h>

/* USART1 is on PA9 (TX) and PA10 (RX) */
#define USART_BAUDRATE    115200

void usart1_init(uint32_t baudrate);
void usart1_send_char(char c);
void usart1_send_string(const char *str);

/* Redirect printf to USART1 */
int fputc(int ch, FILE *f);

#endif /* __USART_H */
