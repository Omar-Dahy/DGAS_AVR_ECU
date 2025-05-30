/*
 * File   :  application.h
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/3/2024 4:02:19 AM
 */ 


#ifndef APPLICATION_H_
#define APPLICATION_H_


/*Section       :         Includes                */
#define F_CPU 16000000UL
#include "ECU_Layer/LED/ecu_led.h"
#include "MCAL_Layer/Interrupt/mcal_external_interrupt.h"
#include "hal_adc.h"
#include "hal_i2c.h"
#include "hal_timer0.h"
#include "hal_timer1.h"
#include "lighting_interface.h"
#include "LDR_interface.h"

/*Section       :         Data type Deceleration                 */

/*Section       :         Macro Deceleration                */



/*Section       :         Macro Function Deceleration                */


/*Section       :         Function Deceleration                */
void application_intialize (void);
void func(uint8 var);
void i2c_slave_interrupt_handler(void);

#endif /* APPLICATION_H_ */