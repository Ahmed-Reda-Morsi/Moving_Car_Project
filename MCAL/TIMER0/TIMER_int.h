#ifndef  TIMER_INT_H
#define TIMER_INT_H
#include "../../LIB/STD_TYPES.h"

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

EN_timerError_t MTIMER0_Init(u8 Copy_u8Mode,u8 Copy_u8PreScaler);
EN_timerError_t MTIMER0_CompareOutputMode(u8 Copy_u8Mode,u8 Copy_u8COM);
EN_timerError_t MTIMER0_PWMDutyCycle(u8 Copy_u8DutyCycle);

EN_timerError_t MTIMER0_DelayInterrupt_MS(u32 Copy_u32Delay);
EN_timerError_t MTIMER0_Delay_MS(u32 Copy_u32Delay);

EN_timerError_t MTIMER0_SetPreLoad(u16 Copy_u16PreLoad);

EN_timerError_t MTIMER0_SetCompareMatchValue(u8 Copy_u8CompareMatchValue);

u8    MTIMER0_u8CheckOverFlow(void);
u8    MTIMER0_u8CheckCompareMatchMode(void);

EN_timerError_t MTIMER0_SetCallBack_REQUIREDTIME(void (*TIMER0_OF_RT_ISR)(void));
EN_timerError_t MTIMER0_SetCallBack_OverFlow(void(*TIMER0_OF_ISR)(void));
EN_timerError_t MTIMER0_SetCallBack_CompareMatchValue(void(*TIMER0_CMV_ISR)(void));



#endif
