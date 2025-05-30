#include "StdTypes.h"
#include "DIO_Int.h" 
#include "MOTOR_Cfg.h"
#include "MOTOR_Int.h"
#include "MOTOR_Priv.h"
#include "Timers.h"
#include "Timers_Services.h"

u8 global_speed = 255;

void MOTOR_Init(void){
	Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8);
	Timer1_OCRA1Mode(OCRA_NON_INVERTING);
	Timer1_OCRB1Mode(OCRB_NON_INVERTING);
	TIMER1_SET_ICR(255);
}

void MOTOR_Stop(MOTOR_t motor){
	if (motor==M1)
	{
		Motor1_SetCompareUnit(0);
	}
	else if(motor==M2)
	{
		Motor2_SetCompareUnit(0);
	}
	else if(motor==TOTAL_MOTORS)
	{
		Motor1_SetCompareUnit(0);
		Motor2_SetCompareUnit(0);
	}
}

void MOTOR_CW(MOTOR_t motor){
	/*0<speed<255*/
	
	if (motor==M1)
	{
		DIO_WritePin(DIR1_PIN,HIGH);
		Motor1_SetCompareUnit(global_speed);
	}
	else if (motor==M2)
	{
		DIO_WritePin(DIR2_PIN,HIGH);
		Motor2_SetCompareUnit(global_speed);
	}
	else if (motor==TOTAL_MOTORS)
	{
		DIO_WritePin(DIR1_PIN,HIGH);
		DIO_WritePin(DIR2_PIN,HIGH);
		Motor1_SetCompareUnit(global_speed);
		Motor2_SetCompareUnit(global_speed);
	}
}

void MOTOR_CCW(MOTOR_t motor){	
		/*0<speed<255*/
		
		if (motor==M1)
		{
			DIO_WritePin(DIR1_PIN,LOW);
			Motor1_SetCompareUnit(global_speed);
		}
		else if (motor==M2)
		{
			DIO_WritePin(DIR2_PIN,LOW);
			Motor2_SetCompareUnit(global_speed);
		}
		else if (motor==TOTAL_MOTORS)
		{
			DIO_WritePin(DIR1_PIN,LOW);
			DIO_WritePin(DIR2_PIN,LOW);
			Motor1_SetCompareUnit(global_speed);
			Motor2_SetCompareUnit(global_speed);
		}
}

/* speed 0:100 */
void MOTOR_Speed(u8 speed){
	if((speed > 100)||(speed < 0)){
		global_speed = 255;
	}
	else{
		global_speed = ((float)speed / 100) * 255;
	}
	
}
/****************************************************/