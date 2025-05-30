/*
 * hal_gpio.c
 *
 * Created: 12/3/2024 4:39:18 AM
 *  Author: AhmedShawada
 */ 

#include "GPIO/hal_gpio.h"

/* Referencing to the Data Direction Control Register (DDRx) */
volatile uint8 *ddr_register[] = {&DDRA ,&DDRB ,&DDRC ,&DDRD};
/* Referencing to the Data Latch Register (PORTx) */
volatile uint8 *port_register[] = {&PORTA ,&PORTB ,&PORTC ,&PORTD};
/* Referencing to the Port Status Register (PINx) */
volatile uint8 *pin_register[] = {&PINA ,&PINB ,&PINC ,&PIND};


/**
 * @brief Initialize the direction of a specific pin
 * @param _pin_config  pointer to the configurations
 * @return Status of the function
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_direction_intialize (const pin_config_t *_pin_config)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _pin_config || _pin_config->pin >= PORT_PIN_MAX_NUMBER)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch (_pin_config->direction)
        {
            case GPIO_DIRECTION_OUTPUT:
                SET_BIT(*ddr_register[_pin_config->port], _pin_config->pin);
                break;
                
            case GPIO_DIRECTION_INPUT:
                CLEAR_BIT(*ddr_register[_pin_config->port], _pin_config->pin);
                break;
                
            default:
                ret = E_NOT_OK;
        }
    }
    return ret;
}
#endif


#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_get_direction_status (const pin_config_t *_pin_config, direction_t *direction_status)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _pin_config || _pin_config->pin >= PORT_PIN_MAX_NUMBER)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *direction_status = READ_BIT(*ddr_register[_pin_config->port], _pin_config->pin);
    }
    return ret;
}
#endif


/**
 * @brief Write logic to a pin
 * @param _pin_config  pointer to the configurations
 * @param logic The logic level to write
 * @return Status of the function
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_write_logic (const pin_config_t *_pin_config, logic_t logic)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _pin_config || _pin_config->pin >= PORT_PIN_MAX_NUMBER)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch (logic)
        {
            case GPIO_LOW:
                CLEAR_BIT(*port_register[_pin_config->port], _pin_config->pin);
                break;
                
            case GPIO_HIGH:
                SET_BIT(*port_register[_pin_config->port], _pin_config->pin);
                break;
                
            default:
                ret = E_NOT_OK;
        }
    }
    return ret;
}
#endif


/**
 * @brief Read logic from a pin
 * @param _pin_config  pointer to the configurations
 * @param logic Pointer to store the logic level read
 * @return Status of the function
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_read_logic (const pin_config_t *_pin_config, logic_t *logic)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _pin_config || NULL == logic || _pin_config->pin >= PORT_PIN_MAX_NUMBER)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *logic = READ_BIT(*pin_register[_pin_config->port], _pin_config->pin);
    }
    return ret;
}
#endif


/**
 * @brief Toggle the logic of a pin
 * @param _pin_config  pointer to the configurations
 * @return Status of the function
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_toggle_logic (const pin_config_t *_pin_config)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _pin_config || _pin_config->pin >= PORT_PIN_MAX_NUMBER)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TOOGGLE_BIT(*port_register[_pin_config->port], _pin_config->pin);
    }
    return ret;
}
#endif


/**
 * @brief Initialize the pin
 * @param _pin_config  pointer to the configurations
 * @return Status of the function
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_intialize (const pin_config_t *_pin_config)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _pin_config || _pin_config->pin >= PORT_PIN_MAX_NUMBER)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_direction_intialize(_pin_config);
        gpio_pin_write_logic(_pin_config, _pin_config->logic);
    }
    return ret;
}
#endif


/**
 * @brief Initialize the direction of a port
 * @param port Port index
 * @param direction Direction value
 * @return Status of the function
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_port_direction_intialize (port_index_t port, uint8 direction)
{
    Std_ReturnType ret = E_OK;
    if (port >= PORT_MAX_NUMBER)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *ddr_register[port] = direction;
    }
    return ret;
}
#endif


/**
 * @brief Read logic from a port
 * @param port Port index
 * @param logic Pointer to store the logic level read
 * @return Status of the function
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_port_read_logic (port_index_t port, uint8 *logic)
{
    Std_ReturnType ret = E_OK;
    if (port >= PORT_MAX_NUMBER || NULL == logic)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *logic = *pin_register[port];
    }
    return ret;
}
#endif


/**
 * @brief Write logic to a port
 * @param port Port index
 * @param logic The logic level to write
 * @return Status of the function
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_port_write_logic (port_index_t port, uint8 logic)
{
    Std_ReturnType ret = E_OK;
    if (port >= PORT_MAX_NUMBER)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *port_register[port] = logic;
    }
    return ret;
}
#endif


/**
 * @brief Toggle the logic of a port
 * @param port Port index
 * @return Status of the function
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_port_toggle_logic (port_index_t port)
{
    Std_ReturnType ret = E_OK;
    if (port >= PORT_MAX_NUMBER)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *port_register[port] ^= PORTC_MASK;  // Toggle all pins in the port
    }
    return ret;
}
#endif
