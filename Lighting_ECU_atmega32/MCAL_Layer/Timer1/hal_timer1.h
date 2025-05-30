/*
 * File   :  hal_timer1.h
 * https://www.linkedin.com/in/ahmed-shawada/
 * Created: 1/25/2025 3:43:13 PM
 * Author: AhmedShawada
 */ 


#ifndef HAL_TIMER1_H_
#define HAL_TIMER1_H_


/*Section       :         Includes                */
#include <avr/io.h>
#include "mcal_internal_interrupt.h"
#include "mcal_std_types.h"
#include "GPIO/hal_gpio.h"

/*Section       :         Data type Deceleration                 */

typedef enum
{
	TMR1_INTERRUPT_DISABLE,
	TMR1_INTERRUPT_ENABLE
	
}TIMER1_INTERRUPT_CONFIG;

typedef enum{
	TIMER1_STOP = 0,
	TIMER1_SCALER_1,
	TIMER1_SCALER_8,
	TIMER1_SCALER_64,
	TIMER1_SCALER_256,
	TIMER1_SCALER_1024,
	EXTERNAL0_FALLING,
	EXTERNAL0_RISING
	
}Timer1Scaler_Type;

typedef enum
{
	TIMER1_NORMAL_MODE = 0,
	TIMER1_CTC_ICR_TOP_MODE,
	TIMER1_CTC_OCRA_TOP_MODE,
	TIMER1_FASTPWM_ICR_TOP_MODE,
	TIMER1_FASTPWM_OCRA_TOP_MODE

}Timer1Mode_type;

typedef enum{
	OCR1A_NORMAL_COMPARE_MODE = 0,
	OCR1A_TOGGLE_COMPARE_BIT_MODE,
	OCR1A_CLEAR_COMPARE_BIT_MODE,
	OCR1A_SET_COMPARE_BIT_MODE,
	OCR1A_no_value,
}OCR1A_COMPARE_MODE_T;

typedef enum
{
	OCR1B_NORMAL_COMPARE_MODE = 0,
	OCR1B_TOGGLE_COMPARE_BIT_MODE,
	OCR1B_CLEAR_COMPARE_BIT_MODE,
	OCR1B_SET_COMPARE_BIT_MODE,
	OCR1B_no_value,
}OCR1B_COMPARE_MODE_T;


typedef enum
{
	OCR1A_FAST_PWM_DISCONNECTED = 0,
	OCR1A_RESERVED,
	OCR1A_FAST_PWM_NON_INVERTING,
	OCR1A_FAST_PWM_INVERTING
	
}OCR1A_FAST_PWM_MODE_T;

typedef enum
{
	OCR1B_FAST_PWM_DISCONNECTED = 0,
	OCR1B_RESERVED,
	OCR1B_FAST_PWM_NON_INVERTING,
	OCR1B_FAST_PWM_INVERTING
	
}OCR1B_FAST_PWM_MODE_T;


typedef enum
{
	NOISE_CANCLER_OFF = 0,
	NOISE_CANCLER_ON
	
}CAPTURE_INPUT_NOISE_CANCLER;


typedef enum{
	RISING,
	FALLING
	
}ICU_Edge_Type;

typedef struct
{
#if TMR1_CAPTURE_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
	void (*TMR1_Capture_InterruptHandler)(void);
#endif
#if TMR1_COMPARE_A_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
	void (*TMR1_CompareA_InterruptHandler)(void);
#endif
#if TMR1_COMPARE_B_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
	void (*TMR1_CompareB_InterruptHandler)(void);
#endif
#if TMR1_OVERFLOW_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
	void (*TMR1_OverFlow_InterruptHandler)(void);
#endif
	uint16 TMR1_PRELOAD_VALUE;
	uint16 COMPARE_VALUE_A;
	uint16 COMPARE_VALUE_B;
	uint16 CAPTURE_VALUE;
	TIMER1_INTERRUPT_CONFIG TIMER1_INTERRUPT;
	Timer1Scaler_Type PRESCALER_VALUE;
	Timer1Mode_type TIMER_MODE;
	OCR1A_COMPARE_MODE_T OC1A_CMode;
	OCR1B_COMPARE_MODE_T OC1B_CMode;
	OCR1A_FAST_PWM_MODE_T OC1A_PMode;
	OCR1B_FAST_PWM_MODE_T OC1B_PMode;
	CAPTURE_INPUT_NOISE_CANCLER NOISE_CANCLER;
	ICU_Edge_Type EDGE;
}Timer1_t;


/*Section       :         Macro Deceleration                */



/*Section       :         Macro Function Deceleration                */

#define OVERFLOW_STATUS()					(READ_BIT(TIFR,TOV1))

#define TIMER1_SetCompareUnitA1(value)		(OCR1A=(value))
#define TIMER1_SetCompareUnitB1(value)		(OCR1B=(value))
#define TIMER1_Set(value)					(TCNT1=(value))
#define TIMER1_Read()						((TCNT1))
#define TIMER1_ICR_Read()					((ICR1))
#define TIMER1_SET_ICR(value)				(ICR1=(value))

/*Section       :         Function Deceleration                */
Std_ReturnType Timer1_Init(const Timer1_t *timer1_obj);
Std_ReturnType Timer1_DeInit(const Timer1_t *timer1_obj);


#endif /* HAL_TIMER1_H_ */