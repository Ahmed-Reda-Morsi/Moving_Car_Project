
#include "led_interface.h"
#include "led_config.h"
#include "led_interface.h"
/*******************************************************************************
 *                                LIB MATH                                     *
 *******************************************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"


/*******************************************************************************
 *                                DIO LIB                                      *
 *******************************************************************************/
#include "../../MCAL/dio/dio_interface.h"






/*******************************************************************************
 *                                LED Initialization Function                   *
 *******************************************************************************/
void HLED_Init(u8 Copy_u8Port,u8 Copy_u8Pin)
{
	MDIO_SetPinDirection(Copy_u8Port,Copy_u8Pin,PIN_OUT);
}



/*******************************************************************************
 *                                Turn on LED Function                            *
 *******************************************************************************/
void HLED_TurnOn(u8 Copy_u8Port,u8 Copy_u8Pin)
{
	MDIO_SetPinValue(Copy_u8Port,Copy_u8Pin,PIN_HIGH);
}


/*******************************************************************************
 *                                Turn off LED Function                            *
 *******************************************************************************/
void HLED_TurnOFF(u8 Copy_u8Port,u8 Copy_u8Pin)
{
	MDIO_SetPinValue(Copy_u8Port,Copy_u8Pin,PIN_LOW);
}
