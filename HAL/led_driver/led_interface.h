

#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_



/*******************************************************************************
 *                                LIB MATH                                     *
 *******************************************************************************/

#include "../../LIB/STD_TYPES.h"




/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void HLED_Init(u8 Copy_u8Port,u8 Copy_u8Pin);
void HLED_TurnOn(u8 Copy_u8Port,u8 Copy_u8Pin);
void HLED_TurnOFF(u8 Copy_u8Port,u8 Copy_u8Pin);



#endif /* LED_INTERFACE_H_ */