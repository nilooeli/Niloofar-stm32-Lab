#include "uart.h"
#include "usart.h"
#include "stm32f4xx_hal.h"

void Uart_Init(void)
{
	// Call CubeMX-generated init
	MX_USART2_UART_Init();
}

void Uart_SendString(const char *s)
{
	// Transmit until NULL
	while(*s)
	{
		HAL_UART_Transmit(&huart2, (uint8_t*)s, 1, HAL_MAX_DELAY);
		s++;
	}
}

#include <stdio.h>

int _write(int file, char *data, int len)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)data, len, HAL_MAX_DELAY);
	return len;
}
