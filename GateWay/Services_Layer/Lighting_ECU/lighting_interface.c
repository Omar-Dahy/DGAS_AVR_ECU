/*
 * lighting_interface.c
 * 
 * Created: 1/27/2025 12:54:42 PM
 * Author: DGAS
 */ 

#include "lighting_interface.h"

static OCR1A_COMPARE_MODE_T oc1a_cmode = OCR1A_no_value;
static OCR1B_COMPARE_MODE_T oc1b_cmode = OCR1B_no_value;

/*************** FLR ----> Front Light Right ***************/
static led_t Led_FLR = {.port_name = PORTC_INDEX, .pin = GPIO_PIN3, .led_status = GPIO_LOW};

/*************** FLL ----> Front Light Left ***************/
static led_t Led_FLL = {.port_name = PORTC_INDEX, .pin = GPIO_PIN2, .led_status = GPIO_LOW};

///*************** BLA ----> Break Light All ***************/
//static led_t Led_BLA = {.port_name = PORTD_INDEX, .pin = GPIO_PIN7, .led_status = GPIO_HIGH};
//
///*************** HLR ----> Hazard Light Right ***************/
//static led_t Led_HLR = {.port_name = PORTD_INDEX, .pin = GPIO_PIN5, .led_status = GPIO_LOW};
//
///*************** HLL ----> Hazard Light Left ***************/
//static led_t Led_HLL = {.port_name = PORTD_INDEX, .pin = GPIO_PIN4, .led_status = GPIO_LOW};
	
	
	
/**
 * @Summary
 * Initializes the lighting services for the ECU by setting up the LED configurations 
 * for front lights, brake lights, and hazard lights.
 * 
 * @Description
 * This function initializes multiple LEDs representing the lighting system of the ECU.
 * It defines their ports, pins, and default states, then calls the `led_intialize` 
 * function to configure each LED. The function returns a status indicating whether the 
 * initialization was successful or not.
 * 
 * @Preconditions
 * - The MCU GPIO ports must be properly configured before calling this function.
 * - The `led_intialize` function should be implemented and correctly handle initialization.
 * 
 * @param None
 * 
 * @return Std_ReturnType
 * - `E_OK`: If all LEDs are initialized successfully.
 * - `E_NOT_OK`: If there is an error initializing any LED.
 */
Std_ReturnType Lighting_Services_Initialize(void)
{
	Std_ReturnType ret = E_OK;
	
	/*************** Initialize Front Light Right ***************/	
	ret = led_intialize(&Led_FLR);
	/*************** Initialize Front Light Left ***************/	 
	ret = led_intialize(&Led_FLL);
	/*************** Initialize Break Light All ***************/
	//ret = led_intialize(&Led_BLA);
	///*************** Initialize Hazard Light Right ***************/
	//ret = led_intialize(&Led_HLR);
	///*************** Initialize Hazard Light Left ***************/
	//ret = led_intialize(&Led_HLL);	
	
	return ret;
}



Std_ReturnType Front_Light_Right_ON(void)
{
	Std_ReturnType ret = E_OK;
	
	ret = led_turn_on(&Led_FLR);
	
	return ret;
}


Std_ReturnType Front_Light_Right_OFF(void)
{
	Std_ReturnType ret = E_OK;
	
	ret = led_turn_off(&Led_FLR);
	
	return ret;
}


Std_ReturnType Front_Light_Left_ON(void)
{
	Std_ReturnType ret = E_OK;
	
	ret = led_turn_on(&Led_FLL);
	
	return ret;
	
}


Std_ReturnType Front_Light_Left_OFF(void)
{
	Std_ReturnType ret = E_OK;
	
	ret = led_turn_off(&Led_FLL);
	
	return ret;
}


Std_ReturnType Front_Light_ALL_ON(void)
{
	Std_ReturnType ret = E_OK;
	
	ret = led_turn_on(&Led_FLR);
	ret = led_turn_on(&Led_FLL);
	
	return ret;
}


Std_ReturnType Front_Light_ALL_OFF(void)
{
	Std_ReturnType ret = E_OK;
	
	ret = led_turn_off(&Led_FLR);
	ret = led_turn_off(&Led_FLL);
	
	return ret;
}

Std_ReturnType Break_Light_Defult(void)
{
	Std_ReturnType ret = E_OK;
	
	Timer0_t timer0_config =
	{
		.COMPARE_VALUE = 0x00,
		.PRELOAD_VALUE = 0,
		.PRESCALER_VALUE = TIMER0_SCALER_256,
		.PWM_MODE = FAST_PWM_NON_INVERTING,
		.TIMER_MODE = TIMER0_FAST_PWM,
		.TIMER0_INTERRUPT = TMR0_INTERRUPT_DISABLE,
		.TMR0_Compare_InterruptHandler = NULL,
		.TMR0_OverFlow_InterruptHandler = NULL
	};
	ret = Timer0_Init(&timer0_config);
	/* Set duty cycle to 50% (0x80) */
	ret = Timer0_Set_Duty(&timer0_config , 0x80);
	
	return ret;
}


Std_ReturnType Break_Light_Full(void)
{
	Std_ReturnType ret = E_OK;
	
	Timer0_t timer0_config =
	{
		.COMPARE_VALUE = 0x00,
		.PRELOAD_VALUE = 0,
		.PRESCALER_VALUE = TIMER0_SCALER_256,
		.PWM_MODE = FAST_PWM_NON_INVERTING,
		.TIMER_MODE = TIMER0_FAST_PWM,
		.TIMER0_INTERRUPT = TMR0_INTERRUPT_DISABLE,
		.TMR0_Compare_InterruptHandler = NULL,
		.TMR0_OverFlow_InterruptHandler = NULL
	};
	ret = Timer0_Init(&timer0_config);
	/* Set duty cycle to 100% (0xFF) */
	ret = Timer0_Set_Duty(&timer0_config , 0xFF);
	
	return ret;
}


Std_ReturnType Hazard_Light_Right_ON(void)
{
	Std_ReturnType ret = E_OK;
	/*
	oc1a_cmode = OCR1A_no_value;
	oc1b_cmode = OCR1B_no_value;
	*/
	oc1a_cmode = OCR1A_TOGGLE_COMPARE_BIT_MODE;
	
	Timer1_t Hazard_Right_1HZ_ON =
	{
		.COMPARE_VALUE_A = 0x7A12,
		.COMPARE_VALUE_B = 0x7A12,
		.PRESCALER_VALUE = TIMER1_SCALER_256,
		.EDGE = RISING,
		.TIMER_MODE = TIMER1_CTC_OCRA_TOP_MODE,
		.OC1A_CMode = oc1a_cmode ,
		.OC1B_CMode = oc1b_cmode ,
		
		.NOISE_CANCLER = NOISE_CANCLER_OFF,
		.TIMER1_INTERRUPT = TMR1_INTERRUPT_DISABLE,
		.OC1B_PMode = OCR1B_FAST_PWM_DISCONNECTED ,
		.OC1A_PMode = OCR1A_FAST_PWM_DISCONNECTED ,
		.TMR1_Capture_InterruptHandler = NULL,
		.TMR1_CompareA_InterruptHandler = NULL,
		.TMR1_CompareB_InterruptHandler = NULL,
		.TMR1_OverFlow_InterruptHandler = NULL
	};
	
	ret = Timer1_Init(&Hazard_Right_1HZ_ON);
	
	
	return ret;
}


Std_ReturnType Hazard_Light_Right_OFF(void)
{
	Std_ReturnType ret = E_OK;
	
	oc1a_cmode = OCR1A_NORMAL_COMPARE_MODE;
	
	Timer1_t Hazard_Right_1HZ_OFF =
	{
		.COMPARE_VALUE_A = 0x0000,
		.COMPARE_VALUE_B = 0x0000,
		.PRESCALER_VALUE = TIMER1_SCALER_256,
		.EDGE = RISING,
		.TIMER_MODE = TIMER1_CTC_OCRA_TOP_MODE,
		.OC1A_CMode = oc1a_cmode ,
		.OC1B_CMode = oc1b_cmode ,
		.OC1A_PMode = OCR1A_FAST_PWM_DISCONNECTED ,
		.OC1B_PMode = OCR1B_FAST_PWM_DISCONNECTED ,
		.NOISE_CANCLER = NOISE_CANCLER_OFF,
		.TIMER1_INTERRUPT = TMR1_INTERRUPT_DISABLE,
		.TMR1_Capture_InterruptHandler = NULL,
		.TMR1_CompareA_InterruptHandler = NULL,
		.TMR1_CompareB_InterruptHandler = NULL,
		.TMR1_OverFlow_InterruptHandler = NULL
	};
	
	ret = Timer1_Init(&Hazard_Right_1HZ_OFF);
	oc1a_cmode = OCR1A_no_value;
		
	return ret;
}


Std_ReturnType Hazard_Light_Left_ON(void)
{
	Std_ReturnType ret = E_OK;
	/*
	oc1a_cmode = OCR1A_TOGGLE_COMPARE_BIT_MODE;
	oc1b_cmode = OCR1B_no_value;
	*/
	oc1b_cmode = OCR1B_TOGGLE_COMPARE_BIT_MODE;
	Timer1_t Hazard_Left_1HZ_ON =
	{
		.COMPARE_VALUE_A = 0x7A12,
		.COMPARE_VALUE_B = 0x7A12,
		.PRESCALER_VALUE = TIMER1_SCALER_256,
		.EDGE = RISING,
		.TIMER_MODE = TIMER1_CTC_OCRA_TOP_MODE,
		.OC1A_CMode = oc1a_cmode,
		.OC1A_PMode = OCR1A_FAST_PWM_DISCONNECTED ,
		.OC1B_CMode = oc1b_cmode,
		.OC1B_PMode = OCR1B_FAST_PWM_DISCONNECTED ,
		.NOISE_CANCLER = NOISE_CANCLER_OFF,
		.TIMER1_INTERRUPT = TMR1_INTERRUPT_DISABLE,
		.TMR1_Capture_InterruptHandler = NULL,
		.TMR1_CompareA_InterruptHandler = NULL,
		.TMR1_CompareB_InterruptHandler = NULL,
		.TMR1_OverFlow_InterruptHandler = NULL
	};
	
	ret = Timer1_Init(&Hazard_Left_1HZ_ON);
		
	return ret;
}


Std_ReturnType Hazard_Light_Left_OFF(void)
{
	Std_ReturnType ret = E_OK;
	
	oc1b_cmode = OCR1B_NORMAL_COMPARE_MODE;
	Timer1_t Hazard_Left_1HZ_OFF =
	{
		.COMPARE_VALUE_A = 0x0000,
		.COMPARE_VALUE_B = 0x0000,
		.PRESCALER_VALUE = TIMER1_SCALER_256,
		.EDGE = RISING,
		.TIMER_MODE = TIMER1_CTC_OCRA_TOP_MODE,
		.OC1A_CMode = oc1a_cmode ,
		.OC1B_CMode = oc1b_cmode ,
		.OC1A_PMode = OCR1A_FAST_PWM_DISCONNECTED ,
		.OC1B_PMode = OCR1B_FAST_PWM_DISCONNECTED ,
		.NOISE_CANCLER = NOISE_CANCLER_OFF,
		.TIMER1_INTERRUPT = TMR1_INTERRUPT_DISABLE,
		.TMR1_Capture_InterruptHandler = NULL,
		.TMR1_CompareA_InterruptHandler = NULL,
		.TMR1_CompareB_InterruptHandler = NULL,
		.TMR1_OverFlow_InterruptHandler = NULL
	};
	
	ret = Timer1_Init(&Hazard_Left_1HZ_OFF);
	oc1b_cmode = OCR1B_no_value;
	
	return ret;
}


Std_ReturnType Hazard_Light_ALL_ON(void)
{
	Std_ReturnType ret = E_OK;
	
	oc1a_cmode = OCR1A_TOGGLE_COMPARE_BIT_MODE;
	oc1b_cmode = OCR1B_TOGGLE_COMPARE_BIT_MODE;
	
	Timer1_t Hazard_ALL_1HZ_ON =
	{
		.COMPARE_VALUE_A = 0x7A12,
		.COMPARE_VALUE_B = 0x7A12,
		.PRESCALER_VALUE = TIMER1_SCALER_256,
		.EDGE = RISING,
		.TIMER_MODE = TIMER1_CTC_OCRA_TOP_MODE,
		.OC1A_CMode = oc1a_cmode ,
		.OC1A_PMode = OCR1A_FAST_PWM_DISCONNECTED ,
		.OC1B_CMode = oc1b_cmode ,
		.OC1B_PMode = OCR1B_FAST_PWM_DISCONNECTED ,
		.NOISE_CANCLER = NOISE_CANCLER_OFF,
		.TIMER1_INTERRUPT = TMR1_INTERRUPT_DISABLE,
		.TMR1_Capture_InterruptHandler = NULL,
		.TMR1_CompareA_InterruptHandler = NULL,
		.TMR1_CompareB_InterruptHandler = NULL,
		.TMR1_OverFlow_InterruptHandler = NULL
	};
	
	ret = Timer1_Init(&Hazard_ALL_1HZ_ON);
	
	return ret;
}


Std_ReturnType Hazard_Light_ALL_OFF(void)
{
	Std_ReturnType ret = E_OK;
	
	oc1a_cmode = OCR1A_NORMAL_COMPARE_MODE;
	oc1b_cmode = OCR1B_NORMAL_COMPARE_MODE;
	
	Timer1_t Hazard_ALL_1HZ_OFF =
	{
		.COMPARE_VALUE_A = 0,
		.COMPARE_VALUE_B = 0,
		.PRESCALER_VALUE = TIMER1_SCALER_256,
		.EDGE = RISING,
		.TIMER_MODE = TIMER1_CTC_OCRA_TOP_MODE,
		.OC1A_CMode = oc1a_cmode ,
		.OC1A_PMode = OCR1A_FAST_PWM_DISCONNECTED ,
		.OC1B_CMode = oc1b_cmode ,
		.OC1B_PMode = OCR1B_FAST_PWM_DISCONNECTED ,
		.NOISE_CANCLER = NOISE_CANCLER_OFF,
		.TIMER1_INTERRUPT = TMR1_INTERRUPT_DISABLE,
		.TMR1_Capture_InterruptHandler = NULL,
		.TMR1_CompareA_InterruptHandler = NULL,
		.TMR1_CompareB_InterruptHandler = NULL,
		.TMR1_OverFlow_InterruptHandler = NULL
	};
	
	ret = Timer1_Init(&Hazard_ALL_1HZ_OFF);
	
	oc1a_cmode = OCR1A_no_value;
	oc1b_cmode = OCR1B_no_value;
	
	return ret;
}

Std_ReturnType Hazard_Light_Emergancy_ON(void)
{
	Std_ReturnType ret = E_OK;
	
	oc1a_cmode = OCR1A_TOGGLE_COMPARE_BIT_MODE;
	oc1b_cmode = OCR1B_TOGGLE_COMPARE_BIT_MODE;
	
	Timer1_t Hazard_Emergancy_5HZ_ON =
	{
		.COMPARE_VALUE_A = 0x61A8,
		.COMPARE_VALUE_B = 0x61A8,
		.PRESCALER_VALUE = TIMER1_SCALER_64,
		.EDGE = RISING,
		.TIMER_MODE = TIMER1_CTC_OCRA_TOP_MODE,
		.OC1A_CMode = oc1a_cmode ,
		.OC1A_PMode = OCR1A_FAST_PWM_DISCONNECTED ,
		.OC1B_CMode = oc1b_cmode ,
		.OC1B_PMode = OCR1B_FAST_PWM_DISCONNECTED ,
		.NOISE_CANCLER = NOISE_CANCLER_OFF,
		.TIMER1_INTERRUPT = TMR1_INTERRUPT_DISABLE,
		.TMR1_Capture_InterruptHandler = NULL,
		.TMR1_CompareA_InterruptHandler = NULL,
		.TMR1_CompareB_InterruptHandler = NULL,
		.TMR1_OverFlow_InterruptHandler = NULL
	};
	
	ret = Timer1_Init(&Hazard_Emergancy_5HZ_ON);
		
	return ret;
}


Std_ReturnType Hazard_Light_Emergancy_OFF(void)
{
	Std_ReturnType ret = E_OK;
	
	oc1a_cmode = OCR1A_NORMAL_COMPARE_MODE;
	oc1b_cmode = OCR1B_NORMAL_COMPARE_MODE;
	
	Timer1_t Hazard_Emergancy_5HZ_OFF =
	{
		.COMPARE_VALUE_A = 0,
		.COMPARE_VALUE_B = 0,
		.PRESCALER_VALUE = TIMER1_SCALER_64,
		.EDGE = RISING,
		.TIMER_MODE = TIMER1_CTC_OCRA_TOP_MODE,
		.OC1A_CMode = oc1a_cmode ,
		.OC1A_PMode = OCR1A_FAST_PWM_DISCONNECTED ,
		.OC1B_CMode = oc1b_cmode ,
		.OC1B_PMode = OCR1B_FAST_PWM_DISCONNECTED ,
		.NOISE_CANCLER = NOISE_CANCLER_OFF,
		.TIMER1_INTERRUPT = TMR1_INTERRUPT_DISABLE,
		.TMR1_Capture_InterruptHandler = NULL,
		.TMR1_CompareA_InterruptHandler = NULL,
		.TMR1_CompareB_InterruptHandler = NULL,
		.TMR1_OverFlow_InterruptHandler = NULL
	};
	
	ret = Timer1_Init(&Hazard_Emergancy_5HZ_OFF);
	
	oc1a_cmode = OCR1A_no_value;
	oc1b_cmode = OCR1B_no_value;
		
	return ret;
}