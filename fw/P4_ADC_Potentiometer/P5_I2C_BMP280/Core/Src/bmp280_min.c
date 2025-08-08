#include "bmp280_min.h"
#include "i2c.h"

static HAL_StatusTypeDef rd(I2C_HandleTypeDef *h, uint8_t a7, uint8_t reg, uint8_t *buf, uint16_t n)
{
	// Read an amount of data in blocking mode from a specific memory address
	return HAL_I2C_Mem_Read(h, I2C_ADDR7_TO_HAL(a7), reg, I2C_MEMADD_SIZE_8BIT, buf, n, HAL_MAX_DELAY);
}

static HAL_StatusTypeDef wr(I2C_HandleTypeDef *h, uint8_t a7, uint8_t reg, uint8_t val)
{
	// Write an amount of data in blocking mode to a specific memory address
    return HAL_I2C_Mem_Write(h, I2C_ADDR7_TO_HAL(a7), reg, I2C_MEMADD_SIZE_8BIT, &val, 1, HAL_MAX_DELAY);
}

// Find the sensor and read its ID
uint8_t BMP280_Probe(I2C_HandleTypeDef *hi2c, uint8_t *addr_out, uint8_t *id_out)
{
    uint8_t id;
    for (uint8_t a7 = 0x76; a7 <= 0x77; a7++)
    {
        if (rd(hi2c, a7, BMP280_REG_ID, &id, 1) == HAL_OK)
        {
            *addr_out = a7;
            *id_out = id;      // expect 0x58 for BMP280
            return 1;
        }
    }
    return 0;
}

// Turns the sensor on with basic settings
HAL_StatusTypeDef BMP280_StartNormal(I2C_HandleTypeDef *hi2c, uint8_t addr7)
{
    // osrs_t = x1 (001), osrs_p = x1 (001), mode = normal (11) => 0b001_001_11 = 0x27
    return wr(hi2c, addr7, BMP280_REG_CTRL_MEAS, 0x27);
}

// Grabs the raw pressure and temperature readings
HAL_StatusTypeDef BMP280_ReadRaw(I2C_HandleTypeDef *hi2c, uint8_t addr7,
                                 uint32_t *raw_press, uint32_t *raw_temp)
{
    uint8_t buf[6];
    if (rd(hi2c, addr7, BMP280_REG_PRESS_MSB, buf, 6) != HAL_OK) return HAL_ERROR;

    uint32_t p = ((uint32_t)buf[0] << 12) | ((uint32_t)buf[1] << 4) | (buf[2] >> 4);
    uint32_t t = ((uint32_t)buf[3] << 12) | ((uint32_t)buf[4] << 4) | (buf[5] >> 4);
    *raw_press = p;
    *raw_temp  = t;
    return HAL_OK;
}
