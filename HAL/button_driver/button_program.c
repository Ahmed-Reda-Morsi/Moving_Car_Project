/**************************************************************************/
/*Author            : Ahmed Reda Morsi                                    */
/*Version           : V1.0.0                                              */
/*Date              : 28 April 2023                                       */
/*Description       :button_program.h                                   */
/**************************************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/exti/exti_interface.h"
#include "button_interface.h"
#include "button_config.h"

EN_buttonState_t HBTTN_ButtonPressed(void (*Copy_Pfunction_ISR_INT_N)(void), EN_extiNumber_t Copy_EXTI_Number)
{
    EN_buttonState_t errorStatus = BUTTON_OK;
    if (Copy_Pfunction_ISR_INT_N != NULL_PTR)

    {
        switch (Copy_EXTI_Number)
        {
        case EXTI0:
            MEXTI_MEXTI_0_SET_CALL_BACK(Copy_Pfunction_ISR_INT_N);
            break;

        case EXTI1:
            MEXTI_MEXTI_1_SET_CALL_BACK(Copy_Pfunction_ISR_INT_N);
            break;
        case EXTI2:
             MEXTI_MEXTI_2_SET_CALL_BACK(Copy_Pfunction_ISR_INT_N);
            break;

        default:
         errorStatus=BUTTON_NOT_OK;
        }
    }
    else
    {
        errorStatus=BUTTON_NOT_OK;
    }
}