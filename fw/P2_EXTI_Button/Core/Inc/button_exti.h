#ifndef __BUTTON_EXTI_H__
#define __BUTTON_EXTI_H__

#include "main.h"

// Call this once to initialize GPIO and debounce logic
void Button_EXTI_Init(void);

// This function should be called from HAL_GPIO_EXTI_Callback
void Button_EXTI_Handler(uint16_t GPIO_Pin);

// This function should be called from HAL_TIM_PeriodElapsedCallback
void Button_Debounce_Timer_Handler(TIM_HandleTypeDef *htim);

#endif
