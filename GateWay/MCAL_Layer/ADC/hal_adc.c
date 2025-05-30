/*
 * File   :  hal_adc.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Created: 12/11/2024 4:58:54 AM
 * Author: AhmedShawada
 */ 

#include "hal_adc.h"

#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void(*ADC_InterruptHandler)(void) = NULL;
#endif

static inline void ADC_input_channel_port_configure(adc_channel_select_t channel);
static inline void Channel_Configuration (adc_channel_select_t channel);
static inline void Select_Result_Format(const adc_conf_t *_adc);
static inline void Configure_Voltage_Reference(const adc_conf_t *_adc);
static inline void Configure_Conversion_Clock(const adc_conf_t *_adc);




/**
 * @Summary Initializes the ADC
 * @Description This routine initializes the ADC.
 *              This routine must be called before any other ADC routine is called.
 *              This routine should only be called once during system initialization.
 * @Preconditions None
 * @param _adc Pointer to the ADC configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_Init(const adc_conf_t *_adc)
{
	Std_ReturnType ret = E_OK;
	
	if (NULL == _adc)
	{
		ret = E_NOT_OK;
	} 
	
	else
	{
		/* Disable the ADC */
		ADC_CONVERTER_DISABLE();
		
		/*Configure the Conversion Clock*/
		Configure_Conversion_Clock(_adc);
		
		/* Configure the default channel */
		Channel_Configuration(_adc->adc_channel);
		ADC_input_channel_port_configure(_adc->adc_channel);
		/* Configure the interrupt */
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
		ADC_InterruptEnable();
		ADC_InterruptFlagClear();
		INTERRUPT_GlobalInterruptEnable();
		ADC_InterruptHandler = _adc->ADC_InterruptHandler;
#endif
	
		/* Configure the result format */
		Select_Result_Format(_adc);
		
		/* Configure the voltage reference */
		Configure_Voltage_Reference(_adc);
		
		/*Enable the ADC*/
		ADC_CONVERTER_ENABLE();
		
		ret = E_OK;	
	}
	return ret; 	
}


/**
 * @Summary De-Initializes the ADC
 * @param _adc Pointer to the ADC configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_DeInit(const adc_conf_t *_adc)
{
	Std_ReturnType ret = E_OK;
	
	if (NULL == _adc)
	{
		ret = E_NOT_OK;
	}
	
	else
	{
		/* Disable the ADC */
		ADC_CONVERTER_DISABLE();
		
		/* Configure the interrupt */
		
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
		ADC_InterruptDisable();
#endif
		
	}
	return ret;
}



/**
 * @Summary Allows selection of a channel for conversion
 * @Description This routine is used to select desired channel for conversion.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @param channel Defines the channel available for conversion.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_SelectChannel(const adc_conf_t *_adc, adc_channel_select_t channel)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    
    else
    {
        Channel_Configuration(channel);
        ADC_input_channel_port_configure(channel);
        ret = E_OK;
    }

    return ret;
    
}

/**
 * @Summary Starts conversion
 * @Description This routine is used to start conversion of desired channel.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_StartConversion(const adc_conf_t *_adc)
{
	Std_ReturnType ret = E_OK;
	
	if (NULL == _adc)
	{
		ret = E_NOT_OK;
	}
	
	else
	{
		ADC_START_CONVERSION();
		ret = E_OK;
	}
	return ret;
}





/**
 * @Summary Returns true when the conversion is completed otherwise false.
 * @Description This routine is used to determine if conversion is completed.
 *              When conversion is complete routine returns true. It returns false otherwise.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 *                ADC_StartConversion() should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @param conversion_status The conversion status
 *          true  - If conversion is complete
 *          false - If conversion is not completed
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_IsConversionDone(const adc_conf_t *_adc, uint8 *conversion_status)
{
		
	Std_ReturnType ret = E_OK;

	if ((NULL == _adc) || (NULL == conversion_status))
	{
		ret = E_NOT_OK;
	}
	else
	{
		/* Wait until the conversion is done */
		while (!ADC_CONVERSION_STATUS());
		/* If conversion is completed, set conversion_status to true (1) */
		*conversion_status = !(uint8)(ADC_CONVERSION_STATUS());
	    
	}
	return ret;
}





/**
 * @Summary Returns the ADC conversion value.
 * @Description This routine is used to get the analog to digital converted value.
 *              This routine gets converted values from the channel specified.
 * @Preconditions   This routine returns the conversion value only after the conversion is complete.
 *                  Completion status can be checked using ADC_IsConversionDone() routine.
 * @param _adc Pointer to the ADC configurations
 * @param conversion_result The converted value.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_GetConversionResult(const adc_conf_t *_adc, uint16 *conversion_result)
{
	Std_ReturnType ret = E_OK;
	
	if ((NULL == _adc) || (NULL == conversion_result))
	{
		ret = E_NOT_OK;
	}
	else
	{
		// Read the ADC result based on alignment
		if (ADC_RESULT_RIGHT == _adc->result_format)
		{
			*conversion_result = (uint16)(ADCL | (ADCH << 8)); // Read ADCL first, then ADCH
		}
		else if (ADC_RESULT_LEFT == _adc->result_format)
		{
			*conversion_result = (uint16)(((ADCH << 8) | ADCL) >> 6); // Adjust result for left alignment
		}
		else
		{
			*conversion_result = (uint16)(ADCL | (ADCH << 8));
		}
		ret = E_OK;
	}
	return ret;
}


/**
 * @Summary Returns the ADC conversion value, also allows selection of a channel for conversion.
 * @Description This routine is used to select desired channel for conversion.
 *              This routine is get the analog to digital converted value.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @param channel Defines the channel available for conversion.
 * @param conversion_result The converted value.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_GetConversion_Blocking(const adc_conf_t *_adc, adc_channel_select_t channel, uint16 *conversion_result)
{
	   
	
	Std_ReturnType ret = E_OK;
	//uint8 l_conversion_status = ZERO_INIT;
	
	if ((NULL == _adc) || (NULL == conversion_result))
	{
		ret = E_NOT_OK;
	}
	else
	{
		// Select the A/D channel
		ret = ADC_SelectChannel(_adc, channel);
		// Start the conversion
		ret = ADC_StartConversion(_adc);

		/* Check if conversion is completed */
		while(ADC_CONVERSION_STATUS());
		
		ret = ADC_GetConversionResult(_adc,conversion_result);
		
		//ret = ADC_IsConversionDone(_adc,&l_conversion_status);
		//if (ADC_CONVERSION_COMPLETED == l_conversion_status)
		//{
			//ret = ADC_GetConversionResult(_adc,conversion_result);
		//} 
		//else
		//{
			//ret = E_NOT_OK;
		//}
	}
	return ret;
	

	
}



/**
 * 
 * @param _adc
 * @param channel
 * @return 
 */
Std_ReturnType ADC_StartConversion_Interrupt(const adc_conf_t *_adc, adc_channel_select_t channel)
{
	Std_ReturnType ret = E_OK;
	
	if (NULL == _adc)
	{
		ret = E_NOT_OK;
	}
	else
	{
		 ADC_InterruptFlagClear();
		 
		 /* select the A/D channel */
		 ret = ADC_SelectChannel(_adc, channel);
		 
		 /* Start the conversion */
		 ret = ADC_StartConversion(_adc);
		 
		 ret = E_OK;
	}
	return ret;
}


static inline void ADC_input_channel_port_configure(adc_channel_select_t channel)
{
	switch(channel)
	{
		case ADC_CHANNEL_AN0	:	CLEAR_BIT(DDRA, DDA0);		break;
		case ADC_CHANNEL_AN1	:	CLEAR_BIT(DDRA, DDA1);  	break;
		case ADC_CHANNEL_AN2	:	CLEAR_BIT(DDRA, DDA2);  	break;
		case ADC_CHANNEL_AN3	:	CLEAR_BIT(DDRA, DDA3);  	break;
		case ADC_CHANNEL_AN4	:	CLEAR_BIT(DDRA, DDA4);  	break;
		case ADC_CHANNEL_AN5	:	CLEAR_BIT(DDRA, DDA5);  	break;
		case ADC_CHANNEL_AN6	:	CLEAR_BIT(DDRA, DDA6);  	break;
		case ADC_CHANNEL_AN7	:	CLEAR_BIT(DDRA, DDA7);		break;
		default:/* Nothing */;
	}
}

static inline void Channel_Configuration (adc_channel_select_t channel)
{
	switch(channel)
	{
		case ADC_CHANNEL_AN0 :
		CLEAR_BIT(ADMUX, MUX0);
		CLEAR_BIT(ADMUX, MUX1);
		CLEAR_BIT(ADMUX, MUX2);
		CLEAR_BIT(ADMUX, MUX3);
		break;
		
		case ADC_CHANNEL_AN1 :
		SET_BIT(ADMUX, MUX0);
		CLEAR_BIT(ADMUX, MUX1);
		CLEAR_BIT(ADMUX, MUX2);
		CLEAR_BIT(ADMUX, MUX3);
		break;
		
		case ADC_CHANNEL_AN2 :
		CLEAR_BIT(ADMUX, MUX0);
		SET_BIT(ADMUX, MUX1);
		CLEAR_BIT(ADMUX, MUX2);
		CLEAR_BIT(ADMUX, MUX3);
		break;
		
		case ADC_CHANNEL_AN3 :
		SET_BIT(ADMUX, MUX0);
		SET_BIT(ADMUX, MUX1);
		CLEAR_BIT(ADMUX, MUX2);
		CLEAR_BIT(ADMUX, MUX3);
		break;
		
		case ADC_CHANNEL_AN4 :
		CLEAR_BIT(ADMUX, MUX0);
		CLEAR_BIT(ADMUX, MUX1);
		SET_BIT(ADMUX, MUX2);
		CLEAR_BIT(ADMUX, MUX3);
		break;
		
		case ADC_CHANNEL_AN5 :
		SET_BIT(ADMUX, MUX0);
		CLEAR_BIT(ADMUX, MUX1);
		SET_BIT(ADMUX, MUX2);
		CLEAR_BIT(ADMUX, MUX3);
		break;
		
		case ADC_CHANNEL_AN6 :
		CLEAR_BIT(ADMUX, MUX0);
		SET_BIT(ADMUX, MUX1);
		SET_BIT(ADMUX, MUX2);
		CLEAR_BIT(ADMUX, MUX3);
		break;
		
		case ADC_CHANNEL_AN7 :
		SET_BIT(ADMUX, MUX0);
		SET_BIT(ADMUX, MUX1);
		SET_BIT(ADMUX, MUX2);
		CLEAR_BIT(ADMUX, MUX3);
		break;
		
		default:
		break;  
	}
	
}



static inline void Select_Result_Format(const adc_conf_t *_adc)
{
	if(ADC_RESULT_RIGHT == _adc->result_format)
	{
		ADC_RESULT_RIGHT_FORMAT();
	}
	
	else if(ADC_RESULT_LEFT == _adc->result_format)
	{
		ADC_RESULT_LEFT_FORMAT();
	}
	
	else
	{
		ADC_RESULT_RIGHT_FORMAT();
	}
}


static inline void Configure_Voltage_Reference(const adc_conf_t *_adc)
{
	switch(_adc->voltage_reference)
	{
		case AREF_INTERNAL_VREF_TURNED_OFF :
			CLEAR_BIT(ADMUX, REFS1);
			CLEAR_BIT(ADMUX, REFS0);
			break;
			 
		case AVCC_WITH_EXTERNAL_CAPACITOR :
			CLEAR_BIT(ADMUX, REFS1);
			SET_BIT(ADMUX, REFS0);
			break;
			 
		case INTERNAL_2_56V_VREF_WITH_EXTERNAL_CAPACITOR :
			SET_BIT(ADMUX, REFS1);
			SET_BIT(ADMUX, REFS0);
			break;
			
		default:
		break;
	}
}

static inline void Configure_Conversion_Clock(const adc_conf_t *_adc)
{
	switch(_adc->conversion_clock)
	{
		case ADC_CONVERSION_CLOCK_FOSC_DIV_2 :
		SET_BIT(ADCSRA,ADPS0);
		CLEAR_BIT(ADCSRA,ADPS1);
		CLEAR_BIT(ADCSRA,ADPS2);
		break;
		
		case ADC_CONVERSION_CLOCK_FOSC_DIV_4 :
		CLEAR_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		CLEAR_BIT(ADCSRA,ADPS2);
		break;
		
		case ADC_CONVERSION_CLOCK_FOSC_DIV_8 :
		SET_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		CLEAR_BIT(ADCSRA,ADPS2);
		break;
		
		case ADC_CONVERSION_CLOCK_FOSC_DIV_16 :
		CLEAR_BIT(ADCSRA,ADPS0);
		CLEAR_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS2);
		break;
		
		case ADC_CONVERSION_CLOCK_FOSC_DIV_32 :
		SET_BIT(ADCSRA,ADPS0);
		CLEAR_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS2);
		break;
		
		case ADC_CONVERSION_CLOCK_FOSC_DIV_64 :
		CLEAR_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS2);
		break;
		
		case ADC_CONVERSION_CLOCK_FOSC_DIV_128 :
		SET_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS2);
		break;
		
		default:
		break;
	}
}


void ADC_ISR(void)
{
	ADC_InterruptFlagClear();
	if(ADC_InterruptHandler)
	{
		ADC_InterruptHandler();
	}
}