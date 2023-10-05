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
EN_timerError_t MTIMER0_CompareOutputMode(u8 u8_arg_Mode,u8 u8_arg_COM);
EN_timerError_t MTIMER0_PWMDutyCycle(u8 u8_arg_DutyCycle);

EN_timerError_t MTIMER0_DelayInterrupt_MS(u32 u32_arg_Delay);
EN_timerError_t MTIMER0_Delay_MS(u32 u32_arg_Delay);

EN_timerError_t MTIMER0_SetPreLoad(u16 u16_arg_PreLoad);

EN_timerError_t MTIMER0_SetCompareMatchValue(u8 u8_arg_CompareMatchValue);

u8    MTIMER0_u8CheckOverFlow(void);
u8    MTIMER0_u8CheckCompareMatchMode(void);

EN_timerError_t MTIMER0_SetCallBack_REQUIREDTIME(void (*TIMER0_OF_RT_ISR)(void));
EN_timerError_t MTIMER0_SetCallBack_OverFlow(void(*TIMER0_OF_ISR)(void));
EN_timerError_t MTIMER0_SetCallBack_CompareMatchValue(void(*TIMER0_CMV_ISR)(void));



#endif
