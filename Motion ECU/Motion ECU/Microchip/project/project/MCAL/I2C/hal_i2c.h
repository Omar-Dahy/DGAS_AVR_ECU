/*
 * File   :  hal_i2c.h
 * https://www.linkedin.com/in/ahmed-shawada/
 * Created: 12/20/2024 11:11:39 PM
 * Author: AhmedShawada
 */ 

#ifndef HAL_I2C_H_
#define HAL_I2C_H_

/* Includes */
#include <avr/io.h>
#include "mcal_std_types.h"
#include "hal_gpio.h"
#include "mcal_internal_interrupt.h"

/* Data Type Declarations */
typedef enum {
    I2C_MASTER_MODE = 0,
    I2C_SLAVE_MODE
} i2c_mode_t;

typedef enum {
    I2C_PRESCALER_1 = 0,
    I2C_PRESCALER_4,
    I2C_PRESCALER_16,
    I2C_PRESCALER_64
} i2c_prescaler_t;

typedef struct {
    i2c_mode_t mode;                     /* Master or Slave mode */
    uint32_t clock;                      /* I2C clock frequency (Hz, for master mode) */
    i2c_prescaler_t prescaler;           /* Prescaler for master mode */
    uint8_t master_address;              /* 7-bit master address (if used) */
    uint8_t slave_address;               /* 7-bit slave address */
    uint8_t interrupt_enable;            /* Enable interrupts (1 = enable, 0 = disable) */
#if I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*interrupt_handler)(void);     /* Interrupt callback */
#endif
} i2c_t;

/* Macro Declarations */
#define I2C_STATUS_MASK             0xF8

/* Master Status Codes */
#define I2C_START_ACK               0x08
#define I2C_REP_START_ACK           0x10
#define I2C_SLA_W_ACK               0x18
#define I2C_SLA_R_ACK               0x40
#define I2C_MSTR_WR_ACK             0x28
#define I2C_MSTR_RD_ACK             0x50
#define I2C_MSTR_RD_NACK            0x58

/* Slave Status Codes */
#define I2C_SLA_W_RCVD_ACK          0x60
#define I2C_SLA_R_RCVD_ACK          0xA8
#define I2C_SLV_DATA_RCVD_ACK       0x80
#define I2C_SLV_DATA_SENT_ACK       0xB8
#define I2C_SLV_STOP_RCVD	        0xA0

/* Macro Function Declarations */
#define I2C_ENABLE()                (TWCR |= (1 << TWEN))
#define I2C_DISABLE()               (TWCR &= ~(1 << TWEN))
#define I2C_CLEAR_INTERRUPT()		(TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN) | (1 << TWIE))
#define I2C_FLAG_STATUS()           (TWCR & (1 << TWINT))
#define I2C_ENABLE_ACK()            (TWCR |= (1 << TWEA))
#define I2C_DISABLE_ACK()           (TWCR &= ~(1 << TWEA))
#define I2C_START()                 (TWCR |= (1 << TWSTA))
#define I2C_CLEAR_START()           (TWCR &= ~(1 << TWSTA))
#define I2C_STOP()                  (TWCR |= (1 << TWSTO))
#define I2C_CLEAR_STOP()            (TWCR &= ~(1 << TWSTO))

/* Function Declarations */
Std_ReturnType i2c_init(const i2c_t *i2c);
Std_ReturnType i2c_deinit(const i2c_t *i2c);
Std_ReturnType i2c_master_start(const i2c_t *i2c);
Std_ReturnType i2c_master_repeated_start(const i2c_t *i2c);
Std_ReturnType i2c_master_stop(const i2c_t *i2c);
Std_ReturnType i2c_master_write_address(const i2c_t *i2c, uint8_t address, uint8_t rw);
Std_ReturnType i2c_master_write_byte(const i2c_t *i2c, uint8_t data);
Std_ReturnType i2c_master_read_byte(const i2c_t *i2c, uint8_t *data, uint8_t ack);
Std_ReturnType i2c_slave_write_byte(const i2c_t *i2c, uint8_t data);
Std_ReturnType i2c_slave_read_byte(const i2c_t *i2c, uint8_t *data);

#endif /* HAL_I2C_H_ */