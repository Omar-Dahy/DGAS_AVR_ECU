/*
 * File   :  hal_timer1.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Created: 1/25/2025 3:43:13 PM
 * Author: AhmedShawada
 */

#include "hal_timer1.h"

/******* Pointer to function to hold the call-backs for TMR1 *******/
#if TMR1_CAPTURE_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static volatile void (*TMR1_Capture_InterruptHandler)(void) = NULL;
#endif

#if TMR1_COMPARE_A_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static volatile void (*TMR1_CompareA_InterruptHandler)(void) = NULL;
#endif

#if TMR1_COMPARE_B_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static volatile void (*TMR1_CompareB_InterruptHandler)(void) = NULL;
#endif

#if TMR1_OVERFLOW_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static volatile void (*TMR1_OverFlow_InterruptHandler)(void) = NULL;
#endif
/*****************************END*************************************/


/***************************Helper_Function***************************/
static Std_ReturnType TMR1_NORMAL_OR_CTC_MODE_SELECT(const Timer1_t *timer1_obj);
static Std_ReturnType TMR1_FAST_PWM_MODE_SELECT(const Timer1_t *timer1_obj);
static Std_ReturnType TMR1_Interrupt_Init (const Timer1_t *timer1_obj);
/*****************************END*************************************/

static volatile uint16 timer1_preload = ZERO_INIT;
static volatile uint16 capture_value = ZERO_INIT;
static volatile uint16 compareA_value = ZERO_INIT;
static volatile uint16 compareB_value = ZERO_INIT;



/**
 * @Summary
 *   Initializes Timer1 with the specified configuration.
 * 
 * @Description
 *   This function configures Timer1 based on the settings provided in the 
 *   Timer1_t configuration object. It handles timer modes, pre-load values, 
 *   pre-scaler setup, and interrupt initialization.
 *
 * @Preconditions
 *   - The Timer1_t configuration object must be initialized with valid parameters.
 *   - The microcontroller's clock source should be configured before calling this function.
 * 
 * @param timer1_obj
 *   A pointer to a Timer1_t structure containing the desired configuration:
 *     - timer1_preload_value: Pre-load value for the timer counter.
 *     - Timer1_Mode: Timer1 operating mode (e.g., Normal, CTC, Fast PWM).
 *     - Scaler: Timer clock pre-scaler value.
 *     - timer_interrupt: Interrupt enable/disable for Timer1.
 * 
 * @return 
 *   - E_OK: Timer1 was successfully initialized.
 *   - E_NOT_OK: An error occurred (e.g., null pointer).
 */
Std_ReturnType Timer1_Init(const Timer1_t *timer1_obj)
{
	Std_ReturnType ret = E_OK;
	
	if(NULL == timer1_obj)
	{
		ret = E_NOT_OK;
	} 
	
	else
	{	
		/*  Configure OC1B,OC1A (PD4,PD5) as an output pin */	
		pin_config_t outputB_pin = {	.port = PORTD_INDEX, .direction = GPIO_DIRECTION_OUTPUT,
										.logic = GPIO_LOW, .pin = GPIO_PIN4	 };
		
		pin_config_t outputA_pin = {	.port = PORTD_INDEX, .direction = GPIO_DIRECTION_OUTPUT,
										.logic = GPIO_LOW, .pin = GPIO_PIN5	 };
		
		ret = gpio_pin_direction_intialize(&outputB_pin);
		ret = gpio_pin_direction_intialize(&outputA_pin);
		
		/* Store pre-load value and load it into the timer */
		//TCNT1H = (timer1_obj->TMR1_PRELOAD_VALUE) >> 8;
		//TCNT1L = (uint8)(timer1_obj->TMR1_PRELOAD_VALUE);
		//timer1_preload = timer1_obj->TMR1_PRELOAD_VALUE;
		
		/* Store compare A value and set it in Timer1 */
		OCR1AH = (timer1_obj->COMPARE_VALUE_A) >> 8;
		OCR1AL = (uint8)(timer1_obj->COMPARE_VALUE_A);
		compareA_value = timer1_obj->COMPARE_VALUE_A;
		
		/* Store compare B value and set it in Timer1 */
		OCR1BH = (timer1_obj->COMPARE_VALUE_B) >> 8;
		OCR1BL = (uint8)(timer1_obj->COMPARE_VALUE_B);
		compareB_value = timer1_obj->COMPARE_VALUE_B;
		
		/* Store capture value and set it in Timer1 */
		ICR1H = (timer1_obj->CAPTURE_VALUE) >> 8;
		ICR1L = (uint8)(timer1_obj->CAPTURE_VALUE);
		capture_value = timer1_obj->CAPTURE_VALUE;
		
		/* Interrupt Configurations */
		if(TMR1_INTERRUPT_ENABLE == timer1_obj->TIMER1_INTERRUPT)
		{
			ret = TMR1_Interrupt_Init(timer1_obj);
		}
		else{ /* Nothing */ }
		
		/* Select Timer1 mode based on configuration */
		switch (timer1_obj->TIMER_MODE)
		{
			case TIMER1_NORMAL_MODE :
			CLEAR_BIT(TCCR1A,WGM10);
			CLEAR_BIT(TCCR1A,WGM11);
			CLEAR_BIT(TCCR1B,WGM12);
			CLEAR_BIT(TCCR1B,WGM13);
			ret = TMR1_NORMAL_OR_CTC_MODE_SELECT(timer1_obj);
			break;
			case TIMER1_CTC_ICR_TOP_MODE :
			CLEAR_BIT(TCCR1A,WGM10);
			CLEAR_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			SET_BIT(TCCR1B,WGM13);
			ret = TMR1_NORMAL_OR_CTC_MODE_SELECT(timer1_obj);
			break;
			
			case TIMER1_CTC_OCRA_TOP_MODE :
			CLEAR_BIT(TCCR1A,WGM10);
			CLEAR_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			CLEAR_BIT(TCCR1B,WGM13);
			ret = TMR1_NORMAL_OR_CTC_MODE_SELECT(timer1_obj);
			break;
			
			case TIMER1_FASTPWM_ICR_TOP_MODE :
			CLEAR_BIT(TCCR1A,WGM10);
			SET_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			SET_BIT(TCCR1B,WGM13);
			ret = TMR1_FAST_PWM_MODE_SELECT(timer1_obj);
			break;
			
			case TIMER1_FASTPWM_OCRA_TOP_MODE :
			SET_BIT(TCCR1A,WGM10);
			SET_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			SET_BIT(TCCR1B,WGM13);
			ret = TMR1_FAST_PWM_MODE_SELECT(timer1_obj);
			break;
		}
		
		/* Set Timer1 pre-scaler */
		TCCR1B &= 0XF8;
		TCCR1B |= timer1_obj->PRESCALER_VALUE;
		
		ret = E_OK;
	}
	
	return ret;
}


/**
 * @Summary
 *   De-initializes Timer1.
 *
 * @Description
 *   Stops Timer1, disables interrupts, and clears the configuration registers.
 *
 * @Preconditions
 *   - Timer1 must have been previously initialized.
 *
 * @param timer1_obj
 *   A pointer to the Timer0_t structure.
 *
 * @return 
 *   - E_OK: Timer1 was successfully de-initialized.
 *   - E_NOT_OK: An error occurred (e.g., null pointer).
 */
Std_ReturnType Timer1_DeInit(const Timer1_t *timer1_obj)
{
	Std_ReturnType ret = E_OK;
	
	if(NULL == timer1_obj)
	{
		ret = E_NOT_OK;
	}
	
	else
	{
		/* Stop Timer1 */
		TCCR1B = TIMER1_STOP;
		
		//CLEAR_BIT(TCCR1B,CS10);
		//CLEAR_BIT(TCCR1B,CS11);
		//CLEAR_BIT(TCCR1B,CS12);
		
		/* Disable interrupts */
#if TMR1_CAPTURE_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
		TMR1_Capture_InterruptHandler = timer1_obj->TMR1_Capture_InterruptHandler;
		TMR1_Capture_InterruptDisable();
#endif

#if TMR1_COMPARE_A_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
		TMR1_CompareA_InterruptHandler = timer1_obj->TMR1_CompareA_InterruptHandler;
		TMR1_CompareA_InterruptDisable();
#endif

#if TMR1_COMPARE_B_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
		TMR1_CompareB_InterruptHandler = timer1_obj->TMR1_CompareB_InterruptHandler;
		TMR1_CompareB_InterruptDisable();
#endif

#if TMR1_OVERFLOW_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
		TMR1_OverFlow_InterruptHandler = timer1_obj->TMR1_OverFlow_InterruptHandler;
		TMR1_OverFlow_InterruptDisable();
#endif					
		ret = E_OK;
	}
	
	return ret;
}


/**
 * @Summary
 *   Configures Timer1 for Normal or CTC (Clear Timer on Compare Match) mode.
 * 
 * @Description
 *   This function sets up Timer1 to operate in either Normal mode or CTC mode. It adjusts the compare output modes for both OC1A and OC1B pins based on the provided configuration in the `timer1_obj` structure. It handles four modes for each pin, including normal compare mode, toggle compare bit mode, clear compare bit mode, and set compare bit mode.
 *   The TCCR1A register is updated accordingly to match the required mode for each channel.
 * 
 * @Preconditions
 *   - The `timer1_obj` must be a valid pointer to a `Timer1_t` structure.
 *   - The `timer1_obj` structure must be initialized with the correct values for `OC1A_CMode` and `OC1B_CMode`, which define the compare output modes for OC1A and OC1B.
 * 
 * @param timer1_obj
 *   A pointer to a `Timer1_t` structure containing the configuration for the compare output modes of OC1A and OC1B:
 *     - OC1A_CMode: The compare mode for OC1A (e.g., normal, toggle, clear, set).
 *     - OC1B_CMode: The compare mode for OC1B (e.g., normal, toggle, clear, set).
 * 
 * @return 
 *   - E_OK: The configuration was applied successfully.
 *   - E_NOT_OK: An error occurred (e.g., null pointer).
 */
static Std_ReturnType TMR1_NORMAL_OR_CTC_MODE_SELECT(const Timer1_t *timer1_obj)
{
	Std_ReturnType ret = E_OK;
	if(NULL == timer1_obj)
	{
		ret = E_NOT_OK;
		
	}
	else
	{
		/* Configure OC1A output mode based on the selected compare mode */ 
		switch(timer1_obj->OC1A_CMode)
		{
			case OCR1A_NORMAL_COMPARE_MODE :
			CLEAR_BIT(TCCR1A,COM1A1);
			CLEAR_BIT(TCCR1A,COM1A0);
			break;
			
			case OCR1A_TOGGLE_COMPARE_BIT_MODE :
			CLEAR_BIT(TCCR1A,COM1A1);
			SET_BIT(TCCR1A,COM1A0);
			break;
			
			case OCR1A_CLEAR_COMPARE_BIT_MODE :
			SET_BIT(TCCR1A,COM1A1);
			CLEAR_BIT(TCCR1A,COM1A0);
			break;
			
			case OCR1A_SET_COMPARE_BIT_MODE :
			SET_BIT(TCCR1A,COM1A1);
			SET_BIT(TCCR1A,COM1A0);
			break;
			default:
			
			break;
		}
		
		/* Configure OC1B output mode based on the selected compare mode */
		switch(timer1_obj->OC1B_CMode)
		{
			case OCR1B_NORMAL_COMPARE_MODE :
			CLEAR_BIT(TCCR1A,COM1B1);
			CLEAR_BIT(TCCR1A,COM1B0);
			break;
			
			case OCR1B_TOGGLE_COMPARE_BIT_MODE :
			CLEAR_BIT(TCCR1A,COM1B1);
			SET_BIT(TCCR1A,COM1B0);
			break;
			
			case OCR1B_CLEAR_COMPARE_BIT_MODE :
			SET_BIT(TCCR1A,COM1B1);
			CLEAR_BIT(TCCR1A,COM1B0);
			break;
			
			case OCR1B_SET_COMPARE_BIT_MODE :
			SET_BIT(TCCR1A,COM1B1);
			SET_BIT(TCCR1A,COM1B0);
			break;
			default:
			
			break;
		}
		
	}
	return ret;
	
}


/**
 * @Summary
 *   Configures Timer1 for Fast PWM (Pulse Width Modulation) mode.
 * 
 * @Description
 *   This function configures Timer1 to operate in Fast PWM mode. It adjusts the duty cycle for both OC1A and OC1B output channels using the OCR1A and OCR1B registers. Based on the configuration in `timer1_obj`, the function selects one of the four available PWM modes for each channel: non-inverting, inverting, reserved, or disconnected.
 *   The TCCR1A register is updated accordingly to match the desired PWM mode for both OC1A and OC1B pins.
 * 
 * @Preconditions
 *   - The `timer1_obj` must be a valid pointer to a `Timer1_t` structure.
 *   - The `timer1_obj` structure must be initialized with valid values for `OC1A_PMode` and `OC1B_PMode`, which define the PWM modes for OC1A and OC1B (e.g., non-inverting, inverting, disconnected).
 * 
 * @param timer1_obj
 *   A pointer to a `Timer1_t` structure containing the configuration for the PWM modes of OC1A and OC1B:
 *     - OC1A_PMode: The PWM mode for OC1A (e.g., non-inverting, inverting, disconnected).
 *     - OC1B_PMode: The PWM mode for OC1B (e.g., non-inverting, inverting, disconnected).
 * 
 * @return 
 *   - E_OK: The configuration was applied successfully.
 *   - E_NOT_OK: An error occurred (e.g., null pointer).
 */
static Std_ReturnType TMR1_FAST_PWM_MODE_SELECT(const Timer1_t *timer1_obj)
{
	Std_ReturnType ret = E_OK;
	if(NULL == timer1_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		/* Configure OC1A PWM mode based on the selected Fast PWM mode */
		switch(timer1_obj->OC1A_PMode)
		{
			case OCR1A_FAST_PWM_DISCONNECTED:
			CLEAR_BIT(TCCR1A,COM1A1);
			CLEAR_BIT(TCCR1A,COM1A0);
			break;
			
			case OCR1A_RESERVED:
			CLEAR_BIT(TCCR1A,COM1A1);
			SET_BIT(TCCR1A,COM1A0);
			break;
			
			case OCR1A_FAST_PWM_NON_INVERTING:
			SET_BIT(TCCR1A,COM1A1);
			CLEAR_BIT(TCCR1A,COM1A0);
			break;
			
			case OCR1A_FAST_PWM_INVERTING:
			SET_BIT(TCCR1A,COM1A1);
			SET_BIT(TCCR1A,COM1A0);
			break;
		}
		
		/* Configure OC1B PWM mode based on the selected Fast PWM mode */ 
		switch(timer1_obj->OC1B_PMode)
		{
			case OCR1B_FAST_PWM_DISCONNECTED:
			CLEAR_BIT(TCCR1A,COM1B1);
			CLEAR_BIT(TCCR1A,COM1B0);
			break;
			case OCR1B_RESERVED:
			CLEAR_BIT(TCCR1A,COM1B1);
			SET_BIT(TCCR1A,COM1B0);
			break;
			case OCR1B_FAST_PWM_NON_INVERTING:
			SET_BIT(TCCR1A,COM1B1);
			CLEAR_BIT(TCCR1A,COM1B0);
			break;
			case OCR1B_FAST_PWM_INVERTING:
			SET_BIT(TCCR1A,COM1B1);
			SET_BIT(TCCR1A,COM1B0);
			break;
		}
		
	}
	return ret ;
}



/**
 * @Summary
 *   Initializes Timer1 interrupts.
 * 
 * @Description
 *   This static function enables Timer1-related interrupts (input capture, 
 *   compare A, compare B, overflow) if they are enabled in the configuration.
 *
 * @Preconditions
 *   - Timer1 must be initialized.
 *   - Interrupt handlers should be properly assigned in the configuration object.
 * 
 * @param timer1_obj
 *   A pointer to a Timer1_t structure containing the interrupt configuration:
 *     - TMR1_Capture_InterruptHandler: Function pointer for input capture interrupt.
 *     - TMR1_CompareA_InterruptHandler: Function pointer for compare A interrupt.
 *     - TMR1_CompareB_InterruptHandler: Function pointer for compare B interrupt.
 *     - TMR1_OverFlow_InterruptHandler: Function pointer for overflow interrupt.
 * 
 * @return 
 *   - E_OK: Interrupts successfully initialized.
 *   - E_NOT_OK: An error occurred (e.g., null pointer).
 */
static Std_ReturnType TMR1_Interrupt_Init (const Timer1_t *timer1_obj)
{
	Std_ReturnType ret = E_OK;
	
	if(NULL == timer1_obj)
	{
		ret = E_NOT_OK;
	}
	
	else
	{
		
#if TMR1_CAPTURE_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
		TMR1_Capture_InterruptHandler = timer1_obj->TMR1_Capture_InterruptHandler;
		TMR1_Capture_InterruptEnable();
		TMR1_Capture_InterruptFlagClear();
		INTERRUPT_GlobalInterruptEnable();
#endif

#if TMR1_COMPARE_A_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
		TMR1_CompareA_InterruptHandler = timer1_obj->TMR1_CompareA_InterruptHandler;
		TMR1_CompareA_InterruptEnable();
		TMR1_CompareA_InterruptFlagClear();
		INTERRUPT_GlobalInterruptEnable();
#endif

#if TMR1_COMPARE_B_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
		TMR1_CompareB_InterruptHandler = timer1_obj->TMR1_CompareB_InterruptHandler;
		TMR1_CompareB_InterruptEnable();
		TMR1_CompareB_InterruptFlagClear();
		INTERRUPT_GlobalInterruptEnable();
#endif

#if TMR1_OVERFLOW_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
		TMR1_OverFlow_InterruptHandler = timer1_obj->TMR1_OverFlow_InterruptHandler;
		TMR1_OverFlow_InterruptEnable();
		TMR1_OverFlow_InterruptFlagClear();
		INTERRUPT_GlobalInterruptEnable();
#endif

		ret = E_OK;
	}
	
	return ret;
}





void TMR1_Capture_ISR(void)
{
	TMR1_Capture_InterruptFlagClear();
	
	ICR1H = (capture_value) >> 8;   /* Initialize the capture value value again */
	ICR1L = (uint8)(capture_value); /* Initialize the capture value value again */
	
	if(TMR1_Capture_InterruptHandler)
	{
		TMR1_Capture_InterruptHandler();     /* Call the callback function */
	}
}


void TMR1_CompareA_ISR(void)
{
	TMR1_CompareA_InterruptFlagClear();
	
	OCR1AH = (compareA_value) >> 8;   /* Initialize the compareA value value again */
	OCR1AL = (uint8)(compareA_value); /* Initialize the compareA value value again */
	
	if(TMR1_CompareA_InterruptHandler)
	{
		TMR1_CompareA_InterruptHandler();     /* Call the callback function */
	}
}

void TMR1_CompareB_ISR(void)
{
	TMR1_CompareB_InterruptFlagClear();	
	
	OCR1BH = (compareB_value) >> 8;   /* Initialize the compareB value value again */
	OCR1BL = (uint8)(compareB_value); /* Initialize the compareB value value again */
	
	if(TMR1_CompareB_InterruptHandler)
	{
		TMR1_CompareB_InterruptHandler();     /* Call the callback function */
	}
}

void TMR1_OverFlow_ISR(void)
{
	TMR1_OverFlow_InterruptFlagClear();
	
	//TCNT1H = (timer1_preload) >> 8;   /* Initialize the pre-loaded value again */
	//TCNT1L = (uint8)(timer1_preload); /* Initialize the pre-loaded value again */
	
	if(TMR1_OverFlow_InterruptHandler)
	{
		TMR1_OverFlow_InterruptHandler();     /* Call the callback function */
	}
}