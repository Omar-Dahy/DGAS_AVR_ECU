/*
 * File   :  hal_spi.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Created: 12/17/2024 11:10:06 PM
 * Author: AhmedShawada
 */ 

#include "hal_spi.h" 

#if SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*SPI_InterruptHandler)(void) = NULL;
#endif

static void SPI_Interrupt_Init(const SPI_Config *Config);
static void SPI_Master_Mode_Configurations(const SPI_Config *Config);
static void SPI_Slave_Mode_Configurations(const SPI_Config *Config);
static void Clock_Polarity_Clock_Phase_Select(const SPI_Config *Config);

Std_ReturnType SPI_Init(const SPI_Config *Config)
{
	Std_ReturnType ret = E_OK;
	
	if (NULL == Config)
	{
		ret = E_NOT_OK;
	} 
	else
	{
		/* Disable SPI Module */
		SPI_DISABLE_MODULE();
		
		/* SPI Mode Select */
		if (SPI_MASTER_MODE == Config->spi_mode)
		{
			SPI_Master_Mode_Configurations(Config);
		}
		else if(SPI_SLAVE_MODE == Config->spi_mode)
		{
			SPI_Slave_Mode_Configurations(Config);
		}
		else{ /* Nothing */ }
		
		/* Set Clock Polarity and Clock Phase  */
		Clock_Polarity_Clock_Phase_Select(Config);
		
		/* Interrupt Configurations */
		if(SPI_INTERRUPT_ENABLE == Config->spi_config.SPI_Interrupt)
		{
			SPI_Interrupt_Init(Config);
		}
		else{ /* Nothing */ }
		
		/* Enable SPI Module */
		SPI_ENABLE_MODULE();
		
	}
	return ret;
}

Std_ReturnType SPI_DeInit(const SPI_Config *Config)
{
	Std_ReturnType ret = E_OK;
	
	if (NULL == Config)
	{
		ret = E_NOT_OK;
	}
	
	else
	{
		/* Disable SPI Module */
		SPI_DISABLE_MODULE();
		
		/* Interrupt Configurations */
#if SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
		SPI_InterruptDisable();
#endif	
	}
	return ret; 	
}


void SPI_Master_Send_Byte(const SPI_Config *Config, const uint8 _data)
{
	/* Start Transmission */
	SPDR = _data;
	

	/* Wait for transmission complete */
	while(!SPIF_STATUS());
	
	/* Clear SPIF flag */
	CLEAR_BIT(SPSR,SPIF);
	
}



void SPI_Slave_Read_Byte(const SPI_Config *Config, uint8 *_data)
{
	/* Wait for reception complete */
	while(!SPIF_STATUS()); 
	
	/* Return data register */
	*_data = SPDR;
}



static void SPI_Interrupt_Init(const SPI_Config *Config)
{
#if SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
	SPI_InterruptHandler = Config->SPI_InterruptHandler;
	SPI_InterruptEnable();
	SPI_InterruptFlagClear();	
	INTERRUPT_GlobalInterruptEnable();
#endif
	
}

static void SPI_Master_Mode_Configurations(const SPI_Config *Config)
{
	Std_ReturnType ret = E_OK;
	
	/*  -----------  PIN_Configurations  ----------- */
	pin_config_t SPI_SS = {.port = PORTB_INDEX, .pin = GPIO_PIN4, .direction = GPIO_DIRECTION_OUTPUT};
	pin_config_t SPI_MOSI = {.port = PORTB_INDEX, .pin = GPIO_PIN5, .direction = GPIO_DIRECTION_OUTPUT};
	pin_config_t SPI_MISO = {.port = PORTB_INDEX, .pin = GPIO_PIN6, .direction = GPIO_DIRECTION_INPUT};
	pin_config_t SPI_SCK = {.port = PORTB_INDEX, .pin = GPIO_PIN7, .direction = GPIO_DIRECTION_OUTPUT};
	ret = gpio_pin_direction_intialize(&SPI_SS);
	ret = gpio_pin_direction_intialize(&SPI_MOSI);
	ret = gpio_pin_direction_intialize(&SPI_MISO);
	ret = gpio_pin_direction_intialize(&SPI_SCK);
	
	/*  -----------  Enable Master  -----------  */
	SPI_MASTER_ENABLE();
	
	/*  -----------  Set Clock Rate  -----------  */
	switch(Config->spi_config.SCKFrequency)
	{
		case SPI_MASTER_FOSC_DIV4 :
	    CLEAR_BIT(SPCR,SPR0);
	    CLEAR_BIT(SPCR,SPR1);
	    break;
		
		case SPI_MASTER_FOSC_DIV16 : 
		SET_BIT(SPCR,SPR0); 
		CLEAR_BIT(SPCR,SPR1); 
		break;
		
		case SPI_MASTER_FOSC_DIV64 : 
		CLEAR_BIT(SPCR,SPR0); 
		SET_BIT(SPCR,SPR1); 
		break;
		
		case SPI_MASTER_FOSC_DIV128 : 
		SET_BIT(SPCR,SPR0); 
		SET_BIT(SPCR,SPR1);
		break;
		
		default:/* Nothing */
		break;
	}
}



static void SPI_Slave_Mode_Configurations(const SPI_Config *Config)
{
	Std_ReturnType ret = E_OK;
	
	pin_config_t SPI_MISO = {.port = PORTB_INDEX, .pin = GPIO_PIN6, .direction = GPIO_DIRECTION_OUTPUT};
	ret = gpio_pin_direction_intialize(&SPI_MISO);
	
	/*  -----------  Enable SLAVE  -----------  */
	SPI_SLAVE_ENABLE();
	
}



static void Clock_Polarity_Clock_Phase_Select(const SPI_Config *Config)
{
	switch(Config->spi_config.ClockPolarity_ClockPhase)
	{
		case SPI_IDLE_LOW_SAMPLE_RAISING :
		CLEAR_BIT(SPCR,CPOL);
		CLEAR_BIT(SPCR,CPHA);
		break;
		
		case SPI_IDLE_LOW_SAMPLE_FALLING :
		CLEAR_BIT(SPCR,CPOL);
		SET_BIT(SPCR,CPHA);
		break;
		
		case SPI_IDLE_HIGH_SAMPLE_FALLING :
		SET_BIT(SPCR,CPOL);
		CLEAR_BIT(SPCR,CPHA);
		break;
		
		case SPI_IDLE_HIGH_SAMPLE_RAISING :
		SET_BIT(SPCR,CPOL);
		SET_BIT(SPCR,CPHA);
		break;
	}
}



void SPI_ISR(void)
{
#if SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
	SPI_InterruptFlagClear();
	if(SPI_InterruptHandler)
	{
		SPI_InterruptHandler();	
	}
#endif
}