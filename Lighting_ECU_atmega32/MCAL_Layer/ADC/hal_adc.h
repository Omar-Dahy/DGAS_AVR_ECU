/*
 * File   :  hal_adc.h
 * https://www.linkedin.com/in/ahmed-shawada/
 * Created: 12/11/2024 4:59:06 AM
 * Author: AhmedShawada
 */ 

#ifndef HAL_ADC_H_
#define HAL_ADC_H_

/*Section       :         Includes                */
#include <avr/io.h>
#include "mcal_internal_interrupt.h"
#include "hal_gpio.h"
#include "mcal_std_types.h"

/*Section       :         Data type Deceleration                 */

typedef enum
{
	ADC_CHANNEL_AN0 = 0,
	ADC_CHANNEL_AN1,
	ADC_CHANNEL_AN2,
	ADC_CHANNEL_AN3,
	ADC_CHANNEL_AN4,
	ADC_CHANNEL_AN5,
	ADC_CHANNEL_AN6,
	ADC_CHANNEL_AN7
}adc_channel_select_t;


typedef enum
{
	AREF_INTERNAL_VREF_TURNED_OFF = 0, 
	AVCC_WITH_EXTERNAL_CAPACITOR,          
	INTERNAL_2_56V_VREF_WITH_EXTERNAL_CAPACITOR = 3
}Voltage_ref_select_t;


typedef enum{
	ADC_CONVERSION_CLOCK_FOSC_DIV_2 = 1,
	ADC_CONVERSION_CLOCK_FOSC_DIV_4,
	ADC_CONVERSION_CLOCK_FOSC_DIV_8,
	ADC_CONVERSION_CLOCK_FOSC_DIV_16,
	ADC_CONVERSION_CLOCK_FOSC_DIV_32,
	ADC_CONVERSION_CLOCK_FOSC_DIV_64,
	ADC_CONVERSION_CLOCK_FOSC_DIV_128
}adc_conversion_clock_t;


/**
 * ADC Configurations
 */
typedef struct{
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* ADC_InterruptHandler)(void);
#endif
    adc_conversion_clock_t conversion_clock;		/* @ref adc_conversion_clock_t */
    adc_channel_select_t adc_channel;				/* @ref adc_channel_select_t */
    Voltage_ref_select_t voltage_reference;			/* Voltage Reference Configuration */
    uint8 result_format : 1;						/* A/D Result Format Select */
    uint8 ADC_Reserved : 7;
}adc_conf_t;


/*Section       :         Macro Deceleration                */

#define ADC_RESULT_RIGHT					 0x01U
#define ADC_RESULT_LEFT						 0x00U

#define ADC_CONVERSION_COMPLETED			 0x01U
#define ADC_CONVERSION_INPROGRESS			 0x00U


/*Section       :         Macro Function Deceleration                */

#define ADC_CONVERSION_STATUS()			(READ_BIT(ADCSRA,ADSC))

#define ADC_START_CONVERSION()			(SET_BIT(ADCSRA,ADSC))

#define ADC_CONVERTER_ENABLE()			(SET_BIT(ADCSRA,ADEN))
#define ADC_CONVERTER_DISABLE()			(CLEAR_BIT(ADCSRA,ADEN))

#define ADC_RESULT_RIGHT_FORMAT()		(CLEAR_BIT(ADMUX,ADLAR))
#define ADC_RESULT_LEFT_FORMAT()		(SET_BIT(ADMUX,ADLAR))



/*Section       :         Function Deceleration                */
Std_ReturnType ADC_Init(const adc_conf_t *_adc);
Std_ReturnType ADC_DeInit(const adc_conf_t *_adc);
Std_ReturnType ADC_SelectChannel(const adc_conf_t *_adc, adc_channel_select_t channel);
Std_ReturnType ADC_StartConversion(const adc_conf_t *_adc);
Std_ReturnType ADC_IsConversionDone(const adc_conf_t *_adc, uint8 *conversion_status);
Std_ReturnType ADC_GetConversionResult(const adc_conf_t *_adc, uint16 *conversion_result);
Std_ReturnType ADC_GetConversion_Blocking(const adc_conf_t *_adc, adc_channel_select_t channel,uint16 *conversion_result);
Std_ReturnType ADC_StartConversion_Interrupt(const adc_conf_t *_adc, adc_channel_select_t channel);


#endif /* HAL_ADC_H_ */