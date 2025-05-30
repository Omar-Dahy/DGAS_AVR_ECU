# define F_CPU 16000000UL
#include <util/delay.h>

/*------------------------ Configuration Defines ---------------------------*/
#define SLAVE_ADDRESS 0x62  /**< 7-bit slave address matching master config */

void i2c_slave_interrupt_handler(void);

#include "MemMap.h"
#include "utils.h"
#include "StdTypes.h"
#include "DIO_Int.h"
#include "MOTOR_Int.h"
#include "Timers.h"
#include "I2C/hal_i2c.h"

i2c_t slave_i2c_obj = {
	.mode = I2C_SLAVE_MODE,
	.clock = 0,                     /**< Not used in slave mode */
	.prescaler = I2C_PRESCALER_1,   /**< Not used in slave mode */
	.master_address = 0,            /**< Not used in slave mode */
	.slave_address = SLAVE_ADDRESS, /**< Set slave address */
	.interrupt_enable = 1,          /**< Enable interrupt-driven communication */
	#if I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
	.interrupt_handler = i2c_slave_interrupt_handler
	#endif
};


volatile uint8 I2C_Value = 0;
volatile uint8 next_byte_is_speed = 0;
volatile uint8 speed = 255;

/*------------------------- Global Variables -------------------------------*/
volatile uint8_t rx_buffer;         /**< Buffer for received I2C data */
volatile uint8_t i2c_state = 0;     /**< Current I2C state:
										 *  0x60  = Own SLA+W received, ACK returned
										 *  0x68  = Arbitration lost, own SLA+W received, ACK returned
										 *  0x70  = General call received, ACK returned
										 *  0x78  = Arbitration lost, general call received, ACK returned
										 *  0x80  = Data received after SLA+W, ACK returned
										 *  0x88  = Data received after SLA+W, NACK returned
										 *  0x90  = Data received after general call, ACK returned
										 *  0x98  = Data received after general call, NACK returned
										 *  0xA0  = STOP or repeated START received while addressed as slave
										 */

void i2c_slave_interrupt_handler(void) {
	i2c_state = (TWSR & I2C_STATUS_MASK);  /**< Store current I2C status */
	
	if ((0xC0 == TWDR) || (I2C_SLV_STOP_RCVD == i2c_state)) {
		/* Do nothing on stop or NACK condition */
		} else {
		rx_buffer = TWDR;  /**< Read received data from master */
		func(1);           /**< Blink LED to indicate reception */
	}
}

int main(void)
{
	
	DIO_Init();
	MOTOR_Init();
	i2c_init(&slave_i2c_obj);
	_delay_ms(150);
	while(1)
	{   
		switch(rx_buffer){
			case 0x81:
				MOTOR_Speed(speed);
				rx_buffer = 0;
			break;
			case 0x82:
				MOTOR_CW(TOTAL_MOTORS);
				rx_buffer = 0;
			break;
			case 0x83:
				MOTOR_CCW(TOTAL_MOTORS);
			break;
			case 0x84:
				MOTOR_Stop(TOTAL_MOTORS);
				rx_buffer = 0;
			break;
			case 0x85:
				MOTOR_CW(M1);
				rx_buffer = 0;
			break;
			case 0x86:
				MOTOR_CCW(M1);
				rx_buffer = 0;
			break;
			case 0x87:
				MOTOR_Stop(M1);
				rx_buffer = 0;
			break;
			case 0x88:
				MOTOR_CW(M2);
				rx_buffer = 0;
			break;
			case 0x89:
				MOTOR_CCW(M2);
				rx_buffer = 0;
			break;
			case 0x8A:
				MOTOR_Stop(M2);
				rx_buffer = 0;
			break;
			default:
				
			break;
			}		  
	}
}

/*-------------------------- Debugging LED Blink ---------------------------*/
/**
 * @brief Blinks LED connected to PC7 for debug signaling.
 * 
 * @param var Number of blink cycles.
 */
void func(uint8 var) {
	DDRC |= (1 << 7);  /**< Set PC7 as output without changing other bits */
	for(uint8 counter = 0; counter < var; counter++) {
		PORTC |= (1 << 7);   /**< Turn LED ON (PC7 = 1) */
		_delay_ms(100);
		PORTC &= ~(1 << 7);  /**< Turn LED OFF (PC7 = 0) */
		_delay_ms(100);
	}
}
