/**************************************************************************/
/*Author            : Ahmed Reda Morsi                                    */
/*Version           : V1.0.0                                              */
/*Date              : 28 April 2023                                       */
/*Description       :button_interface.h                                   */
/**************************************************************************/
#ifndef BUTTON_INTERFACE_H_
#define BUTTON_INTERFACE_H_
#include "../../LIB/STD_TYPES.h"
/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
    BUTTON_OK,BUTTON_NOT_OK
}EN_buttonState_t;

typedef enum
{
    EXTI0,EXTI1,EXTI2
}EN_extiNumber_t;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
EN_buttonState_t HBTTN_SetButtonPressedCallBack(void (*ptr_arg_pFunctionISR_INT_N)(void), EN_extiNumber_t enum_arg_EXTI_Number);

EN_buttonState_t HBTTN_IsButtonPressed(u8 u8_Arg_PortNumber ,  u8 u8_Arg_binNumber);
#endif /* BUTTON_INTERFACE_H_ */