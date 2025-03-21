#include "main.h"
#include "fonts.h"
#include "ssd1306.h"

void SSD1306_Temperature(float temp, float avg_temp){
	char buffer[32];

	SSD1306_GotoXY(0, 10);
	sprintf(buffer, "Temperature");
	SSD1306_Puts(buffer, &Font_11x18, SSD1306_COLOR_WHITE);

	// Print temperature
	SSD1306_GotoXY(0, 30);
	sprintf(buffer, "Live: %.2f F", temp);
	SSD1306_Puts(buffer, &Font_7x10, SSD1306_COLOR_WHITE);

	// Print average temperature
	SSD1306_GotoXY(0, 40);
	sprintf(buffer, "Average: %.2f F", avg_temp);
	SSD1306_Puts(buffer, &Font_7x10, SSD1306_COLOR_WHITE);
}


void SSD1306_Light(float light, float light_avg){
	char buffer[32];

	SSD1306_GotoXY(0, 10);
	sprintf(buffer, "Light");
	SSD1306_Puts(buffer, &Font_11x18, SSD1306_COLOR_WHITE);

	// Print temperature
	SSD1306_GotoXY(0, 30);
	sprintf(buffer, "Live: %.2f  Lux", light);
	SSD1306_Puts(buffer, &Font_7x10, SSD1306_COLOR_WHITE);

	// Print average temperature
	SSD1306_GotoXY(0, 40);
	sprintf(buffer, "Average: %.2f  Lux", light_avg);
	SSD1306_Puts(buffer, &Font_7x10, SSD1306_COLOR_WHITE);
}

void SSD1306_Show_Readings(float temp, float volts, float light, int hum){
	char buffer[32]; // Buffer to hold strings before printing
    RTC_TimeTypeDef time;

    // Get the current time
    HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);

	// Print temperature
	SSD1306_GotoXY(0, 10);
	sprintf(buffer, "Temp: %.2f F", temp);
	SSD1306_Puts(buffer, &Font_7x10, SSD1306_COLOR_WHITE);

	// Print average temperature
	SSD1306_GotoXY(0, 20);
	sprintf(buffer, "V_ADC: %.2f V", volts);
	SSD1306_Puts(buffer, &Font_7x10, SSD1306_COLOR_WHITE);

	// Print light level
	SSD1306_GotoXY(0, 30);
	sprintf(buffer, "Light: %.2f Lux", light);
	SSD1306_Puts(buffer, &Font_7x10, SSD1306_COLOR_WHITE);

	// Print humidity
	SSD1306_GotoXY(0, 40);
	sprintf(buffer, "Humidity: %d%%", hum);
	SSD1306_Puts(buffer, &Font_7x10, SSD1306_COLOR_WHITE);

	// Print time
	SSD1306_GotoXY(0, 50);
	sprintf(buffer, "Time: %02d:%02d:%02d", sTime.Hours, sTime.Minutes, sTime.Seconds);
	SSD1306_Puts(buffer, &Font_7x10, SSD1306_COLOR_WHITE);
}
