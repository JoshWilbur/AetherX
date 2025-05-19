#ifndef INC_SCREENS_H_
#define INC_SCREENS_H_

void SSD1306_Show_Readings(float temp, float avg_temp, float light, int hum);

void SSD1306_Screen(float stat, float avg, char *metric, char *unit);

#endif /* INC_SCREENS_H_ */
