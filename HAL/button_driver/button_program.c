/**************************************************************************/
/*Author            : Ahmed Reda Morsi                                    */
/*Version           : V1.0.0                                              */
/*Date              : 28 April 2023                                       */
/*Description       :button_program.h                                   */
/**************************************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/exti/exti_interface.h"
#include "../../MCAL/exti/exti_config.h"

#include "button_interface.h"
#include "button_config.h"


/*
 * Description :
 * This function allows the user to define a callback function that will be called when a
 * specific button is pressed. It sets up the necessary configurations and associations between
 * the button and the corresponding external interrupt.
 */

EN_buttonState_t HBTTN_SetButtonPressedCallBack(void (*ptr_arg_pFunctionISR_INT_N)(void), EN_extiNumber_t enum_arg_EXTI_Number)
{
    EN_buttonState_t enum_Local_errorStatus = BUTTON_OK;
    if (ptr_arg_pFunctionISR_INT_N != NULL_PTR)

    {
        switch (enum_arg_EXTI_Number)
        {
        case EXTI0:
            MEXTI_0_SET_CALL_BACK(ptr_arg_pFunctionISR_INT_N);
			MEXTI_EnableInterrupt(INT0_PIN,RISING_EDGE);

            break;

        case EXTI1:
            MEXTI_1_SET_CALL_BACK(ptr_arg_pFunctionISR_INT_N);
			MEXTI_EnableInterrupt(INT1_PIN,RISING_EDGE);

            break;
        case EXTI2:
             MEXTI_1_SET_CALL_BACK(ptr_arg_pFunctionISR_INT_N);
			 MEXTI_EnableInterrupt(INT2_PIN,RISING_EDGE);

            break;

        default:
         enum_Local_errorStatus=BUTTON_NOT_OK;
        }
    }
    else
    {
        enum_Local_errorStatus=BUTTON_NOT_OK;
    }
	return enum_Local_errorStatus;
}