#include "pwm_fade.h"
#include "tim.h"
extern TIM_HandleTypeDef htim2;

void PWM_Fade_Init(void)
{
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
}

void PWM_FadeLED_once(void)
{
	// Ramp Up
	for (uint16_t duty = 0; duty<= 999; duty += 10)
	{
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, duty);
		HAL_Delay(10);
	}
	// Ramp Down
	for (uint16_t duty = 999; duty < 1000; duty -= 10)
	{
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, duty);
		HAL_Delay(10);
	}
	// Make sure we end at 0
   __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);
}
