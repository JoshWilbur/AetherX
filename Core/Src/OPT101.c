#include "main.h"

// Function to read the OPT101 sensor
int OPT101_Read(void){
	// Set channel to ADC1_CH10 (PC0)
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_10;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) Error_Handler();

	int OPT101_raw = -1;
	HAL_ADC_Start(&hadc1); // Begin ADC conversion
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    OPT101_raw = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1); // End ADC conversion
	return OPT101_raw;
}

// Function to output OPT101 readings in Lux
float OPT101_Lux(void){
	int OPT101_raw = OPT101_Read();
	float OPT101_volt = ((float)OPT101_raw / 4095.0) * ADC_VRef;
	const float sensitivity = 0.00045; // V per lux

	float lux = OPT101_volt / sensitivity;
	return lux;
}

float OPT101_Avg(float *readings, int len){
	float sum = 0;
	for (int i = 0; i < len; i++){
		sum += readings[i];
	}
	float avg = sum / (float)len;
	return avg;
}
