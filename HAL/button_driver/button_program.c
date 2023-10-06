
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/exti/exti_interface.h"
#include "../../MCAL/exti/exti_config.h"
#include "../../MCAL/dio/dio_interface.h"
#include "button_interface.h"
#include "button_config.h"

/*
*
* Description :
* This function allows the user to define specific Pin to Polling in it unit the button is pressed
*  the default input is High , then the button should apply low value if it's pressed.
*/
EN_buttonState_t HBTTN_IsButtonPressed(u8 u8_Arg_PortNumber ,  u8 u8_Arg_binNumber)
{
	EN_buttonState_t errorStatus=BUTTON_OK;
	errorStatus= MDIO_SetPinDirection(u8_Arg_PortNumber,u8_Arg_binNumber,PIN_IN);
	errorStatus=MDIO_SetPullupResistor(u8_Arg_PortNumber,u8_Arg_binNumber);
    //Polling unit the input equals LOW
	while(MDIO_u8GetPinValue(u8_Arg_PortNumber,u8_Arg_binNumber)!=0);

return errorStatus;
}

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