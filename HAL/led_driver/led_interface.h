

#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

/*******************************************************************************
 *                               LED Enum errorState                           *
 *******************************************************************************/
typedef enum
{
	LED_OK,LED_NOT_OK
	}EN_LEDErrorState_t;

/*******************************************************************************
 *                                LIB MATH                                     *
 *******************************************************************************/

#include "../../LIB/STD_TYPES.h"



/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

EN_LEDErrorState_t HLED_Init(u8 Copy_u8Port,u8 Copy_u8Pin);
EN_LEDErrorState_t HLED_TurnOn(u8 Copy_u8Port,u8 Copy_u8Pin);
EN_LEDErrorState_t HLED_TurnOFF(u8 Copy_u8Port,u8 Copy_u8Pin);
EN_LEDErrorState_t HLED_Toggle(u8 Copy_u8Port,u8 Copy_u8Pin);


#endif /* LED_INTERFACE_H_ */