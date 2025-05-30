/*
 * File   :  hal_timer0.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Created: 1/25/2025 3:43:13 PM
 * Author: AhmedShawada
 */ 

#include "hal_timer0.h"

/******* Pointer to function to hold the call-backs for TMR1 *******/
#if TMR0_COMPARE_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static volatile void (*TMR0_Compare_InterruptHandler)(void) = NULL;
#endif

#if TMR0_OVERFLOW_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static volatile void (*TMR0_OverFlow_InterruptHandler)(void) = NULL;
#endif
/*****************************END*************************************/

/***************************Helper_Function***************************/
static Std_ReturnType Timer0_Normal_Mode_Select(const Timer0_t *timer0_obj);
static Std_ReturnType Timer0_CTC_Mode_Select(const Timer0_t *timer0_obj);
static Std_ReturnType Timer0_Fast_PWM_Mode_Select(const Timer0_t *timer0_obj);
static Std_ReturnType TMR0_Interrupt_Init (const Timer0_t *timer0_obj);
/*****************************END*************************************/

static uint8 volatile timer0_preload_value = 0;
static uint8 volatile compare_value = 0;





/**
 * @Summary
 *   Initializes Timer0 with the specified configuration.
 * 
 * @Description
 *   This function configures Timer0 based on the provided settings in the Timer0_t structure.
 *   It handles timer modes, pre-load values, compare values, and interrupt initialization.
 *
 * @Preconditions
 *   - The Timer0_t structure must be properly initialized before calling this function.
 *   - The microcontroller clock source should be configured.
 *
 * @param timer0_obj
 *   A pointer to a Timer0_t structure containing the timer settings.
 *
 * @return 
 *   - E_OK: Timer0 initialized successfully.
 *   - E_NOT_OK: An error occurred (e.g., null pointer).
 */
Std_ReturnType Timer0_Init(const Timer0_t *timer0_obj)
{
	Std_ReturnType ret = E_OK;
	if(NULL == timer0_obj)
	{
		ret =  E_NOT_OK;
	}
	else
	{
		/*  Configure OC0 (PB3) as an output pin */
		pin_config_t output_pin = {	 .port = PORTB_INDEX, .direction = GPIO_DIRECTION_OUTPUT,
									 .logic = GPIO_LOW, .pin = GPIO_PIN3	 };
		
		ret = gpio_pin_direction_intialize(&output_pin);
		
		/* Store pre-load value and load it into the timer */
		timer0_preload_value = timer0_obj->PRELOAD_VALUE;
		TIMER0_Set(timer0_obj->PRELOAD_VALUE);
		
		/* Store compare value and set it in Timer0 */
		TIMER0_SetCompareUnit(timer0_obj->COMPARE_VALUE);
		compare_value = timer0_obj->COMPARE_VALUE;
		
		/* Initialize interrupt if enabled */
		if(TMR0_INTERRUPT_ENABLE == timer0_obj->TIMER0_INTERRUPT)
		{
			ret = TMR0_Interrupt_Init(timer0_obj);
		}
		else{ /* Nothing */ }
			
		/* Select Timer0 mode based on configuration */
		switch(timer0_obj->TIMER_MODE)
		{
			case TIMER0_NORMAL_MODE:
			CLEAR_BIT(TCCR0,FOC0 );                         
			CLEAR_BIT(TCCR0,WGM00 );                       
			CLEAR_BIT(TCCR0,WGM01 );                      
			ret = Timer0_Normal_Mode_Select(timer0_obj);
			break;
			
			case TIMER0_CTC:
			CLEAR_BIT(TCCR0,FOC0);                     
			CLEAR_BIT(TCCR0,WGM00);                   
			SET_BIT(TCCR0,WGM01);                    
			ret = Timer0_CTC_Mode_Select(timer0_obj);
			break;
			
			case TIMER0_FAST_PWM:
			CLEAR_BIT(TCCR0,FOC0);               
			SET_BIT(TCCR0,WGM00);               
			SET_BIT(TCCR0,WGM01);              
			ret = Timer0_Fast_PWM_Mode_Select(timer0_obj);
			break;
			
			default: ret = E_NOT_OK;
		}
	}
	
	/* Set Timer0 pre-scaler */
	TCCR0 &= 0XF8;
	TCCR0 |= timer0_obj->PRESCALER_VALUE;
	
	return ret;
}

/**
 * @Summary
 *   De-initializes Timer0.
 *
 * @Description
 *   Stops Timer0, disables interrupts, and clears the configuration registers.
 *
 * @Preconditions
 *   - Timer0 must have been previously initialized.
 *
 * @param timer0_obj
 *   A pointer to the Timer0_t structure.
 *
 * @return 
 *   - E_OK: Timer0 was successfully de-initialized.
 *   - E_NOT_OK: An error occurred (e.g., null pointer).
 */
Std_ReturnType Timer0_DeInit(const Timer0_t *timer0_obj)
{
	Std_ReturnType ret = E_OK;
	if(NULL == timer0_obj)
	{
		ret =  E_NOT_OK;
	}
	
	else
	{
		/* Stop Timer0 */
		TCCR0 = TIMER0_STOP;
		
		/* Disable interrupts */
#if TMR0_COMPARE_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
		TMR0_Compare_InterruptHandler = timer0_obj->TMR0_Compare_InterruptHandler;
		TMR0_Compare_InterruptDisable();
#endif

#if TMR0_OVERFLOW_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
		TMR0_OverFlow_InterruptHandler = timer0_obj->TMR0_OverFlow_InterruptHandler;
		TMR0_OverFlow_InterruptDisable();
#endif
		
		ret = E_OK;
	}
	return ret;
}


/**
 * @Summary
 *   Sets the duty cycle for Timer0 in PWM mode.
 *
 * @Description
 *   Updates the compare match value to adjust the duty cycle.
 *
 * @Preconditions
 *   - Timer0 must be initialized and running in PWM mode.
 *
 * @param timer0_obj
 *   A pointer to the Timer0_t structure.
 *
 * @param DUTY_VALUE
 *   The new duty cycle value (0-255).
 *
 * @return 
 *   - E_OK: Duty cycle was successfully updated.
 *   - E_NOT_OK: An error occurred (e.g., null pointer).
 */
Std_ReturnType Timer0_Set_Duty(const Timer0_t *timer0_obj, uint8 DUTY_VALUE)
{
	Std_ReturnType ret = E_OK;
	if (NULL == timer0_obj)
	{
		ret = E_NOT_OK;
	}
	
	else
	{
		TIMER0_SetCompareUnit(DUTY_VALUE);
		ret = E_OK;
	}
	
	return ret;
}


/**
 * @Summary
 *   Selects and configures Timer0 in Normal Mode.
 * 
 * @Description
 *   This function sets the Timer0 mode to Normal Mode and configures the output
 *   compare behavior based on the provided settings in the Timer0_t structure.
 *
 * @Preconditions
 *   - Timer0 must be properly initialized before calling this function.
 *   - The microcontroller clock must be configured.
 *
 * @param timer0_obj
 *   Pointer to a Timer0_t structure that contains the mode configuration.
 *   - COMPARE_MODE: Determines how the OC0 pin behaves on a compare match.
 *
 * @return 
 *   - E_OK: Timer0 was successfully configured in Normal Mode.
 *   - E_NOT_OK: An error occurred (e.g., null pointer).
 */
static Std_ReturnType Timer0_Normal_Mode_Select(const Timer0_t *timer0_obj)
{
	
	Std_ReturnType ret = E_OK;
	if (NULL == timer0_obj)
	{ 
		ret = E_NOT_OK;
	}
	
	else
	{
		switch (timer0_obj->COMPARE_MODE) 
		{
			case NORMAL_COMPARE_MODE:
			CLEAR_BIT(TCCR0, COM00); 
			CLEAR_BIT(TCCR0, COM01); 
			break;
			
			case TOGGLE_COMPARE_BIT_MODE:
			SET_BIT(TCCR0, COM00); 
			CLEAR_BIT(TCCR0, COM01); 
			break;
			
			case CLEAR_COMPARE_BIT_MODE:
			CLEAR_BIT(TCCR0, COM00); 
			SET_BIT(TCCR0, COM01); 
			break;
			
			case SET_COMPARE_BIT_MODE:
			SET_BIT(TCCR0, COM00); 
			SET_BIT(TCCR0, COM01); 
			break;
			
			default: ret = E_NOT_OK;
		}
	}

	return ret;
}


/**
 * @Summary
 *   Selects and configures Timer0 in CTC Mode.
 * 
 * @Description
 *   This function sets the Timer0 mode to CTC (Clear Timer on Compare Match) 
 *   and configures the output compare behavior based on the provided settings.
 *
 * @Preconditions
 *   - Timer0 must be properly initialized before calling this function.
 *   - The microcontroller clock must be configured.
 *
 * @param timer0_obj
 *   Pointer to a Timer0_t structure that contains the mode configuration.
 *   - COMPARE_MODE: Determines how the OC0 pin behaves on a compare match.
 *
 * @return 
 *   - E_OK: Timer0 was successfully configured in CTC Mode.
 *   - E_NOT_OK: An error occurred (e.g., null pointer).
 */
static Std_ReturnType Timer0_CTC_Mode_Select(const Timer0_t *timer0_obj)
{
	Std_ReturnType ret = E_OK;
	
	if (NULL == timer0_obj)
	{
		ret = E_NOT_OK;
	} 
	
	else
	{
		switch (timer0_obj->COMPARE_MODE)
		{
			case NORMAL_COMPARE_MODE:
			CLEAR_BIT(TCCR0, COM00); 
			CLEAR_BIT(TCCR0, COM01); 
			break;
			case TOGGLE_COMPARE_BIT_MODE:
			SET_BIT(TCCR0, COM00); 
			CLEAR_BIT(TCCR0, COM01); 
			break;
			case CLEAR_COMPARE_BIT_MODE:
			CLEAR_BIT(TCCR0, COM00); 
			SET_BIT(TCCR0, COM01); 
			break;
			case SET_COMPARE_BIT_MODE:
			SET_BIT(TCCR0, COM00); 
			SET_BIT(TCCR0, COM01); 
			break;
			default: ret = E_NOT_OK;
		}
	}

	return ret;
}

/**
 * @Summary
 *   Selects and configures Timer0 in Fast PWM Mode.
 * 
 * @Description
 *   This function sets Timer0 to Fast PWM Mode and configures the PWM output
 *   behavior based on the provided settings in the Timer0_t structure.
 *
 * @Preconditions
 *   - Timer0 must be properly initialized before calling this function.
 *   - The microcontroller clock must be configured.
 *
 * @param timer0_obj
 *   Pointer to a Timer0_t structure that contains the mode configuration.
 *   - PWM_MODE: Determines the PWM output behavior (e.g., Inverting, Non-Inverting).
 *
 * @return 
 *   - E_OK: Timer0 was successfully configured in Fast PWM Mode.
 *   - E_NOT_OK: An error occurred (e.g., null pointer).
 */
static Std_ReturnType Timer0_Fast_PWM_Mode_Select(const Timer0_t *timer0_obj)
{

	Std_ReturnType ret = E_OK;
	
	if (NULL == timer0_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		switch (timer0_obj->PWM_MODE)
		{
			case FAST_PWM_DISCONNECTED:
			CLEAR_BIT(TCCR0, COM00); 
			CLEAR_BIT(TCCR0, COM01); 
			break;
			
			case FAST_PWM_NON_INVERTING:
			CLEAR_BIT(TCCR0, COM00); 
			SET_BIT(TCCR0, COM01); 
			break;
			
			case FAST_PWM_INVERTING:
			SET_BIT(TCCR0, COM00); 
			SET_BIT(TCCR0, COM01); 
			break;
			
			default: ret = E_NOT_OK;

		}
	}
	return ret;
}


/**
 * @Summary
 *   Initializes Timer0 interrupts.
 * 
 * @Description
 *   This static function enables Timer0-related interrupts (compare, overflow)
 *	 if they are enabled in the configuration.
 *
 * @Preconditions
 *   - Timer0 must be initialized.
 *   - Interrupt handlers should be properly assigned in the configuration object.
 * 
 * @param timer1_obj
 *   A pointer to a Timer0_t structure containing the interrupt configuration:
 *     - TMR0_Compare_InterruptHandler: Function pointer for compare  interrupt.
 *     - TMR0_OverFlow_InterruptHandler: Function pointer for overflow interrupt.
 * 
 * @return 
 *   - E_OK: Interrupts successfully initialized.
 *   - E_NOT_OK: An error occurred (e.g., null pointer).
 */
static Std_ReturnType TMR0_Interrupt_Init (const Timer0_t *timer0_obj)
{
	
	Std_ReturnType ret = E_OK;
	
	if(NULL == timer0_obj)
	{
		ret = E_NOT_OK;
	}
	
	else
	{
#if TMR0_COMPARE_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
		TMR0_Compare_InterruptHandler = timer0_obj->TMR0_Compare_InterruptHandler;
		TMR0_Compare_InterruptEnable();
		TMR0_Compare_InterruptFlagClear();
		INTERRUPT_GlobalInterruptEnable();
#endif

#if TMR0_OVERFLOW_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
		TMR0_OverFlow_InterruptHandler = timer0_obj->TMR0_OverFlow_InterruptHandler;
		TMR0_OverFlow_InterruptEnable();
		TMR0_OverFlow_InterruptFlagClear();
		INTERRUPT_GlobalInterruptEnable();
#endif

		ret = E_OK;
	}
	return ret;
}


void TMR0_Compare_ISR(void)
{
	TMR0_Compare_InterruptFlagClear();
	
	//TIMER0_SetCompareUnit(compare_value) /* Initialize the compare value again */
	
	if(TMR0_Compare_InterruptHandler)
	{
		TMR0_Compare_InterruptHandler();     /* Call the callback function */
	}
}


void TMR0_OverFlow_ISR(void)
{
	TMR0_OverFlow_InterruptFlagClear();
	
	TIMER0_Set(timer0_preload_value);  /* Initialize the pre-loaded value again */
	
	if(TMR0_OverFlow_InterruptHandler)
	{
		TMR0_OverFlow_InterruptHandler();     /* Call the callback function */
	}
}