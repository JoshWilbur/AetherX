#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

int Poll_Button1(void);
int Poll_Button2(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

extern volatile int screen_flag;
extern volatile int LED_flag;

#endif /* INC_BUTTON_H_ */
