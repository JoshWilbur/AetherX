#include "main.h"

volatile int screen_flag = 0;
volatile int LED_flag = 1;

// USED FOR TESTING ONLY
int Poll_Button1(void){
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_4)){
		return 1;
	}
	return 0;
}

// USED FOR TESTING ONLY
int Poll_Button2(void){
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5)){
		return 1;
	}
	return 0;
}

// GPIO EXTI callback handler for direction switching
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	// Switch 1
    if(GPIO_Pin == GPIO_PIN_4){ // Check if PC4 is the interrupt pin
    	screen_flag = !screen_flag;
    }
    // Switch 2
    if(GPIO_Pin == GPIO_PIN_5){ // Check if PC5 is the interrupt pin
    	LED_flag = !LED_flag;
    }
}
