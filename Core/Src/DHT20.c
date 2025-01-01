#include "main.h"

#define DHT20_ADDR 0x38 << 1

// Initialize the DHT20 sensor
int DHT20_Init(void) {
    uint8_t status;
    uint8_t status_cmd = 0x71;

    // Delay for power-on stabilization
    HAL_Delay(100);

    // Read status register
    if (HAL_I2C_Master_Transmit(&hi2c1, DHT20_ADDR, &status_cmd, 1, HAL_MAX_DELAY) != HAL_OK) return 0;
    if (HAL_I2C_Master_Receive(&hi2c1, DHT20_ADDR, &status, 1, HAL_MAX_DELAY) != HAL_OK) return 0;

    // Check if sensor is calibrated
    if ((status & 0x08) == 0) return 0;
    return 1; // Return 1 if no issues
}

float DHT20_Humidity(void){
    uint8_t cmd[3] = {0xAC, 0x33, 0x00};
    uint8_t data[7]; // 6 data bytes + 1 CRC byte

    // Send measurement command
    if (HAL_I2C_Master_Transmit(&hi2c1, DHT20_ADDR, cmd, 3, HAL_MAX_DELAY) != HAL_OK) return 0.0;
    HAL_Delay(80); // Wait for measurement to complete

    // Receive measurement data
    if (HAL_I2C_Master_Receive(&hi2c1, DHT20_ADDR, data, 7, HAL_MAX_DELAY) != HAL_OK) return 0.0;

    // Convert raw data to temperature and humidity
    uint32_t raw_humidity = ((uint32_t)data[1] << 12) | ((uint32_t)data[2] << 4) | ((data[3] >> 4) & 0x0F);
    float humidity = ((float)raw_humidity / (1 << 20)) * 100.0f;
    return humidity;
}
