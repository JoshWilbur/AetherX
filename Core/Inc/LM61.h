#ifndef INC_LM61_H_
#define INC_LM61_H_

int LM61_read(void);
float LM61_temp(int unit);
float Temp_avg(int readings);

#endif /* INC_LM61_H_ */
