#ifndef INC_SCREENS_H_
#define INC_SCREENS_H_

void SSD1306_Show_Readings(float temp, float avg_temp, float light, int hum);

void SSD1306_Temperature(float temp, float avg_temp);
void SSD1306_Light(float light, float light_avg);

#endif /* INC_SCREENS_H_ */
