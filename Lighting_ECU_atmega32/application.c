/***************************************************************************
 * @file        lighting_ecu_slave.c
 * @author      Embedded Systems Team
 * @date        03/03/2025
 * @brief       I2C Slave Firmware for Lighting ECU
 * 
 * This file implements the firmware logic for an I2C slave device that acts 
 * as the Lighting ECU in a distributed automotive system. It receives commands 
 * from the Master ECU and performs actions on the car's front lights, brake lights, 
 * and hazard lights accordingly. It utilizes TWI (I2C) communication with 
 * interrupt-based reception.
 *
 * @hardware    AVR Microcontroller
 * @peripherals I2C (TWI), GPIO (for controlling LEDs/lights)
 * 
 * @dependencies 
 *  - application.h
 *  - lighting services, LDR services
 *  - i2c.h (includes TWSR and TWDR definitions)
 * 
 * ***************************************************************************/

/*---------------------------- Includes -------------------------------------*/
#include "application.h"

/*------------------------ Configuration Defines ---------------------------*/
#define SLAVE_ADDRESS 0x60  /**< 7-bit slave address matching master config */

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

/*-------------------- I2C Object Initialization ---------------------------*/
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

/*------------------------ Function Prototypes -----------------------------*/
void application_intialize(void);
void func(uint8 var);

/*------------------------ I2C Interrupt Handler ---------------------------*/
/**
 * @brief I2C interrupt service routine for slave.
 *        Stores received data and invokes an LED blink test.
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

/*----------------------------- Main Function ------------------------------*/
int main(void) {
    application_intialize();  /**< Initialize subsystems */
    rx_buffer = 0;            /**< Set default buffer value */
    func(3);                  /**< Blink 3 times on startup */
    
    while (1) {
        /* Check rx_buffer and take corresponding action */
        switch(rx_buffer) {
            case 0x80:
                Front_Light_Right_ON();
                rx_buffer = 0; /**< Reset buffer after processing */
				break;
            case 0x81:
                Front_Light_Right_OFF();
                rx_buffer = 0; /**< Reset buffer after processing */
				break;
            case 0x82:
                Front_Light_Left_ON();
                rx_buffer = 0; /**< Reset buffer after processing */
				break;
            case 0x83:
                Front_Light_Left_OFF();
                rx_buffer = 0; /**< Reset buffer after processing */ 
				break;
            case 0x84:
                Front_Light_ALL_ON();
                rx_buffer = 0; /**< Reset buffer after processing */
				break;
            case 0x85:
                Front_Light_ALL_OFF();
                rx_buffer = 0; /**< Reset buffer after processing */ 
				break;
            case 0x86:
                Break_Light_Full();
                rx_buffer = 0; /**< Reset buffer after processing */ 
				break;
            case 0x87:
                Break_Light_Defult();
                rx_buffer = 0; /**< Reset buffer after processing */ 
				break;
            case 0x88:
                Hazard_Light_Right_ON();
                rx_buffer = 0; /**< Reset buffer after processing */ 
				break;
            case 0x89:
                Hazard_Light_Right_OFF();
                rx_buffer = 0; /**< Reset buffer after processing */ 
				break;
            case 0x8A:
                Hazard_Light_Left_ON();
                rx_buffer = 0; /**< Reset buffer after processing */ 
				break;
            case 0x8B:
                Hazard_Light_Left_OFF();
                rx_buffer = 0; /**< Reset buffer after processing */ 
				break;
            case 0x8C:
                Hazard_Light_ALL_ON();
                rx_buffer = 0; /**< Reset buffer after processing */ 
				break;
            case 0x8D:
                Hazard_Light_ALL_OFF();
                rx_buffer = 0; /**< Reset buffer after processing */
				break;
            case 0x8E:
                Hazard_Light_Emergancy_ON();
                rx_buffer = 0; /**< Reset buffer after processing */ 
				break;
            case 0x8F:
                Hazard_Light_Emergancy_OFF(); 
				rx_buffer = 0; /**< Reset buffer after processing */
				break;
            default:
                /**< Unknown command */
                break;
        }
    }
    return 0;
}

/*--------------------- Application Initialization -------------------------*/
/**
 * @brief Initializes application services and I2C slave.
 */
void application_intialize(void) {
    Std_ReturnType ret = E_OK;
    
    Lighting_Services_Initialize();  /**< Initialize lighting hardware */
    Break_Light_Defult();           /**< Set default brake light state */
    LDR_Services_Initialize();      /**< Initialize light-dependent resistor service */
    i2c_init(&slave_i2c_obj);       /**< Configure and initialize I2C */

    if (ret != E_OK) {
        /* Optional: Handle failure case */
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

