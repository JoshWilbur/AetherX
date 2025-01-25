#include "main.h"

int Poll_Button1(void){
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_4)){
		return 1;
	}
	return 0;
}

int Poll_Button2(void){
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5)){
		return 1;
	}
	return 0;
}
