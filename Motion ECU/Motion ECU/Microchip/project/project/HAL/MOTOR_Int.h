#ifndef MOTOR_INT_H_
#define MOTOR_INT_H_

typedef enum{
	M1,
	M2,
	TOTAL_MOTORS
}MOTOR_t;

void MOTOR_Init(void);

void MOTOR_Stop(MOTOR_t motor); 
void MOTOR_CW(MOTOR_t motor);
void MOTOR_CCW(MOTOR_t motor);

/* speed 0:100 */
void MOTOR_Speed(u8 speed);





#endif /* MOTOR_INT_H_ */