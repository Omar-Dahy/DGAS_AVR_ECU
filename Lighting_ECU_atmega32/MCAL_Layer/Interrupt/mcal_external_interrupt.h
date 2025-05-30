/*
 * File   :  mcal_external_interrupt.h
 * https://www.linkedin.com/in/ahmed-shawada/
 * Created: 12/9/2024 11:08:21 PM
 * Author: AhmedShawada
 */ 



#ifndef MCAL_EXTERNAL_INTERRUPT_H_
#define MCAL_EXTERNAL_INTERRUPT_H_

/*Section       :         Includes                */
#include "mcal_interrupt_config.h"

/*Section       :         Data type Deceleration                 */
typedef void (*InterruptHandler)(void);

typedef enum
{
	INTERRUPT_EXTERNAL_INT0 = 0,
	INTERRUPT_EXTERNAL_INT1,
	INTERRUPT_EXTERNAL_INT2
}interrupt_INTx_scr;

typedef enum
{
	INTERRUPT_FALLING_EDGE = 0,
	INTERRUPT_RISING_EDGE
}interrupt_INTx_edge;

typedef struct
{
	void (* EXT_InterruptHandler)(void);
	interrupt_INTx_scr source;
	interrupt_INTx_edge edge;
	pin_config_t mcu_pin;
}interrupt_INTx_t;

/*Section       :         Macro Deceleration                */



/*Section       :         Macro Function Deceleration                */
#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* This routine clears the interrupt enable for the external interrupt, INT0 */
#define EXT_INT0_InterruptDisable()         CLEAR_BIT(GICR,INT0)
/* This routine sets the interrupt enable for the external interrupt, INT0 */
#define EXT_INT0_InterruptEnable()          SET_BIT(GICR,INT0)
/* This routine clears the interrupt flag for the external interrupt, INT0 */
#define EXT_INT0_InterruptFlagClear()       CLEAR_BIT(GIFR,INTF0)
/* This routine set the edge detect of the extern interrupt to negative edge */
#define EXT_INT0_RisingEdgeSet()		    {SET_BIT(MCUCR,ISC01); SET_BIT(MCUCR,ISC00);}
/* This routine set the edge detect of the extern interrupt to positive edge */
#define EXT_INT0_FallingEdgeSet()           {SET_BIT(MCUCR,ISC01); CLEAR_BIT(MCUCR,ISC00);}
	
/* This routine clears the interrupt enable for the external interrupt, INT1 */
#define EXT_INT1_InterruptDisable()         CLEAR_BIT(GICR,INT1)
/* This routine sets the interrupt enable for the external interrupt, INT1 */
#define EXT_INT1_InterruptEnable()          SET_BIT(GICR,INT1)
/* This routine clears the interrupt flag for the external interrupt, INT1 */
#define EXT_INT1_InterruptFlagClear()       CLEAR_BIT(GIFR,INTF1)
/* This routine set the edge detect of the extern interrupt to negative edge */
#define EXT_INT1_RisingEdgeSet()            {SET_BIT(MCUCR, ISC11); SET_BIT(MCUCR, ISC10);}
/* This routine set the edge detect of the extern interrupt to positive edge */
#define EXT_INT1_FallingEdgeSet()           {SET_BIT(MCUCR, ISC11); CLEAR_BIT(MCUCR, ISC10);}


/* This routine clears the interrupt enable for the external interrupt, INT2 */
#define EXT_INT2_InterruptDisable()         CLEAR_BIT(GICR,INT2)
/* This routine sets the interrupt enable for the external interrupt, INT2 */
#define EXT_INT2_InterruptEnable()          SET_BIT(GICR,INT2)
/* This routine clears the interrupt flag for the external interrupt, INT2 */
#define EXT_INT2_InterruptFlagClear()       CLEAR_BIT(GIFR,INTF2)
/* This routine set the edge detect of the extern interrupt to negative edge */
#define EXT_INT2_RisingEdgeSet()            SET_BIT(MCUCSR,ISC2)
/* This routine set the edge detect of the extern interrupt to positive edge */
#define EXT_INT2_FallingEdgeSet()           CLEAR_BIT(MCUCSR,ISC2)

#endif

/*Section       :         Function Deceleration                */
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *int_obj);
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj);


#endif /* MCAL_EXTERNAL_INTERRUPT_H_ */