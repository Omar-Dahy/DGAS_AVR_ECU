/*
 * File   :  mcal_interrupt_gen_cfg.h
 * https://www.linkedin.com/in/ahmed-shawada/
 * Created: 12/9/2024 11:09:53 PM
 * Author: AhmedShawada
 */ 



#ifndef MCAL_INTERRUPT_GEN_CFG_H_
#define MCAL_INTERRUPT_GEN_CFG_H_

/*Section       :         Macro Deceleration                */

#define INTERRUPT_FEATURE_ENABLE 1U

/*=============== INTx INTERRUPT FEATURE ENABLE ===============*/

#define EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE				INTERRUPT_FEATURE_ENABLE

/*=============== ADC INTERRUPT FEATURE ENABLE ===============*/

#define ADC_INTERRUPT_FEATURE_ENABLE						INTERRUPT_FEATURE_ENABLE

/*=============== SPI INTERRUPT FEATURE ENABLE ===============*/

#define SPI_INTERRUPT_FEATURE_ENABLE					INTERRUPT_FEATURE_ENABLE

/*=============== I2C INTERRUPT FEATURE ENABLE ===============*/

#define I2C_INTERRUPT_FEATURE_ENABLE                   INTERRUPT_FEATURE_ENABLE

/*=============== TIMER0 INTERRUPT FEATURE ENABLE ===============*/

#define TMR0_COMPARE_INTERRUPT_FEATURE_ENABLE		   INTERRUPT_FEATURE_ENABLE
#define TMR0_OVERFLOW_INTERRUPT_FEATURE_ENABLE		   INTERRUPT_FEATURE_ENABLE

/*=============== TIMER1 INTERRUPT FEATURE ENABLE ===============*/

#define TMR1_CAPTURE_INTERRUPT_FEATURE_ENABLE		   INTERRUPT_FEATURE_ENABLE
#define TMR1_COMPARE_A_INTERRUPT_FEATURE_ENABLE		   INTERRUPT_FEATURE_ENABLE
#define TMR1_COMPARE_B_INTERRUPT_FEATURE_ENABLE		   INTERRUPT_FEATURE_ENABLE
#define TMR1_OVERFLOW_INTERRUPT_FEATURE_ENABLE		   INTERRUPT_FEATURE_ENABLE

#endif /* MCAL_INTERRUPT_GEN_CFG_H_ */