/*
 * mcal_std_types.h
 *
 * Created: 12/3/2024 4:26:49 AM
 *  Author: AhmedShawada
 */ 


#ifndef MCAL_STD_TYPES_H_
#define MCAL_STD_TYPES_H_

/*Section       :         Includes                */
#include "std_libraries.h"
#include "compiler.h"

/*Section       :         Data type Deceleration                 */
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;

typedef signed char sint8;
typedef signed short sint16;
typedef signed int sint32;
typedef uint8 Std_ReturnType;
/*Section       :         Macro Deceleration                */
#define STD_HIGH             0x01
#define STD_LOW              0x00

#define STD_ON               0x01
#define STD_OFF              0x00

#define STD_ACTIVE           0x01
#define STD_IDLE             0x00

#define E_OK                 (Std_ReturnType)0x01
#define E_NOT_OK             (Std_ReturnType)0x00

#define CONFIG_ENABLE        0x01
#define CONFIG_DISABLE       0x00
#define ZERO_INIT            0


/*Section       :         Macro Function Deceleration                */


/*Section       :         Function Deceleration                */




#endif /* MCAL_STD_TYPES_H_ */