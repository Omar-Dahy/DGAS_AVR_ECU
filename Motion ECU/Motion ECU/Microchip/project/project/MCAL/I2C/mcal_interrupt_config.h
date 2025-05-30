/*
 * File   :  mcal_interrupt_config.h
 * https://www.linkedin.com/in/ahmed-shawada/
 * Created: 12/9/2024 11:09:35 PM
 * Author: AhmedShawada
 */ 

 


#ifndef MCAL_INTERRUPT_CONFIG_H_
#define MCAL_INTERRUPT_CONFIG_H_


/*Section       :         Includes                */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include "mcal_interrupt_gen_cfg.h"
#include "hal_gpio.h"
#include "mcal_std_types.h"

/*Section       :         Data type Deceleration                 */



/*Section       :         Macro Deceleration                */
#define INTERRUPT_ENABLE    1
#define INTERRUPT_DISABLE   0
#define INTERRUPT_OCCUR     1
#define INTERRUPT_NOT_OCCUR 0



/*Section       :         Macro Function Deceleration                */

/* This macro will enable global interrupts. */
#define INTERRUPT_GlobalInterruptEnable()  sei()
/* This macro will disable global interrupts. */
#define INTERRUPT_GlobalInterruptDisable() cli()


/*Section       :         Function Deceleration                */


#endif /* MCAL_INTERRUPT_CONFIG_H_ */