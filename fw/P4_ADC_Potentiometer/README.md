P4 – ADC->PWM with Potentiometer (STM32F401RE)
Adjust the on-board LED brightness with a potentiometer: ADC reads the pot → maps to PWM duty → LED fades.

Overview
MCU/Board: NUCLEO-F401RE

Feature set: ADC1 single conversion, TIM2 PWM (CH1), GPIO

Goal: Turn the pot to change LED brightness smoothly from 0–100%.

Hardware
Signal	Pin (NUCLEO-F401RE)	Notes
Pot wiper (Vout)	PA0 (ADC1_IN0)	Analog input (0–3.3 V)
Pot end 1	3V3	
Pot end 2	GND	
LED (LD2) PWM	PA5 (TIM2_CH1)	On-board LED with AF1 (TIM2)

If you used different pins, update them in CubeMX and code.

Repo Layout
kotlin
Copy
Edit
fw/
  P4-ADC-PWM-Potentiometer/
    Core/
    Drivers/
    Inc/
    Src/
    P4-ADC-PWM-Potentiometer.ioc
    README.md  <-- this file
CubeMX Configuration (key points)
RCC/Clock

HSI or HSE → System Clock 84 MHz (typical F4 config). Any stable clock works.

GPIO

PA0: Mode = Analog (no pull)

PA5: Mode = Alternate Function → AF1 (TIM2_CH1)

TIM2

Enable PWM Generation CH1

Pick a user-friendly PWM frequency (e.g. 1 kHz):

PSC and ARR such that F_pwm = 84 MHz / ((PSC+1)*(ARR+1)) ≈ 1000 Hz

Example: PSC = 83, ARR = 999 → 84 MHz / (84 * 1000) = 1000 Hz

Start PWM on TIM2_CH1

ADC1

Mode: Single Conversion, Continuous Conversion: Enabled

Channel: IN0 (PA0)

Sampling Time: 480 cycles (stable reading for pots)

Data alignment: Right

Enable DMA (optional) or use polling.

Firmware Logic (tl;dr)
Start PWM: HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);

Start ADC: HAL_ADC_Start(&hadc1); (or with DMA)

Loop:

Poll (or wait DMA): raw = HAL_ADC_GetValue(&hadc1); // 12-bit: 0–4095

Map to duty and write CCR:

c
Copy
Edit
// assuming ARR = 999
uint32_t duty = (raw * (htim2.Init.Period + 1)) / 4096; // 0..1000
__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, duty);
Optional: print raw/duty via UART for debugging.

Build & Flash
Open the .ioc in STM32CubeIDE → Generate Code.

Build (Ctrl+B).

Connect NUCLEO and Run/Debug.

Turn the potentiometer and watch LED brightness change.

Testing Checklist
LED fully off near 0 V on PA0, fully bright near 3.3 V.

UART (optional): periodically print raw and duty.

No visible flicker at ~1 kHz; if you see flicker, increase PWM frequency.

Troubleshooting
LED stuck ON:

PA5 must be AF1 (TIM2_CH1), not plain GPIO Output.

Ensure PWM actually started and CCR updates (watch in debugger).

No ADC change:

PA0 must be Analog mode, no pull; pot wired 3V3–GND with wiper to PA0.

Use long sampling time (e.g., 480 cycles).

If using polling, call HAL_ADC_PollForConversion() before GetValue().

Duty range too small/large:

Recheck mapping formula uses ARR+1 and 12-bit divisor 4096.

Verify your actual ARR value.

Noise/jitter:

Add small averaging (e.g., average 8–16 samples) or enable ADC oversampling (if available).

Keep pot wires short; add 0.1 µF from wiper to GND if needed.

Parameters You Can Tune
PWM frequency: 500 Hz–2 kHz looks smooth for LEDs.

ADC sampling time: 144–480 cycles; higher = stabler.

Update rate: throttle updates to ~1–5 ms if UART printing makes it sluggish.

Tag & Version
Git tag for this checkpoint: P4-ADC-PWM-Potentiometer
Push it if you haven’t:

bash
Copy
Edit
git tag -a P4-ADC-PWM-Potentiometer -m "P4: ADC->PWM with Pot"
git push origin P4-ADC-PWM-Potentiometer