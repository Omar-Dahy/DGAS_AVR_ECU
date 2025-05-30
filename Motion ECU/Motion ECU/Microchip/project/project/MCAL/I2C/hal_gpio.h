/*
 * hal_gpio.h
 *
 * Created: 12/3/2024 4:39:35 AM
 *  Author: AhmedShawada
 */ 


#ifndef HAL_GPIO_H_
#define HAL_GPIO_H_

/*Section       :         Includes                */
#include <avr/io.h>
#include "mcal_std_types.h"
#include "device_config.h"
#include "hal_gpio_cfg.h"


/*Section       :         Data type Deceleration                 */
typedef enum{
	GPIO_LOW = 0,
	GPIO_HIGH
}logic_t;

typedef enum{
	GPIO_DIRECTION_INPUT = 0,
	GPIO_DIRECTION_OUTPUT
}direction_t;

typedef enum{
	GPIO_PIN0 = 0,
	GPIO_PIN1,
	GPIO_PIN2,
	GPIO_PIN3,
	GPIO_PIN4,
	GPIO_PIN5,
	GPIO_PIN6,
	GPIO_PIN7
}pin_index_t;

typedef enum{
	PORTA_INDEX = 0,
	PORTB_INDEX,
	PORTC_INDEX,
	PORTD_INDEX,
}port_index_t;

typedef struct{
	uint8 port       : 3;       /* @ref port_index_t */
	uint8 pin        : 3;       /* @ref pin_index_t */
	uint8 direction  : 1;       /* @ref direction_t */
	uint8 logic      : 1;       /* @ref logic_t  */
}pin_config_t;


/*Section       :         Macro Deceleration                */
#define BIT_MASK         (uint8)1
#define PORT_PIN_MAX_NUMBER     8
#define PORT_MAX_NUMBER         4

#define PORTC_MASK              0xff

#define GPIO_PORT_PIN_CONFIGURATION  CONFIG_ENABLE
#define GPIO_PORT_CONFIGURATION      CONFIG_ENABLE


/*Section       :         Macro Function Deceleration                */
#define HWREG(_x)    (*((volatile uint8_t  *) (_x)))

#define SET_BIT(REG,BIT_POS)         (REG |= (BIT_MASK << BIT_POS))
#define CLEAR_BIT(REG,BIT_POS)       (REG &= ~(BIT_MASK << BIT_POS))
#define TOOGGLE_BIT(REG,BIT_POS)     (REG ^= (BIT_MASK << BIT_POS))
#define READ_BIT(REG,BIT_POS)        ((REG >> BIT_POS) & BIT_MASK)


/*Section       :         Function Deceleration                */
Std_ReturnType gpio_pin_direction_intialize (const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_get_direction_status (const pin_config_t *_pin_config ,direction_t *direction_status);
Std_ReturnType gpio_pin_write_logic (const pin_config_t *_pin_config ,logic_t logic);
Std_ReturnType gpio_pin_read_logic (const pin_config_t *_pin_config ,logic_t *logic);
Std_ReturnType gpio_pin_toggle_logic (const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_intialize (const pin_config_t *_pin_config);

Std_ReturnType gpio_port_direction_intialize (port_index_t port ,uint8 direction);
Std_ReturnType gpio_port_get_direction_status (port_index_t port ,uint8 *direction_status);
Std_ReturnType gpio_port_write_logic (port_index_t port ,uint8 logic);
Std_ReturnType gpio_port_read_logic (port_index_t port ,uint8 *logic);
Std_ReturnType gpio_port_toggle_logic (port_index_t port);


#endif /* HAL_GPIO_H_ */