#ifndef INC_ALTIMETER_H_
HAL_StatusTypeDef I2C_Write(uint8_t reg_addr, uint8_t *write_data, uint16_t length);
HAL_StatusTypeDef I2C_Read(uint8_t reg, uint8_t *data);
#define INC_ALTIMETER_H_
#endif /* INC_ALTIMETER_H_ */
