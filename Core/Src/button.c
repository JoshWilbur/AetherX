#include "main.h"

volatile int screen_flag = 0;
volatile int LED_flag = 0;
volatile int read_flag = 1;

volatile int button_hist[4] = {0}; // Stores history of last 4 button presses
volatile int button_flag = 0;
volatile int i = 0;
int standby_flag = 0;

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

void Button_History(void){
    static uint32_t last_press_time = 0;  // Track time of last press
    uint32_t current_time = HAL_GetTick();  // Get current time

    // Reset sequence if time 4 seconds exceeded
    if (current_time - last_press_time > 4000) i = 0;
    last_press_time = current_time;

    // Store the button press
    button_hist[i++] = button_flag;
    button_flag = 0;


    if (i > 3) {
        if (button_hist[0] == 4 && button_hist[1] == 5 && button_hist[2] == 4 && button_hist[3] == 5) {
            standby_flag = 1;
        }
        i = 0;  // Reset sequence after checking
    }

}

// GPIO EXTI callback handler for direction switching
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	// Switch 1
    if(GPIO_Pin == GPIO_PIN_4){ // Check if PC4 is the interrupt pin
    	screen_flag = 1;
    	button_flag = 4;
    }

    // Switch 2
    if(GPIO_Pin == GPIO_PIN_5){ // Check if PC5 is the interrupt pin
    	LED_flag = !LED_flag;
    	button_flag = 5;
    }
}

// TIM2 callback, triggers every ~0.125 seconds
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){ // Confirm htim2 is the interrupt clock
		read_flag = 1; // Set flag to calculate RPM
	}
}
