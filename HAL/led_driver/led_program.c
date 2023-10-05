

/*******************************************************************************
 *                                LIB MATH                                     *
 *******************************************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"


/*******************************************************************************
 *                                DIO LIB                                      *
 *******************************************************************************/
#include "../../MCAL/dio/dio_interface.h"

#include "led_interface.h"
#include "led_config.h"
#include "led_interface.h"

/*
 * Description:
 * This function initializes a specific LED pin on a given port, enabling it for use and returns error status.
 */

EN_LEDErrorState_t HLED_Init(u8 u8_arg_Port,u8 u8_arg_Pin)
{
	EN_LEDErrorState_t enum_Local_errorStatus=LED_OK;
	if(!MDIO_SetPinDirection(u8_arg_Port,u8_arg_Pin,PIN_OUT))
	{
		enum_Local_errorStatus=LED_NOT_OK;
	}
	return enum_Local_errorStatus;
}


/*
 * Description:
 * This function turns on the specified LED by setting the corresponding pin on the given
 * port to a logic high level and returns an error status.
 */
EN_LEDErrorState_t HLED_TurnOn(u8 u8_arg_Port,u8 u8_arg_Pin)
{
		EN_LEDErrorState_t enum_Local_errorStatus=LED_OK;
		if(!MDIO_SetPinValue(u8_arg_Port,u8_arg_Pin,PIN_HIGH))
		{
			enum_Local_errorStatus=LED_NOT_OK;
		}
		return enum_Local_errorStatus;
}

/*
 * Description:
 * This function turns off the specified LED by setting the corresponding pin on the
 * given port to a logic low level and returns the error status.
 */

EN_LEDErrorState_t HLED_TurnOFF(u8 u8_arg_Port,u8 u8_arg_Pin)
{
	EN_LEDErrorState_t enum_Local_errorStatus=LED_OK;
	if(!MDIO_SetPinValue(u8_arg_Port,u8_arg_Pin,PIN_LOW))
	{
		enum_Local_errorStatus=LED_NOT_OK;
	}
	return enum_Local_errorStatus;
}

/*
 * Description:
 * This function toggles the state of the specified LED. If the LED is currently on,
 * it will be turned off, and vice versa. The function achieves this by inverting the logic 
 * level of the corresponding pin on the given port and returns the error status.
 */

EN_LEDErrorState_t HLED_Toggle(u8 u8_arg_Port,u8 u8_arg_Pin)
{
	EN_LEDErrorState_t enum_Local_errorStatus=LED_OK;
	if(!MDIO_TogglePinValue(u8_arg_Port,u8_arg_Pin))
	{
		enum_Local_errorStatus=LED_NOT_OK;
	}
	return enum_Local_errorStatus;
}
