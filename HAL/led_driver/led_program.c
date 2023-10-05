

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
/*******************************************************************************
 *                                LED Initialization Function                   *
 *******************************************************************************/
EN_LEDErrorState_t HLED_Init(u8 Copy_u8Port,u8 Copy_u8Pin)
{
	EN_LEDErrorState_t errorStatus=LED_OK;
	if(!MDIO_SetPinDirection(Copy_u8Port,Copy_u8Pin,PIN_OUT))
	{
		errorStatus=LED_NOT_OK;
	}
	return errorStatus;
}



/*******************************************************************************
 *                                Turn on LED Function                            *
 *******************************************************************************/
EN_LEDErrorState_t HLED_TurnOn(u8 Copy_u8Port,u8 Copy_u8Pin)
{
		EN_LEDErrorState_t errorStatus=LED_OK;
		if(!MDIO_SetPinValue(Copy_u8Port,Copy_u8Pin,PIN_HIGH))
		{
			errorStatus=LED_NOT_OK;
		}
		return errorStatus;
}


/*******************************************************************************
 *                                Turn off LED Function                            *
 *******************************************************************************/
EN_LEDErrorState_t HLED_TurnOFF(u8 Copy_u8Port,u8 Copy_u8Pin)
{
	EN_LEDErrorState_t errorStatus=LED_OK;
	if(!MDIO_SetPinValue(Copy_u8Port,Copy_u8Pin,PIN_LOW))
	{
		errorStatus=LED_NOT_OK;
	}
	return errorStatus;
}

/*******************************************************************************
 *                                Toggle LED Function                            *
 *******************************************************************************/
EN_LEDErrorState_t HLED_Toggle(u8 Copy_u8Port,u8 Copy_u8Pin)
{
	EN_LEDErrorState_t errorStatus=LED_OK;
	if(!MDIO_TogglePinValue(Copy_u8Port,Copy_u8Pin))
	{
		errorStatus=LED_NOT_OK;
	}
	return errorStatus;
}
