## STM32 Lab Projects (STM32F401RE)

This repository contains a series of embedded systems projects developed on the **STM32F401RE Nucleo** board using **STM32CubeIDE** and the **HAL** driver framework. The goal is to build up embedded programming skills through progressive hands-on labs, ranging from basic GPIO to advanced DMA, FreeRTOS, and low-power applications.

---

## 📚 Overview

Each project demonstrates a specific STM32 feature or embedded design pattern. They are structured in folders under `fw/` (firmware), named `P0`, `P1`, etc., to reflect the order and complexity of development.

---

## 📋 Project Task Table

| Project | Feature                             | Goal                       | Done When                                    |
|---------|-------------------------------------|----------------------------|-----------------------------|
| **P0**  | GPIO + Clock Init                   | Blink LED @ 1Hz            | LED blinks reliably                          |
| **P1**  | UART2 Printf                        | PC serial I/O              | "Hello, STM32" prints in terminal            |
| **P2**  | EXTI Pushbutton + Debounce         | Interrupt + debounce       | Button press toggles LED once                |
| **P3**  | TIM1 PWM -> LED                     | Hardware PWM               | LED fades smoothly                           |
| **P4**  | ADC1 Potentiometer -> PWM          | Analog read + LED control  | Pot controls brightness                      |
| **P5**  | I2C BMP280 (WHOAMI + raw)          | Basic I2C                  | IDs and raw values print                     |
| **P6**  | BMP280 Calibration                 | Engineering units          | Temp/Pressure values look stable             |
| **P7**  | UART Streaming                     | Structured CSV/JSON logs   | Log 60+ seconds without drop                 |
| **P8**  | UART TX via DMA                    | Non-blocking comms         | System stays responsive during logging       |
| **P9**  | Data Logging (Flash/SD)            | On-device storage          | Records survive power cycle                  |
| **P10** | UART CLI                           | Runtime control            | You can change settings live                 |
| **P11** | FreeRTOS Task Split                | Concurrency                | No starvation across tasks                   |
| **P12** | Low Power + RTC                    | Energy awareness           | System sleeps + wakes reliably               |
| **P13** | I2C DMA                            | Offload sensor reads       | Reads use minimal CPU                        |
| **P14** | Watchdog + Fault Logging           | Self-recovery              | System resets + logs fault cause             |
| **P15** | Integrated Demo App                | Interview showcase         | Full demo script runs end-to-end             |

---

## 🧰 Tools & Environment

- **Board**: STM32F401RE Nucleo
- **IDE**: STM32CubeIDE
- **Framework**: STM32 HAL (Hardware Abstraction Layer)
- **Interface**: ST-Link USB (UART via virtual COM)
- **Terminals**: PuTTY / Tera Term for serial output

---

## 📁 Folder Structure

Niloofar-stm32-Lab/
├── fw/
│ ├── P0_BlinkLED/
│ ├── UART-Printf/
│ ├── P2_EXTI_Button/
│ └── ...
├── images/
├── .gitignore
└── README.md ← you are here

yaml
Copy
Edit

---

## 🏁 Getting Started

To run any project:

1. Clone the repository:
   ```bash
   git clone https://github.com/nilooeli/Niloofar-stm32-Lab.git
Open the .ioc file of the project in STM32CubeIDE.

Build and flash to the STM32F401RE board via ST-Link.

Monitor UART output if applicable (115200 8N1 via COM port).

💡 Future Plans
 Add project diagrams for each task

 Add build instructions and test results per folder

 Include logic analyzer screenshots for verification

 Write blog or documentation pages per milestone

🙏 Acknowledgments
Special thanks to STMicroelectronics, CubeIDE team, and the embedded systems community for resources and tools.