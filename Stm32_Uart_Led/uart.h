#ifndef  __UART_H
#define  __UART_H


#include "stm32f4xx_hal.h"                 // Device header
#include <stdio.h>

//void USART2_Init(void);
void test_setup(void);
int USART_write(int ch);
int USART_read(void);


#endif