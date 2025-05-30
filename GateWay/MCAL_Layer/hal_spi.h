/*
 * File   :  hal_spi.h
 * https://www.linkedin.com/in/ahmed-shawada/
 * Created: 12/17/2024 11:10:18 PM
 * Author: AhmedShawada
 */ 

#ifndef HAL_SPI_H_
#define HAL_SPI_H_


/*Section       :         Includes                */
#include <avr/io.h>
#include "mcal_std_types.h"
#include "hal_gpio.h"
#include "mcal_internal_interrupt.h"

/*Section       :         Macro Deceleration                */
/* ========= SPI Mode ========= */
#define SPI_SLAVE_MODE						0
#define SPI_MASTER_MODE						1 
/* ========= SCK Frequency Select ========= */
#define SPI_MASTER_FOSC_DIV4				0 
#define SPI_MASTER_FOSC_DIV16				1 
#define SPI_MASTER_FOSC_DIV64				2 
#define SPI_MASTER_FOSC_DIV128				3
/******* SCK Frequency Select ( DOUPLE SPI SPEED (SPI2X) ) *******/
#define SPI_MASTER_FOSC_DIV2				4
#define SPI_MASTER_FOSC_DIV8				5
#define SPI_MASTER_FOSC_DIV32				6 
#define SPI_MASTER__DOUPLE_FOSC_DIV64		7

/* ========= Select Clock Polarity and Clock Phase ========= */
#define SPI_IDLE_LOW_SAMPLE_RAISING			0
#define SPI_IDLE_LOW_SAMPLE_FALLING			1
#define SPI_IDLE_HIGH_SAMPLE_FALLING		2
#define SPI_IDLE_HIGH_SAMPLE_RAISING		3

/* ========= SPI Interrupt ========= */
#define SPI_INTERRUPT_DISABLE				0
#define SPI_INTERRUPT_ENABLE				1


/*Section       :         Macro Function Deceleration                */
#define SPI_ENABLE_MODULE()			(SET_BIT(SPCR,SPE)) 
#define SPI_DISABLE_MODULE()		(CLEAR_BIT(SPCR,SPE))

#define SPI_MASTER_ENABLE()			(SET_BIT(SPCR,MSTR))
#define SPI_SLAVE_ENABLE()			(CLEAR_BIT(SPCR,MSTR))

#define SPIF_STATUS()				(READ_BIT(SPSR,SPIF))


/*Section       :         Data type Deceleration                 */
typedef struct
{
	uint8 SCKFrequency : 3;
	uint8 ClockPolarity_ClockPhase : 2;
	uint8 SPI_Interrupt : 1;
	uint8 Reserved : 2;
	
}SPI_Control_Config;


typedef struct
{
#if SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
	void (* SPI_InterruptHandler)(void);
#endif
	uint8 spi_mode;
	SPI_Control_Config spi_config;
	
}SPI_Config;


/*Section       :         Function Deceleration                */
Std_ReturnType SPI_Init(const SPI_Config *Config);
Std_ReturnType SPI_DeInit(const SPI_Config *Config);
void SPI_Master_Send_Byte(const SPI_Config *Config, const uint8 _data);
void SPI_Slave_Read_Byte(const SPI_Config *Config, uint8 *_data);
Std_ReturnType SPI_Send_Byte_NonBlocking(const SPI_Config *Config, const uint8 _data);
Std_ReturnType SPI_Read_Byte_NonBlocking(const SPI_Config *Config, uint8 *_data);


#endif /* HAL_SPI_H_ */