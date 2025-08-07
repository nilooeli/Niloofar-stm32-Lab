# P2_EXTI_Button

## 🔍 Goal
Use external interrupt (EXTI) and a debounce timer to toggle an LED **once per valid button press**, even with mechanical bounce.

---

## ⚙️ Features
- EXTI line triggered by pushbutton (PC13)
- Timer-based debounce using TIM1 (~20ms)
- LED toggles only once per press (PA5)
- Code modularized into `button_exti.h/.c`

---

## 🔩 Hardware Setup

| Component   | Pin     | Function             |
|-------------|---------|----------------------|
| Pushbutton  | PC13    | EXTI input           |
| LED         | PA5     | Output (toggle LED)  |

> Using STM32F401RE Nucleo board (or similar)

---

## 🛠️ STM32CubeMX Configuration

### GPIO
- PC13 → GPIO_EXTI13, Pull-up enabled
- PA5  → Output Push-Pull, No pull

### NVIC
- Enable `EXTI15_10_IRQn`
- Enable `TIM1 Update Interrupt`

### TIM1 Settings
- Clock Source: Internal Clock
- Prescaler: 8399
- Counter Period: 1999  
→ Yields ~20ms delay on 84 MHz clock

---

## 📄 Code Structure

Core/
├── Inc/
│ ├── button_exti.h # Debounce + EXTI logic header
├── Src/
│ ├── button_exti.c # Debounce + EXTI implementation
├── main.c # Calls EXTI handlers from HAL callbacks

cpp
Copy
Edit

### Usage in `main.c`
```c
#include "button_exti.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    Button_EXTI_Handler(GPIO_Pin);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    Button_Debounce_Timer_Handler(htim);
}
✅ Result
LED toggles once per press

No multiple toggles from button bounce

Button presses feel reliable and clean