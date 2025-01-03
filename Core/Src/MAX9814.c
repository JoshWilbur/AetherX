#include "main.h"

// Function for polling the MAX9814 microphone
int MAX9814_Read(void){
	// Set channel to ADC1_CH14 (PC4)
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_14;
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
