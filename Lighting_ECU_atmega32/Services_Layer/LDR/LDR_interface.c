/*
 * LDR_interface.c
 * 
 * Created: 1/27/2025 6:38:10 PM
 *  Author: DGAS Team
 */ 

#include "LDR_interface.h"

/* Static Functions Area */
static Std_ReturnType dynamic_threshold_read();


/* Static variables to store LDR readings for averaging */
static uint16 LDR1_Store[5];    // Array to store readings from LDR1 
static uint16 LDR2_Store[5];    // Array to store readings from LDR2
static uint16 LDR3_Store[5];    // Array to store readings from LDR3
static uint16 LDR4_Store[5];    // Array to store readings from LDR4

/* Static variables to store the summed LDR readings */
static uint16 LDR1_SUM;		    // Sum of readings for LDR1
static uint16 LDR2_SUM;		    // Sum of readings for LDR2
static uint16 LDR3_SUM;		    // Sum of readings for LDR3
static uint16 LDR4_SUM;		    // Sum of readings for LDR4

/* Static variable to store the total sum of all LDRs */ 
static volatile uint16 LDRs_SUM;		    // Sum of all LDR average readings

static volatile uint16 dynamic_threshold;

static volatile uint16 threshold_flag = 0;
/* Static Variables to store individual LDR readings */
static uint16 LDR1_res_1;		// Latest reading from LDR1
static uint16 LDR2_res_2;		// Latest reading from LDR2
static uint16 LDR3_res_3;		// Latest reading from LDR3
static uint16 LDR4_res_4;		// Latest reading from LDR4

/* Counters for each LDR reading */ 
static uint8 LDR1_Counter;		// Counter for LDR1 readings
static uint8 LDR2_Counter;		// Counter for LDR2 readings
static uint8 LDR3_Counter;		// Counter for LDR3 readings
static uint8 LDR4_Counter;		// Counter for LDR4 readings

static uint32 temp_ldr_01=0;

/* ADC configuration for LDR1 (Analog Channel 0) */
static adc_conf_t LDR_1 =
{
	.adc_channel = ADC_CHANNEL_AN0,							// ADC Channel for LDR1
	.conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_128,  // Clock division for ADC
	.result_format = ADC_RESULT_RIGHT,						// Right-aligned result
	.voltage_reference = AVCC_WITH_EXTERNAL_CAPACITOR		// Voltage reference setting
};

/* ADC configuration for LDR2 (Analog Channel 1) */
static adc_conf_t LDR_2 =
{
	.adc_channel = ADC_CHANNEL_AN1,							// ADC Channel for LDR2
	.conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_128,  // Clock division for ADC
	.result_format = ADC_RESULT_RIGHT,						// Right-aligned result
	.voltage_reference = AVCC_WITH_EXTERNAL_CAPACITOR		// Voltage reference setting
};

/* ADC configuration for LDR3 (Analog Channel 2) */
static adc_conf_t LDR_3 =
{
	.adc_channel = ADC_CHANNEL_AN2,							// ADC Channel for LDR3
	.conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_128,  // Clock division for ADC
	.result_format = ADC_RESULT_RIGHT,						// Right-aligned result
	.voltage_reference = AVCC_WITH_EXTERNAL_CAPACITOR		// Voltage reference setting
};

/* ADC configuration for LDR4 (Analog Channel 3) */
static adc_conf_t LDR_4 =
{
	.adc_channel = ADC_CHANNEL_AN3,							// ADC Channel for LDR4
	.conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_128,  // Clock division for ADC
	.result_format = ADC_RESULT_RIGHT,						// Right-aligned result
	.voltage_reference = AVCC_WITH_EXTERNAL_CAPACITOR		// Voltage reference setting
};


static adc_conf_t Potentiometer =
{
	.adc_channel = ADC_CHANNEL_AN4,							// ADC Channel for Potentiometer
	.conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_128,  // Clock division for ADC
	.result_format = ADC_RESULT_RIGHT,						// Right-aligned result
	.voltage_reference = AVCC_WITH_EXTERNAL_CAPACITOR		// Voltage reference setting
};





/**
 * @brief Initialize the LDR sensors.
 * 
 * @details This function initializes all four LDR sensors by configuring the ADC settings for each one.
 * It ensures that the ADC channels are correctly set up for each LDR sensor before reading.
 * 
 * @return E_OK if initialization is successful, otherwise an error code.
 */
Std_ReturnType LDR_Services_Initialize(void){
	
	Std_ReturnType ret = E_OK;
	
	/* Initialize each LDR with the appropriate configuration */ 
	ret = ADC_Init(&LDR_1);
	ret = ADC_Init(&LDR_2);
	ret = ADC_Init(&LDR_3);
	ret = ADC_Init(&LDR_4);
	/* Initialize each Potentiometer with the appropriate configuration */ 
	ret = ADC_Init(&Potentiometer);
	
	return ret;
}





/**
 * @brief Read LDR1 sensor.
 * 
 * @details This function reads the value from LDR1 five times, averages the readings, 
 * and stores the result in LDR1_SUM.
 * 
 * @return E_OK if reading is successful, otherwise an error code.
 */
Std_ReturnType LDR1_Read (void)
{
	Std_ReturnType ret = E_OK;
	
	/* Loop to take 5 readings for LDR1 */ 
	for (LDR1_Counter = 0; LDR1_Counter < 5; LDR1_Counter++)
	{
		/* Perform ADC conversion for LDR1 and store the result */ 
		ret = ADC_GetConversion_Blocking(&LDR_1,ADC_CHANNEL_AN0,&LDR1_res_1);
		/* Store the reading */ 
		LDR1_Store[LDR1_Counter] = LDR1_res_1;
		//temp_ldr_01 += LDR1_res_1;
		_delay_ms(100);
		
	}
	/* Calculate the average of the 5 readings */ 
	LDR1_SUM = (LDR1_Store[0] + LDR1_Store[1] + LDR1_Store[2] + LDR1_Store[3] + LDR1_Store[4]) / 5;
	//temp_ldr_01 /= 5;
	return ret;
}



/**
 * @brief Read LDR2 sensor.
 * 
 * @details This function reads the value from LDR2 five times, averages the readings, 
 * and stores the result in LDR2_SUM.
 * 
 * @return E_OK if reading is successful, otherwise an error code.
 */
Std_ReturnType LDR2_Read (void)
{
	Std_ReturnType ret = E_OK;
	
	/* Loop to take 5 readings for LDR2 */ 
	for (LDR2_Counter = 0; LDR2_Counter < 5; LDR2_Counter++)
	{
		/* Perform ADC conversion for LDR2 and store the result */ 
		ret = ADC_GetConversion_Blocking(&LDR_2,ADC_CHANNEL_AN1,&LDR2_res_2);
		/* Store the reading */ 
		LDR2_Store[LDR2_Counter] = LDR2_res_2;
		
		_delay_ms(100);
		
	}
	/* Calculate the average of the 5 readings */ 
	LDR2_SUM = (LDR2_Store[0] + LDR2_Store[1] + LDR2_Store[2] + LDR2_Store[3] + LDR2_Store[4]) / 5;
	
	return ret;
}



/**
 * @brief Read LDR3 sensor.
 * 
 * @details This function reads the value from LDR3 five times, averages the readings, 
 * and stores the result in LDR3_SUM.
 * 
 * @return E_OK if reading is successful, otherwise an error code.
 */
Std_ReturnType LDR3_Read (void)
{
	Std_ReturnType ret = E_OK;
	
	/* Loop to take 5 readings for LDR3 */ 
	for (LDR3_Counter = 0; LDR3_Counter < 5; LDR3_Counter++)
	{
		/* Perform ADC conversion for LDR3 and store the result */ 
		ret = ADC_GetConversion_Blocking(&LDR_2,ADC_CHANNEL_AN2,&LDR3_res_3);
		/* Store the reading */ 
		LDR3_Store[LDR3_Counter] = LDR3_res_3;
		
		_delay_ms(100);
		
	}
	/* Calculate the average of the 5 readings */ 
	LDR3_SUM = (LDR3_Store[0] + LDR3_Store[1] + LDR3_Store[2] + LDR3_Store[3] + LDR3_Store[4]) / 5;
	
	return ret;
}



/**
 * @brief Read LDR4 sensor.
 * 
 * @details This function reads the value from LDR4 five times, averages the readings, 
 * and stores the result in LDR4_SUM.
 * 
 * @return E_OK if reading is successful, otherwise an error code.
 */
Std_ReturnType LDR4_Read (void)
{
	Std_ReturnType ret = E_OK;
	
	/* Loop to take 5 readings for LDR4 */ 
	for (LDR4_Counter = 0; LDR4_Counter < 5; LDR4_Counter++)
	{
		/* Perform ADC conversion for LDR4 and store the result */ 
		ret = ADC_GetConversion_Blocking(&LDR_2,ADC_CHANNEL_AN3,&LDR4_res_4);
		/* Store the reading */ 
		LDR4_Store[LDR4_Counter] = LDR4_res_4;
		
		_delay_ms(100);
		
	}
	/* Calculate the average of the 5 readings */ 
	LDR4_SUM = (LDR4_Store[0] + LDR4_Store[1] + LDR4_Store[2] + LDR4_Store[3] + LDR4_Store[4]) / 5;
	
	return ret;
}



/**
 * @brief Automate the LDR sensor readings and control the front lights.
 * 
 * @details This function calculates the average of all LDRs' readings. If the average 
 * is below a reference threshold, it turns on the front lights; otherwise, it turns them off.
 * 
 * @return E_OK if automation is successful, otherwise an error code.
 */
Std_ReturnType LDRS_Automation (void)
{
	Std_ReturnType ret = E_OK;
	
	ret = dynamic_threshold_read();
	
	ret = LDR1_Read();
	ret = LDR2_Read();
	ret = LDR3_Read();
	ret = LDR4_Read();
	/* Calculate the average of all LDR sums 450 */ 
	LDRs_SUM = ((LDR1_SUM + LDR2_SUM + LDR3_SUM + LDR4_SUM) / 4);
	
	/* Check if the average LDR value is below the reference value */ 
	if(LDRs_SUM <= dynamic_threshold){
		/* If it's below the reference, turn on the front lights */ 
		ret = Front_Light_ALL_ON();
	}
	else{
		/* If it's above the reference, turn off the front lights */ 
		ret = Front_Light_ALL_OFF();
	}
	
	return ret;
}

static Std_ReturnType dynamic_threshold_read(){
	Std_ReturnType ret = E_OK;
	if(0 == threshold_flag){
		uint8 L_Counter;
		volatile uint16 temp_threshold = 0;
		/* Loop to take 5 readings for LDR4 */
		for (L_Counter = 0; L_Counter < 5; L_Counter++)
		{
			/* Perform ADC conversion for LDR4 and store the result */
			ret = ADC_GetConversion_Blocking(&Potentiometer , ADC_CHANNEL_AN4 , &dynamic_threshold);
			/* Store the reading */
			temp_threshold = temp_threshold + dynamic_threshold;
			_delay_ms(100);
		
		}
		/* Calculate the average of the 5 readings */
		dynamic_threshold = (float)temp_threshold / 5.0 ;
	}
	else{
		ret = E_NOT_OK;
	}
		
	return ret;
}

Std_ReturnType dynamic_threshold_write(uint16 new_dynamic_threshold){
	Std_ReturnType ret = E_OK;
	if((new_dynamic_threshold > 1001) || (new_dynamic_threshold < 0)){
		ret = E_NOT_OK;
	}
	else{
		threshold_flag = 1;
		dynamic_threshold = new_dynamic_threshold;
	}
	
	return ret;
}