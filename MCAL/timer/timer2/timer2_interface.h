


#ifndef TIMER2_INTERFACE_H_
#define TIMER2_INTERFACE_H_

/*******************************************************************************
 *                               standard LIBS                                  *
 *******************************************************************************/

#include "../../../LIB/STD_TYPES.h"



/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	TIMER2_OK,TIMER2_NOT_OK
}EN_timer2_Error_t;


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

EN_timer2_Error_t MTIMER2_Init(u8 u8_arg_Mode,u8 u8_arg_PreScaler);

EN_timer2_Error_t MTIMER2_PWM_init(void);

EN_timer2_Error_t MTIMER2_SetPWMNormalMode_DutyCycle(u8 u8_arg_DutyCycle);



#endif /* TIMER2_INTERFACE_H_ */