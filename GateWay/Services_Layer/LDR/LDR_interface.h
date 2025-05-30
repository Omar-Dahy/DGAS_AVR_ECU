/*
 * LDR_interface.h
 *
 * Created: 1/27/2025 6:39:19 PM
 *  Author: AhmedShawada
 */ 


#ifndef LDR_INTERFACE_H_
#define LDR_INTERFACE_H_

/*Section       :         Includes                */
#include "hal_adc.h"
#include "lighting_interface.h"


/*Section       :         Data type Deceleration                 */


/*Section       :         Macro Deceleration                */
//#define LIGHT_REFRANCE  450


/*Section       :         Macro Function Deceleration                */


/*Section       :         Function Deceleration                */
Std_ReturnType LDR_Services_Initialize(void);
Std_ReturnType LDR1_Read(void);
Std_ReturnType LDR2_Read(void);
Std_ReturnType LDR3_Read(void);
Std_ReturnType LDR4_Read(void);
Std_ReturnType LDRS_Automation (void);
Std_ReturnType dynamic_threshold_write(uint16 new_dynamic_threshold);


#endif /* LDR_INTERFACE_H_ */