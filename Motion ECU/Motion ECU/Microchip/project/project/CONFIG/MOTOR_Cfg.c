#include "StdTypes.h"
#include "MOTOR_Int.h"
#include "MOTOR_Cfg.h"
#include "DIO_Int.h"

const DIO_Pin_t MOTOR_ENABLE [TOTAL_MOTORS][ENABLE_Status]={
	{M1_IN1,M1_IN2},
	{M2_IN1,M2_IN2},
	{M3_IN1,M3_IN2},
	{M4_IN1,M4_IN2}
};



