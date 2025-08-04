# P3 – TIM1 PWM LED Fade

> **Project 3:** Use TIM1’s hardware PWM to smoothly fade the on-board LED and restart the effect on push-button press.

---

## 📋 Overview

This demo shows how to configure and use TIM1 on the STM32F401RE to generate a PWM signal that drives the green LED (LD2).  
A user-button (B1 on PC13) triggers an EXTI interrupt; each press requests a one-cycle fade up and fade down of the LED brightness.

---

## 🔌 Hardware

- **Board:** Nucleo-F401RE  
- **LED (LD2):** PA5, driven by TIM2_CH1 (remapped to TIM1_CH1 in CubeMX)  
- **User Button (B1):** PC13, configured as EXTI13 (falling-edge trigger)  

---

## ⚙️ Pin Configuration

| Signal        | MCU Pin | Mode                   | Pull   |
|---------------|---------|------------------------|--------|
| LD2 (Green)   | PA5     | TIM1_CH1 (Alternate)   | N/A    |
| B1 (Blue Btn) | PC13    | External Interrupt 13  | Pull-up|

*(Ensure in your `.ioc` NVIC EXTI15_10_IRQn is enabled.)*

---

## 📁 Project Structure

fw/P3_TIM1_PWM_LED/
├─ Core/
│ ├─ Inc/
│ │ └─ main.h
│ ├─ Src/
│ │ ├─ main.c
│ │ └─ stm32f4xx_it.c
│ └─ …
├─ Drivers/
│ └─ STM32F4xx_HAL_Driver/
├─ P3_TIM1_PWM_LED.ioc
└─ README.md ← (this file)

yaml
Copy
Edit

---

## 🚀 Getting Started

1. **Open** the `P3_TIM1_PWM_LED.ioc` in STM32CubeIDE.  
2. **Generate Code** (Project → Generate Code).  
3. **Build** the project (`Project → Build All`).  
4. **Flash** to your Nucleo board (`Run → Debug` or use ST-Link).  

---

## ▶️ Usage

1. After reset, the LED is off.  
2. **Press the user-button (B1)** to request a fade:  
   - LED will ramp from off → full brightness  
   - Then ramp back down → off  
3. You may press B1 again after the sequence completes to restart.

---

## 🔍 How It Works

- **`PWM_FadeInit()`** starts TIM1 PWM on CH1.  
- **`HAL_GPIO_EXTI_Callback()`** sets a `fade_requested` flag when PC13 triggers.  
- **`main()`** loop polls that flag and calls `PWM_FadeOnce()`, which performs a single up/down duty cycle using `__HAL_TIM_SET_COMPARE()` and `HAL_Delay()`.

---

## ⚠️ Notes

- The fade routine does **not** block in an interrupt— it runs in `main()` to keep SysTick working.  
- Ensure only **one** `HAL_GPIO_EXTI_Callback()` exists in your project.

---

## 📜 License

This code is released under the MIT License. See [LICENSE](../../LICENSE) for details.