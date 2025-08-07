#include "pot_pwm.h"
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart2;

void PotPWM_Init(void)
{
    // Start PWM and ADC
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);
    HAL_ADC_Start(&hadc1);
}

void PotPWM_Update(void)
{
	HAL_ADC_Start(&hadc1);
	// wait for complete regular conversion
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    uint32_t raw = HAL_ADC_GetValue(&hadc1);
    uint32_t period = __HAL_TIM_GET_AUTORELOAD(&htim2);

    // capture-compare-register simple direct mapping for now
    uint32_t ccr = (raw * period) / 4095;

    // compare timer2 with the capture-compare register
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, ccr);

}
