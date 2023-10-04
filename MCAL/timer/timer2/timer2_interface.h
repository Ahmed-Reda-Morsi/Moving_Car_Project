


#ifndef TIMER2_INTERFACE_H_
#define TIMER2_INTERFACE_H_

/*******************************************************************************
 *                               standard LIBS                                  *
 *******************************************************************************/

#include "../../LIB/STD_TYPES.h"



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
EN_timer2_Error_t MTIMER2_CompareOutputMode(u8 Copy_u8Mode,u8 Copy_u8COM);
EN_timer2_Error_t MTIMER2_PWMDutyCycle(u8 Copy_u8DutyCycle);

EN_timer2_Error_t MTIMER2_SetPreLoad(u16 Copy_u16PreLoad);
EN_timer2_Error_t MTIMER2_SetCompareMatchValue(u8 Copy_u8CompareMatchValue);
u8    MTIMER2_u8CheckOverFlow(void);
u8    MTIMER2_u8CheckCompareMatchMode(void);
EN_timer2_Error_t MTIMER2_SetCallBack_OverFlow(void(*TIMER2_OF_ISR)(void));
void MTIMER2_SetCallBack_CompareMatchValue(void(*TIMER2_CMV_ISR)(void));



#endif /* TIMER2_INTERFACE_H_ */