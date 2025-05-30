/*
 * File   :  mcal_internal_interrupt.h
 * https://www.linkedin.com/in/ahmed-shawada/
 * Created: 12/9/2024 11:08:40 PM
 * Author: AhmedShawada
 */ 



#ifndef MCAL_INTERNAL_INTERRUPT_H_
#define MCAL_INTERNAL_INTERRUPT_H_


/*Section       :         Includes                */
#include "mcal_interrupt_config.h"


/*Section       :         Macro Function Deceleration                */

/*=============== ADC INTERNAL INTERRUPT===============*/

#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the ADC Interrupt */
#define ADC_InterruptDisable()				(CLEAR_BIT(ADCSRA,ADIE))
/* This routine sets the interrupt enable for the ADC Interrupt */
#define ADC_InterruptEnable()				(SET_BIT(ADCSRA,ADIE))
/* This routine clears the interrupt flag for the ADC Interrupt */
#define ADC_InterruptFlagClear()			(SET_BIT(ADCSRA,ADIF))
#endif  

/*=============== END ADC INTERNAL INTERRUPT ===============*/

/*=============== SPI INTERNAL INTERRUPT===============*/

#if SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the SPI Module */
#define SPI_InterruptDisable()				(CLEAR_BIT(SPCR,SPIE))
/* This routine sets the interrupt enable for the SPI Module */
#define SPI_InterruptEnable()				(SET_BIT(SPCR,SPIE))
/* This routine clears the interrupt flag for the SPI Module */
#define SPI_InterruptFlagClear()			(CLEAR_BIT(SPSR,SPIF))
#endif

/*=============== END SPI INTERNAL INTERRUPT ===============*/


/*=============== I2C INTERNAL INTERRUPT===============*/

#if I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the I2C Module */
#define I2C_InterruptDisable()			   (CLEAR_BIT(TWCR,TWIE))
/* This routine sets the interrupt enable for the I2C Module */
#define I2C_InterruptEnable()			   (SET_BIT(TWCR,TWIE))
/* This routine clears the interrupt flag for the I2C Module */
#define I2C_InterruptFlagClear()		   (SET_BIT(TWCR,TWINT))
#endif

/*=============== END I2C INTERNAL INTERRUPT ===============*/




/*=============== TIMER0 INTERNAL INTERRUPT ===============*/

/* --------------- Compare Interrupt ----------*/
#if TMR0_COMPARE_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine clears the Compare interrupt enable for the TMR0 Module */
#define TMR0_Compare_InterruptDisable()			(CLEAR_BIT(TIMSK,OCIE0))
/* This routine sets the Compare interrupt enable for the TMR0 Module */
#define TMR0_Compare_InterruptEnable()			(SET_BIT(TIMSK,OCIE0))
/* This routine clears the Compare interrupt flag for the TMR0 Module */
#define TMR0_Compare_InterruptFlagClear()		(SET_BIT(TIFR,OCF0))
#endif

/* --------------- Overflow Interrupt ----------*/
#if TMR0_OVERFLOW_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine clears the Overflow interrupt enable for the TMR0 Module */
#define TMR0_OverFlow_InterruptDisable()		(CLEAR_BIT(TIMSK,TOIE0))
/* This routine sets the Overflow interrupt enable for the TMR0 Module */
#define TMR0_OverFlow_InterruptEnable()			(SET_BIT(TIMSK,TOIE0))
/* This routine clears the Overflow interrupt flag for the TMR0 Module */
#define TMR0_OverFlow_InterruptFlagClear()		(SET_BIT(TIFR,TOV0))
#endif

/*=============== END TIMER0 INTERNAL INTERRUPT ===============*/



/*=============== TIMER1 INTERNAL INTERRUPT ===============*/

/* --------------- Capture Interrupt ----------*/
#if TMR1_CAPTURE_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine clears the Capture interrupt enable for the TMR1 Module */
#define TMR1_Capture_InterruptDisable()			(CLEAR_BIT(TIMSK,TICIE1))
/* This routine sets the Capture interrupt enable for the TMR1 Module */
#define TMR1_Capture_InterruptEnable()			(SET_BIT(TIMSK,TICIE1))
/* This routine clears the Capture interrupt flag for the TMR1 Module */
#define TMR1_Capture_InterruptFlagClear()		(SET_BIT(TIFR,ICF1))
#endif

/* --------------- CompareA Interrupt ----------*/
#if TMR1_COMPARE_A_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine clears the CompareA interrupt enable for the TMR1 Module */
#define TMR1_CompareA_InterruptDisable()		(CLEAR_BIT(TIMSK,OCIE1A))
/* This routine sets the CompareA interrupt enable for the TMR1 Module */
#define TMR1_CompareA_InterruptEnable()			(SET_BIT(TIMSK,OCIE1A))
/* This routine clears the CompareA interrupt flag for the TMR1 Module */
#define TMR1_CompareA_InterruptFlagClear()		(SET_BIT(TIFR,OCF1A))
#endif

/* --------------- CompareB Interrupt ----------*/
#if TMR1_COMPARE_B_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine clears the CompareA interrupt enable for the TMR1 Module */
#define TMR1_CompareB_InterruptDisable()		(CLEAR_BIT(TIMSK,OCIE1B))
/* This routine sets the CompareA interrupt enable for the TMR1 Module */
#define TMR1_CompareB_InterruptEnable()			(SET_BIT(TIMSK,OCIE1B))
/* This routine clears the CompareA interrupt flag for the TMR1 Module */
#define TMR1_CompareB_InterruptFlagClear()		(SET_BIT(TIFR,OCF1B))
#endif

/* --------------- Overflow Interrupt ----------*/
#if TMR1_OVERFLOW_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine clears the Overflow interrupt enable for the TMR1 Module */
#define TMR1_OverFlow_InterruptDisable()		(CLEAR_BIT(TIMSK,TOIE1))
/* This routine sets the Overflow interrupt enable for the TMR1 Module */
#define TMR1_OverFlow_InterruptEnable()			(SET_BIT(TIMSK,TOIE1))
/* This routine clears the Overflow interrupt flag for the TMR1 Module */
#define TMR1_OverFlow_InterruptFlagClear()		(SET_BIT(TIFR,TOV1))
#endif

/*=============== END TIMER1 INTERNAL INTERRUPT ===============*/



#endif /* MCAL_INTERNAL_INTERRUPT_H_ */