#include "main.h"
#include "fonts.h"
#include "ssd1306.h"

void SSD1306_Screen(float stat, float avg, const char *metric, const char *unit, float high, float low){
	char buffer[32];

	// Print metric name
	SSD1306_GotoXY(0, 0);
	sprintf(buffer, "%s", metric);
	SSD1306_Puts(buffer, &Font_11x18, SSD1306_COLOR_WHITE);

	// Print live value
	SSD1306_GotoXY(0, 20);
	sprintf(buffer, "Live: %.2f %s", stat, unit);
	SSD1306_Puts(buffer, &Font_7x10, SSD1306_COLOR_WHITE);

	// Print average value
	SSD1306_GotoXY(0, 30);
	sprintf(buffer, "Avg: %.2f %s", avg, unit);
	SSD1306_Puts(buffer, &Font_7x10, SSD1306_COLOR_WHITE);

	// Print high value
	SSD1306_GotoXY(0, 40);
	sprintf(buffer, "High: %.2f %s", high, unit);
	SSD1306_Puts(buffer, &Font_7x10, SSD1306_COLOR_WHITE);

	// Print low value
	SSD1306_GotoXY(0, 50);
	sprintf(buffer, "Low: %.2f %s", low, unit);
	SSD1306_Puts(buffer, &Font_7x10, SSD1306_COLOR_WHITE);
}

void SSD1306_Show_Readings(float temp, float volts, float light, int hum){
	char buffer[32]; // Buffer to hold strings before printing
    RTC_TimeTypeDef time;

    // Get the current time
    HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);

	// Print temperature
	SSD1306_GotoXY(0, 0);
	sprintf(buffer, "Temp: %.2f F", temp);
	SSD1306_Puts(buffer, &Font_7x10, SSD1306_COLOR_WHITE);

	// Print average temperature
	SSD1306_GotoXY(0, 10);
	sprintf(buffer, "V_ADC: %.2f V", volts);
	SSD1306_Puts(buffer, &Font_7x10, SSD1306_COLOR_WHITE);

	// Print light level
	SSD1306_GotoXY(0, 20);
	sprintf(buffer, "Light: %.2f Lux", light);
	SSD1306_Puts(buffer, &Font_7x10, SSD1306_COLOR_WHITE);

	// Print humidity
	SSD1306_GotoXY(0, 30);
	sprintf(buffer, "Humidity: %d%%", hum);
	SSD1306_Puts(buffer, &Font_7x10, SSD1306_COLOR_WHITE);

	// Print time
	SSD1306_GotoXY(0, 40);
	sprintf(buffer, "Time: %02d:%02d:%02d", sTime.Hours, sTime.Minutes, sTime.Seconds);
	SSD1306_Puts(buffer, &Font_7x10, SSD1306_COLOR_WHITE);
}
