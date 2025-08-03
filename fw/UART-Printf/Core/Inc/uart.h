/* uart.h */
#ifndef __UART_H
#define __UART_H

#include <stdio.h>

/**  Initialize UART2 at 115200-8-N-1. **/
void Uart_Init(void);

/** Send a null-terminated string over UART2 **/
void Uart_SendString(const char *s);

#endif
