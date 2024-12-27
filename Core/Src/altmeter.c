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
	MPL3115A2_write(CTRL_REG1, 0x04); // Software reset
	HAL_Delay(100);
    MPL3115A2_write(CTRL_REG1, 0x00);
    HAL_Delay(10);
    MPL3115A2_write(PT_DATA_CFG, 0x07);

    // Enable data flags in CTRL_REG1 and set OSR to 128
    MPL3115A2_write(CTRL_REG1, 0x38);
    MPL3115A2_write(CTRL_REG1, 0x39);
    HAL_Delay(512); // OSR = 128 means 512ms sampling time
}

// Function to read pressure value from device
float MPL3115A2_pressure(){
	uint8_t buffer[3];
	uint8_t status = MPL3115A2_read(STATUS_REG);
	if (status & 0x04){
		uint8_t reg = OUT_P_MSB;
		HAL_I2C_Master_Transmit(&hi2c1, MPL3115A2_ADDR, &reg, 1, HAL_MAX_DELAY);
		HAL_I2C_Master_Receive(&hi2c1, MPL3115A2_ADDR, buffer, 3, HAL_MAX_DELAY);

		// 20 bit pressure value
		uint32_t pressure_raw = (buffer[0] << 16) | (buffer[1] << 8) | buffer[2];
		pressure_raw >>= 4;
		float pressure = pressure_raw / 4.0f; // Convert to Pascal units
		return pressure;
	}
	return -1;
}

// Function to read temperature value from device
float MPL3115A2_temp(){
	uint8_t buffer[2];
	uint8_t status = MPL3115A2_read(STATUS_REG);
	if (status & 0x02){
		uint8_t reg = OUT_T_MSB;
		HAL_I2C_Master_Transmit(&hi2c1, MPL3115A2_ADDR, &reg, 1, HAL_MAX_DELAY);
		HAL_I2C_Master_Receive(&hi2c1, MPL3115A2_ADDR, buffer, 2, HAL_MAX_DELAY);

		// 12 bit temperature value
		uint16_t temp_raw = (buffer[0] << 8) | buffer[1];
		temp_raw >>= 4;
		float temp = temp_raw / 16.0f;
		return temp;
	}
	return -1;
}
