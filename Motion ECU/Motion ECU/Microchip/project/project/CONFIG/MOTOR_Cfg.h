#ifndef MOTOR_CFG_H_
#define MOTOR_CFG_H_
//#include "MOTOR_Int.h"


#define Motor1_SetCompareUnit(value)     (OCR1A=(value))
#define Motor2_SetCompareUnit(value)     (OCR1B=(value))

#define  M1_IN1  PINB0
#define  M1_IN2  PINB1

#define  M2_IN1  PIND6
#define  M2_IN2  PIND7

#define  M3_IN1  PINC2
#define  M3_IN2  PINC3

#define  M4_IN1  PINC4
#define  M4_IN2  PINC5

#define  ENABLE_Status 2 /********************************/




#define DIR1_PIN   PINA0

#define DIR2_PIN   PINA1

#endif /* MOTOR_CFG_H_ */