// This file reads and interprets values from the MPL3115A2 sensor from Adafruit
// Datasheet: https://cdn-shop.adafruit.com/datasheets/1893_datasheet.pdf
#include "main.h"

#define MPL3115A2_ADDR 0x60 << 1 // Shift for 7 bit address
#define CTRL_REG1 0x26
#define PT_DATA_CFG 0x13
#define OUT_P_MSB 0x01
#define OUT_T_MSB 0x04
#define STATUS_REG 0x00

// Function to handle writing to device
void MPL3115A2_write(uint8_t reg, uint8_t value){
	uint8_t write_data[2] = {reg, value};
    HAL_I2C_Master_Transmit(&hi2c1, MPL3115A2_ADDR, write_data, 2, HAL_MAX_DELAY);
}

// Function to handle reading registers
uint8_t MPL3115A2_read(uint8_t reg){
	uint8_t value; // 8 bit integer for write back data
	HAL_I2C_Master_Transmit(&hi2c1, MPL3115A2_ADDR, &reg, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c1, MPL3115A2_ADDR, &value, 1, HAL_MAX_DELAY);
	return value;
}

// Initialization function for the MPL3115A2
void MPL3115A2_init(){
    // Setup as described on page 10 of the data sheet
	MPL3115A2_write(CTRL_REG1, 0x39); // Set to barometer mode
	MPL3115A2_write(PT_DATA_CFG, 0x07);
	MPL3115A2_write(CTRL_REG1, 0xB9);
}

// Function to read pressure value from device
float MPL3115A2_pressure(){
	uint8_t buffer[3];
	uint8_t status = MPL3115A2_read(STATUS_REG);
	if (status & 0x08){
		HAL_I2C_Master_Transmit(&hi2c1, MPL3115A2_ADDR, OUT_P_MSB, 1, HAL_MAX_DELAY);
		HAL_I2C_Master_Receive(&hi2c1, MPL3115A2_ADDR, buffer, 3, HAL_MAX_DELAY);

		// 20 bit pressure value
		uint32_t pressure = ((uint32_t)buffer[0] << 16) | ((uint32_t)buffer[1] << 8) | buffer[2];
		pressure >>= 4;
		pressure /= 4.0f; // Convert to Pascal units
		return pressure;
	}
}

// Function to read temperature value from device
float MPL3115A2_temp(){
	uint8_t buffer[2];
	uint8_t status = MPL3115A2_read(STATUS_REG);
	if (status & 0x08){
		HAL_I2C_Master_Transmit(&hi2c1, MPL3115A2_ADDR, OUT_T_MSB, 1, HAL_MAX_DELAY);
		HAL_I2C_Master_Receive(&hi2c1, MPL3115A2_ADDR, buffer, 2, HAL_MAX_DELAY);

		// 12 bit temperature value
		uint16_t temp = ((uint16_t)buffer[0] << 8) | buffer[1];
		temp >>= 4;
		temp /= 16.0f; // Convert to Celsius units
		return temp;
	}
}

