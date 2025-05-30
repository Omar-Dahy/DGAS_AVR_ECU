/*
 * File   :  hal_timer0.h
 * https://www.linkedin.com/in/ahmed-shawada/
 * Created: 1/25/2025 3:43:13 PM
 * Author: AhmedShawada
 */ 


#ifndef HAL_TIMER0_H_
#define HAL_TIMER0_H_

/*Section       :         Includes                */
#include <avr/io.h>
#include "mcal_internal_interrupt.h"
#include "mcal_std_types.h"
#include "GPIO/hal_gpio.h"

/*Section       :         Data type Deceleration                 */
typedef enum
{
	TMR0_INTERRUPT_DISABLE,
	TMR0_INTERRUPT_ENABLE
}TIMER0_INTERRUPT_CONFIG;

typedef enum
{
	TIMER0_STOP=0,
	TIMER0_SCALER_1,
	TIMER0_SCALER_8,
	TIMER0_SCALER_64,
	TIMER0_SCALER_256,
	TIMER0_SCALER_1024,
	EXTERNALl_FALLING,
	EXTERNAL_RISING
}Timer0Scaler_t;

typedef enum
{
	TIMER0_NORMAL_MODE=0,
	TIMER0_CTC=2,
	TIMER0_FAST_PWM=3,
}TIMER0_MODES;

typedef enum
{
	NORMAL_COMPARE_MODE = 0,
	TOGGLE_COMPARE_BIT_MODE,
	CLEAR_COMPARE_BIT_MODE,
	SET_COMPARE_BIT_MODE,
}COMPARE_MODE_T;

typedef enum
{
	FAST_PWM_DISCONNECTED = 0,
	FAST_PWM_RESERVED,
	FAST_PWM_NON_INVERTING,
	FAST_PWM_INVERTING
}FAST_PWM_MODE_T;


typedef enum
{
	PHASE_CORRECT_DISCONNECTED = 0,
	PHASE_CORRECT_ESERVED,
	PHASE_CORRECT_NON_INVERTING,
	PHASE_CORRECT_INVERTING
}PHASE_CORRECT_MODE_T;



typedef struct
{
#if TMR0_COMPARE_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
	void (*TMR0_Compare_InterruptHandler)(void);
#endif
#if TMR0_OVERFLOW_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
	void (*TMR0_OverFlow_InterruptHandler)(void);
#endif

	uint8 PRELOAD_VALUE;
	uint8 COMPARE_VALUE;
	TIMER0_INTERRUPT_CONFIG TIMER0_INTERRUPT;
	Timer0Scaler_t PRESCALER_VALUE;
	TIMER0_MODES TIMER_MODE;
	COMPARE_MODE_T COMPARE_MODE;
	FAST_PWM_MODE_T PWM_MODE;
	
}Timer0_t;

/*Section       :         Macro Deceleration                */


/*Section       :         Macro Function Deceleration                */
#define TIMER0_SetCompareUnit(value)     (OCR0=(value))
#define TIMER0_ReadCompareUnit()         ((OCR0))
#define TIMER0_Set(value)                (TCNT0=(value))
#define TIMER0_Read()                    ((TCNT0))


/*Section       :         Function Deceleration                */
Std_ReturnType Timer0_Init(const Timer0_t *timer0_obj);
Std_ReturnType Timer0_DeInit(const Timer0_t *timer0_obj);
Std_ReturnType Timer0_Set_Duty(const Timer0_t *timer0_obj, uint8 DUTY_VALUE);




#endif /* HAL_TIMER0_H_ */