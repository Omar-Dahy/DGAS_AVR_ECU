#include "StdTypes.h"
#include "DIO_Int.h"
#include "MOTOR_Int.h"

#define FORWARD_B       PINC0
#define RIGHT_B         PINC1
#define LEFT_B          PINC2
#define BACKWARD_B      PINC3
#define STOP_B          PINC4
void MOVE_Init(void)
{
	
}


void FORWARD (void)
{
	MOTOR_CW(M1);
	MOTOR_CW(M2);
	MOTOR_CCW(M3);
	MOTOR_CCW(M4);
}
void BACKWARD (void)
{
	MOTOR_CCW(M1);
	MOTOR_CCW(M2);
	MOTOR_CW(M3);
	MOTOR_CW(M4);
}
void RIGHT(void)
{
	MOTOR_CW(M1);
	MOTOR_CW(M2);
	MOTOR_Stop(M3);
	MOTOR_Stop(M4);
}
void LEFT(void)
{
	MOTOR_Stop(M1);
	MOTOR_Stop(M2);
	MOTOR_CCW(M3);
	MOTOR_CCW(M4);
}
void STOP_MOVE (void)
{
	MOTOR_Stop(M1);
	MOTOR_Stop(M2);
	MOTOR_Stop(M3);
	MOTOR_Stop(M4);
}
void MOVE_Runnable(void)
{
	if(DIO_ReadPin(FORWARD_B)==LOW)
	{
		FORWARD();
		while(DIO_ReadPin(FORWARD_B)==LOW);
	}
	if(DIO_ReadPin(BACKWARD_B)==LOW)
	{
		BACKWARD();
		while(DIO_ReadPin(BACKWARD_B)==LOW);
	}
	if(DIO_ReadPin(RIGHT_B)==LOW)
	{
		RIGHT();
		while(DIO_ReadPin(RIGHT_B)==LOW);
	}
	if(DIO_ReadPin(LEFT_B)==LOW)
	{
		LEFT();
		while(DIO_ReadPin(LEFT_B)==LOW);
	}
	if(DIO_ReadPin(STOP_B)==LOW)
	{
		STOP_MOVE();
		while(DIO_ReadPin(STOP_B)==LOW);
	}
}