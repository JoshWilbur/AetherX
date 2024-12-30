#include "main.h"

// Function for polling the LM61 temperature sensor
int LM61_read(void){
	int LM61_raw = -1;
	HAL_ADC_Start(&hadc1); // Begin ADC conversion
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	LM61_raw = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1); // End ADC conversion
	return LM61_raw;
}

// Function to return temperature
float LM61_temp(int unit){
	int LM61_raw = LM61_read();
	float v_adc = (LM61_raw / 4095.0f) * 3.3f;
	float temp_C = (v_adc - 0.6) / 0.01f;

	if (unit == 0){ // Return Celsius
		return temp_C;
	}else if (unit == 1){ // Return Fahrenheit
		return (temp_C * 1.8f) + 32;
	}else{
		return -1;
	}
}

// Function to get average temperature
float Temp_avg(int readings){
	float sum = 0;
	for (int i = 0; i < readings; i++){
		sum += LM61_temp(1);
		HAL_Delay(10);
	}
	float avg = sum / readings;
	return avg;
}
