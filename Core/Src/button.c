#include "main.h"

int poll_button(void){
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_4)){
		return 1;
	}
	return 0;
}
