#ifndef  TIMER_INT_H
#define TIMER_INT_H
#include "../../../LIB/STD_TYPES.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	TIMER0_OK,TIMER0_NOT_OK
}EN_timerError_t;


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

EN_timerError_t MTIMER0_Init(u8 u8_arg_Mode,u8 u8_arg_PreScaler);

EN_timerError_t MTIMER0_DelayInterrupt_MS(u32 u32_arg_Delay);

EN_timerError_t MTIMER0_SetCallBack_REQUIREDTIME(void (*TIMER0_OF_RT_ISR)(void));



#endif
