#ifndef INC_ALTIMETER_H_

void MPL3115A2_write(uint8_t reg, uint8_t value);
uint8_t MPL3115A2_read(uint8_t reg);
void MPL3115A2_init();
float MPL3115A2_pressure();
float MPL3115A2_temp();

#define INC_ALTIMETER_H_
#endif /* INC_ALTIMETER_H_ */
