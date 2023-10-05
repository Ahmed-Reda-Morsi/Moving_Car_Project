


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

EN_timer2_Error_t MTIMER2_Init(u8 Copy_u8Mode,u8 Copy_u8PreScaler);
EN_timer2_Error_t MTIMER2_SetCallBack_OverFlow(void(*TIMER2_OF_ISR)(void));

EN_timer2_Error_t MTIMER2_SetPWMNormalMode_DutyCycle(u8 u8_Local_DutyCycle);


#endif /* TIMER2_INTERFACE_H_ */