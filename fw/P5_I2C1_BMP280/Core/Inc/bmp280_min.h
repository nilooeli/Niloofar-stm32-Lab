#pragma once
#include "main.h"
#include "i2c.h"

#define BMP280_REG_ID        0xD0
#define BMP280_REG_RESET     0xE0
#define BMP280_REG_STATUS    0xF3
#define BMP280_REG_CTRL_MEAS 0xF4
#define BMP280_REG_CONFIG    0xF5
#define BMP280_REG_PRESS_MSB 0xF7  // F7..F9 pressure, FA..FC temp

// HAL expects 7-bit address << 1
#define I2C_ADDR7_TO_HALL(a)  ((a) << 1)

uint8_t BMP280_Probe(I2C_HandleTypeDef *hi2c, uint8_t *addr_out, uint8_t *id_out);
HAL_StatusTypeDef BMP280_StartNormal(I2C_HandleTypeDef *hi2c, uint8_t addr7);
HAL_StatusTypeDef BMP280_ReadRaw(I2C_HandleTypeDef *hi2c, uint8_t addr7,
								uint32_t *raw_press, uint32_t *raw_temp);
