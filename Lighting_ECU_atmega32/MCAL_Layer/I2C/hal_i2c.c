/*
 * File   :  hal_i2c.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Created: 12/20/2024 11:11:26 PM
 * Author: AhmedShawada
 */

#include "hal_i2c.h"

/* Static Function Prototypes */
static void i2c_master_set_prescaler(const i2c_t *i2c);
static void i2c_master_set_clock(const i2c_t *i2c);
static void i2c_interrupt_init(const i2c_t *i2c);
static Std_ReturnType i2c_wait_for_flag(void);

/* Interrupt Callback */
#if I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*i2c_interrupt_callback)(void) = NULL;
#endif

Std_ReturnType i2c_init(const i2c_t *i2c) {
    if (i2c == NULL) {
        return E_NOT_OK;
    }

    /* Disable I2C */
    I2C_DISABLE();

    /* Configure mode */
    if (i2c->mode == I2C_MASTER_MODE) {
        i2c_master_set_prescaler(i2c);
        i2c_master_set_clock(i2c);
        if (i2c->master_address != 0) {
            TWAR = (i2c->master_address << 1); /* 7-bit address */
        }
    } else if (i2c->mode == I2C_SLAVE_MODE) {
        TWAR = (i2c->slave_address << 1); /* 7-bit address */
    }

    /* Configure interrupts */
    if (i2c->interrupt_enable) {
        i2c_interrupt_init(i2c);
    }

    /* Enable ACK */
    I2C_ENABLE_ACK();

    /* Enable I2C */
    I2C_ENABLE();

    return E_OK;
}

Std_ReturnType i2c_deinit(const i2c_t *i2c) {
    if (i2c == NULL) {
        return E_NOT_OK;
    }

    /* Disable I2C */
    I2C_DISABLE();

    /* Disable interrupts */
#if I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    TWCR &= ~(1 << TWIE);
#endif

    return E_OK;
}

Std_ReturnType i2c_master_start(const i2c_t *i2c) {
    if (i2c == NULL) {
        return E_NOT_OK;
    }

    I2C_CLEAR_INTERRUPT();
    I2C_START();
    I2C_ENABLE();
    if (i2c_wait_for_flag() != E_OK) {
        return E_NOT_OK;
    }

    if ((TWSR & I2C_STATUS_MASK) != I2C_START_ACK) {
        return E_NOT_OK;
    }

    return E_OK;
}

Std_ReturnType i2c_master_repeated_start(const i2c_t *i2c) {
    if (i2c == NULL) {
        return E_NOT_OK;
    }

    I2C_CLEAR_INTERRUPT();
    I2C_START();
    I2C_ENABLE();
    if (i2c_wait_for_flag() != E_OK) {
        return E_NOT_OK;
    }

    if ((TWSR & I2C_STATUS_MASK) != I2C_REP_START_ACK) {
        return E_NOT_OK;
    }

    return E_OK;
}

Std_ReturnType i2c_master_stop(const i2c_t *i2c) {
    if (i2c == NULL) {
        return E_NOT_OK;
    }

    I2C_CLEAR_INTERRUPT();
    I2C_STOP();
    I2C_ENABLE();

    /* No need to wait for TWSTO; it clears automatically */
    return E_OK;
}

Std_ReturnType i2c_master_write_address(const i2c_t *i2c, uint8_t address, uint8_t rw) {
    if (i2c == NULL) {
        return E_NOT_OK;
    }

    TWDR = (address << 1) | (rw & 0x01); /* 7-bit address + R/W bit */
    I2C_CLEAR_START();
    I2C_CLEAR_INTERRUPT();
    I2C_ENABLE();
    if (i2c_wait_for_flag() != E_OK) {
        return E_NOT_OK;
    }

    uint8_t expected_status = (rw ? I2C_SLA_R_ACK : I2C_SLA_W_ACK);
    if ((TWSR & I2C_STATUS_MASK) != expected_status) {
        return E_NOT_OK;
    }

    return E_OK;
}

Std_ReturnType i2c_master_write_byte(const i2c_t *i2c, uint8_t data) {
    if (i2c == NULL) {
        return E_NOT_OK;
    }

    TWDR = data;
    I2C_CLEAR_INTERRUPT();
    I2C_ENABLE();
    if (i2c_wait_for_flag() != E_OK) {
        return E_NOT_OK;
    }

    if ((TWSR & I2C_STATUS_MASK) != I2C_MSTR_WR_ACK) {
        return E_NOT_OK;
    }

    return E_OK;
}

Std_ReturnType i2c_master_read_byte(const i2c_t *i2c, uint8_t *data, uint8_t ack) {
    if (i2c == NULL || data == NULL) {
        return E_NOT_OK;
    }

    if (ack) {
        I2C_ENABLE_ACK();
    } else {
        I2C_DISABLE_ACK();
    }

    I2C_CLEAR_INTERRUPT();
    I2C_ENABLE();
    if (i2c_wait_for_flag() != E_OK) {
        return E_NOT_OK;
    }

    uint8_t expected_status = (ack ? I2C_MSTR_RD_ACK : I2C_MSTR_RD_NACK);
    if ((TWSR & I2C_STATUS_MASK) != expected_status) {
        return E_NOT_OK;
    }

    *data = TWDR;
    return E_OK;
}

Std_ReturnType i2c_slave_write_byte(const i2c_t *i2c, uint8_t data) {
    if (i2c == NULL) {
        return E_NOT_OK;
    }

    TWDR = data;
    I2C_CLEAR_INTERRUPT();
    I2C_ENABLE();
    if (i2c_wait_for_flag() != E_OK) {
        return E_NOT_OK;
    }

    if ((TWSR & I2C_STATUS_MASK) != I2C_SLV_DATA_SENT_ACK) {
        return E_NOT_OK;
    }

    return E_OK;
}

Std_ReturnType i2c_slave_read_byte(const i2c_t *i2c, uint8_t *data) {
    if (i2c == NULL || data == NULL) {
        return E_NOT_OK;
    }

    I2C_CLEAR_INTERRUPT();
    I2C_ENABLE();
    if (i2c_wait_for_flag() != E_OK) {
        return E_NOT_OK;
    }

    if ((TWSR & I2C_STATUS_MASK) != I2C_SLV_DATA_RCVD_ACK) {
        return E_NOT_OK;
    }

    *data = TWDR;
    return E_OK;
}

static void i2c_master_set_prescaler(const i2c_t *i2c) {
    TWSR &= ~(3 << TWPS0); /* Clear prescaler bits */
    switch (i2c->prescaler) {
        case I2C_PRESCALER_1:
            TWSR |= (0 << TWPS0);
            break;
        case I2C_PRESCALER_4:
            TWSR |= (1 << TWPS0);
            break;
        case I2C_PRESCALER_16:
            TWSR |= (2 << TWPS0);
            break;
        case I2C_PRESCALER_64:
            TWSR |= (3 << TWPS0);
            break;
    }
}

static void i2c_master_set_clock(const i2c_t *i2c) {
    /* SCL = F_CPU / (16 + 2 * TWBR * Prescaler) */
    uint8_t prescaler_value = (1 << (i2c->prescaler * 2)); /* 1, 4, 16, 64 */
    TWBR = ((F_CPU / i2c->clock) - 16) / (2 * prescaler_value);
}

static void i2c_interrupt_init(const i2c_t *i2c) {
#if I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    i2c_interrupt_callback = i2c->interrupt_handler;
    TWCR |= (1 << TWIE); /* Enable I2C interrupt */
    I2C_CLEAR_INTERRUPT();
    INTERRUPT_GlobalInterruptEnable(); /* Enable global interrupts */
#endif
}

static Std_ReturnType i2c_wait_for_flag(void) {
    uint16_t timeout = 10000; /* Adjust as needed */
    while (!(TWCR & (1 << TWINT))) {
        if (--timeout == 0) {
            return E_NOT_OK;
        }
    }
    return E_OK;
}

#if I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
ISR(TWI_vect) {
    I2C_CLEAR_INTERRUPT();
    if (i2c_interrupt_callback) {
        i2c_interrupt_callback();
    }
}
#endif