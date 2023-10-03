/**************************************************************************/
/*Author            : Ahmed Reda Morsi                                    */
/*Version           : V1.0.0                                              */
/*Date              : 28 April 2023                                       */
/*Description       :button_interface.h                                   */
/**************************************************************************/
#ifndef BUTTON_INTERFACE_H_
#define BUTTON_INTERFACE_H_
typedef enum
{
    BUTTON_OK,BUTTON_NOT_OK
}EN_buttonState_t;

typedef enum
{
    EXTI0,EXTI1,EXTI2
}EN_extiNumber_t;

EN_buttonState_t HBTTN_SetButtonPressedCallBack(void (*Copy_Pfunction_ISR_INT_N)(void), EN_extiNumber_t Copy_EXTI_Number);

#endif /* BUTTON_INTERFACE_H_ */