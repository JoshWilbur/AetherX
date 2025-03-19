#ifndef INC_OPT101_H_
#define INC_OPT101_H_

int OPT101_Read(void);
float OPT101_Lux(void);
float OPT101_Avg(float *readings, int len);

#endif /* INC_OPT101_H_ */
