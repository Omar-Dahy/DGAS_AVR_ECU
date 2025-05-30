/*
 * File   :  application.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/3/2024 4:02:19 AM
*/ 
#define F_CPU 16000000UL
#include "application.h"

#define LIGHTING_ECU_ADDRESS 0X60
#define MOTION_ECU_ADDRESS   0X62

#define MOTOR_SPEED		0X80

#define MOTOR_ALL_CW	0X82
#define MOTOR_ALL_CCW	0X83
#define MOTOR_ALL_STOP	0X84

#define MOTOR_M1_CW		0X85
#define MOTOR_M1_CCW	0X86
#define MOTOR_M1_STOP	0X87

#define MOTOR_M2_CW		0X88
#define MOTOR_M2_CCW	0X89
#define MOTOR_M2_STOP	0X8A

void i2c_interrupt_handler(void) {
	/* Handle I2C interrupt */
}

i2c_t i2c_config = {
	.mode = I2C_MASTER_MODE,
	.clock = 100000, /* 100 kHz */
	.prescaler = I2C_PRESCALER_1,
	.master_address = 0x10,
	.slave_address = 0,
	.interrupt_enable = 0,
	#if I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
	.interrupt_handler = i2c_interrupt_handler
	#endif
};

void func(uint8 var);
void func(uint8 var){
	DDRD = 0x40;
	uint8 counter=0;
	for(counter=0; counter < var; counter++){
		PORTD = 0x40;
		_delay_ms(500);
		PORTD = 0x00;
		_delay_ms(500);
	}

}

Std_ReturnType return_value = E_OK;
uint8 slave_function_code = 0x80;
int main(void)
{
	/* Initialize debug GPIOs */
	DDRD |= (1 << 6) | (1 << 7); /* PB5: Transaction, PB4: Error/Normal */
	PORTD &= ~((1 << 6) | (1 << 7)); /* Start low */
	
	application_intialize();
	_delay_ms(500);	/* Delay untill the slave intialize */
	while(1){
		Motion_ecu_all_functions();
	}
	
	return 0;
}

void application_intialize (void)
{
	Std_ReturnType ret = E_OK;
	i2c_init(&i2c_config);
	if (ret != E_OK)
	{/*Handle failure*/}
}

void Lighting_ecu_all_functions(void){
	i2c_master_start(&i2c_config);
	i2c_master_write_address(&i2c_config, LIGHTING_ECU_ADDRESS,0);
	_delay_ms(405);
	if(E_NOT_OK == return_value){PORTD |= (1 << 6);}else{PORTD &= ~(1 << 6);}
	return_value = i2c_master_write_byte(&i2c_config, slave_function_code);
	if(E_NOT_OK == return_value){PORTD |= (1 << 7);}else{PORTD &= ~(1 << 7);}
	_delay_ms(2000);
	slave_function_code ++;
	return_value = i2c_master_write_byte(&i2c_config, slave_function_code);
	if(E_NOT_OK == return_value){PORTD |= (1 << 7);}else{PORTD &= ~(1 << 7);}
	i2c_master_stop(&i2c_config);
	_delay_ms(2000);
	slave_function_code ++;
	if(0x90 == slave_function_code){
		slave_function_code = 0x80;
	}
}

void Motion_ecu_all_functions(void) {
	static uint8_t motion_function_code = 0x81;  // Start from the first function code
	Std_ReturnType return_value = E_OK;

	// Start I2C communication
	i2c_master_start(&i2c_config);
	i2c_master_write_address(&i2c_config, MOTION_ECU_ADDRESS, 0);  // Write operation
	_delay_ms(405);

	// Check if address write was successful
	if (E_NOT_OK == return_value) {
		PORTD |= (1 << 6);  // Error indicator
		} else {
		PORTD &= ~(1 << 6);
	}

	// Send function code to motion ECU
	return_value = i2c_master_write_byte(&i2c_config, motion_function_code);
	if (E_NOT_OK == return_value) {
		PORTD |= (1 << 7);  // Error indicator
		} else {
		PORTD &= ~(1 << 7);
	}

	i2c_master_stop(&i2c_config);  // Stop I2C
	_delay_ms(2000);               // Delay between commands

	// Prepare next function code
	motion_function_code++;
	if (motion_function_code > 0x8A) {
		motion_function_code = 0x81;  // Loop back to first command
	}
}
