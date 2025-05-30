/*
 * lighting_interface.h
 * 
 * Created: 1/27/2025 12:54:57 PM
 * Author: DGAS
 */ 


#ifndef LIGHTING_INTERFACE_H_
#define LIGHTING_INTERFACE_H_

/*Section       :         Includes                */
#include "ecu_led.h"
#include "hal_timer0.h"
#include "hal_timer1.h"

/*Section       :         Data type Deceleration                 */



/*Section       :         Macro Deceleration                */



/*Section       :         Macro Function Deceleration                */



/*Section       :         Function Deceleration                */
Std_ReturnType Lighting_Services_Initialize(void);

Std_ReturnType Front_Light_Right_ON(void);
Std_ReturnType Front_Light_Right_OFF(void);
Std_ReturnType Front_Light_Left_ON(void);
Std_ReturnType Front_Light_Left_OFF(void);
Std_ReturnType Front_Light_ALL_ON(void);
Std_ReturnType Front_Light_ALL_OFF(void);

Std_ReturnType Break_Light_Defult(void);
Std_ReturnType Break_Light_Full(void);

Std_ReturnType Hazard_Light_Right_ON(void);
Std_ReturnType Hazard_Light_Right_OFF(void);
Std_ReturnType Hazard_Light_Left_ON(void);
Std_ReturnType Hazard_Light_Left_OFF(void);
Std_ReturnType Hazard_Light_ALL_ON(void);
Std_ReturnType Hazard_Light_ALL_OFF(void);

Std_ReturnType Hazard_Light_Emergancy_ON(void);
Std_ReturnType Hazard_Light_Emergancy_OFF(void);


#endif /* LIGHTING_INTERFACE_H_ */