#ifndef INC_LM61_H_
#define INC_LM61_H_

int LM61_Read(void);
float LM61_Temp(int unit);
float Temp_Avg(float *readings, int len);

#endif /* INC_LM61_H_ */
