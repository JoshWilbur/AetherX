#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

int Poll_Button1(void);
int Poll_Button2(void);
void Button_History(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

extern volatile int screen_flag;
extern volatile int LED_flag;
extern volatile int read_flag;
extern volatile int button_flag;
extern int standby_flag;

#endif /* INC_BUTTON_H_ */
