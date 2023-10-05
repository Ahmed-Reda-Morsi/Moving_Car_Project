
#ifndef EXTI_INT_H
#define EXTI_INT_H
#include "../../LIB/STD_TYPES.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	EXTI_OK,EXTI_NOT_OK
}EN_extiError_t;
/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
EN_extiError_t MEXTI_GlobalInterruptEnable(void);
EN_extiError_t MEXTI_GlobalInterruptDisable(void);

EN_extiError_t MEXTI_EnableInterrupt(u8 Copy_u8InterruptPIN,u8 Copy_u8InterruptSensingLevel);

EN_extiError_t MEXTI_DisableInterrupt(u8 Copy_u8InterruptPIN);

EN_extiError_t MEXTI_0_SET_CALL_BACK(void(*Copy_Pfunction_ISR_INT0)(void));

EN_extiError_t MEXTI_1_SET_CALL_BACK(void(*Copy_Pfunction_ISR_INT1)(void));

EN_extiError_t MEXTI_2_SET_CALL_BACK(void(*Copy_Pfunction_ISR_INT2)(void));

#endif
