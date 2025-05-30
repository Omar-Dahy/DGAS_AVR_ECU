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


#endif /* MCAL_INTERNAL_INTERRUPT_H_ */