/*
 * ecu_led.h
 *
 * Created: 12/3/2024 4:57:07 AM
 *  Author: AhmedShawada
 */ 


#ifndef ECU_LED_H_
#define ECU_LED_H_

/*Section       :         Includes                */
#include "GPIO/hal_gpio.h"

/*Section       :         Data type Deceleration                 */

typedef enum {
	LED_OFF = 0,
	LED_ON
}led_status_t;

typedef struct{
	uint8 port_name  : 4;
	uint8 pin        : 3;
	uint8 led_status : 1;
}led_t;

/*Section       :         Macro Deceleration                */

/*Section       :         Macro Function Deceleration                */

/*Section       :         Function Deceleration                */
Std_ReturnType led_intialize (const led_t *led);
Std_ReturnType led_turn_on (const led_t *led);
Std_ReturnType led_turn_off (const led_t *led);
Std_ReturnType led_turn_toggle (const led_t *led);


#endif /* ECU_LED_H_ */