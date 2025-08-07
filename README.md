
Niloofar’s STM32 Lab
Hands-on mini-projects for the NUCLEO-F401RE to practice core MCU skills (GPIO, timers, interrupts, UART, I²C, ADC, DMA, FreeRTOS, and low-power). Each demo is small, documented, and easy to import into STM32CubeIDE.

fw/UART-Printf - UART Printf Redirection on STM32F401RE This project demonstrates how to retarget the standard printf() function in C to transmit debug messages over UART using STM32 HAL functions. It is based on the STM32F401RE Nucleo board and developed using STM32CubeIDE.

Goal
Enable printf() for sending strings over UART to a serial terminal (e.g., PuTTY, Tera Term).

Features
UART2 configured for communication

Retargeted printf() via _write() function

Transmits strings to a serial terminal over USB

Uses HAL drivers (no low-level register manipulation)

Hardware
Component Connection STM32F401RE Nucleo board UART2 (TX) PA2 UART2 (RX) PA3 (optional) USB connection ST-Link USB

UART2 is connected internally to the ST-Link virtual COM port on the Nucleo board.

Configuration Summary
STM32CubeMX Settings: USART2:

Baud Rate: 115200

Word Length: 8 Bits

Stop Bits: 1

Parity: None

Mode: TX

NVIC:

No UART interrupts needed

Retarget printf() Add this to retarget.c or main.c:

c Copy Edit int _write(int file, char data, int len) { HAL_UART_Transmit(&huart2, (uint8_t)data, len, HAL_MAX_DELAY); return len; } Note: huart2 must be declared as extern if used in another file.

How to Run
Flash the firmware to the STM32 board.

Open a serial terminal (e.g., PuTTY):

Port: Check the COM port of your Nucleo ST-Link.

Baudrate: 115200

Reset the board — you should see output messages via printf().

Folder Structure
bash Copy Edit fw/UART-Printf/ ├── Core/ │ ├── Src/ │ └── Inc/ ├── .ioc # STM32CubeMX config ├── README.md # This file 📎 Example Output makefile Copy Edit System Initialized. Temperature: 24.3 C Status: OK

References
STM32 HAL Documentation

Nucleo Virtual COM Port Info
