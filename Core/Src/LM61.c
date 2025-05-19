#include "main.h"

// Function for polling the LM61 temperature sensor
int LM61_Read(void){
	// Set channel to ADC1_CH13 (PC3)
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_13;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) Error_Handler();

	int LM61_raw = -1;
	HAL_ADC_Start(&hadc1); // Begin ADC conversion
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	LM61_raw = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1); // End ADC conversion
	return LM61_raw;
}

// Function to return temperature
float LM61_Temp(int unit){
	int LM61_raw = LM61_Read();
	float v_adc = ((float)LM61_raw / 4095.0f) * ADC_VRef;
	float temp_C = (v_adc - 0.6) / 0.01f;

	if (unit == 0){ // Return temp in Celsius
		return temp_C;
	}else if (unit == 1){ // Return temp in Fahrenheit
		return (temp_C * 1.8f) + 32;
	}
	return -1;
}
