
#include "MCAL/dio/dio_interface.h"
#include "MCAL/timer/timer0/timer0_interface.h"
#include "MCAL/timer/timer0/timer0_config.h"

int main(void)
{
    /* Replace with your application code */
	MDIO_SetPinDirection(PORTC,5,PIN_OUT);
	MTIMER0_Init(TIMER0_NORMAL_MODE,TIMER0_CS_PRESCALLER_8);
	MDIO_SetPinValue(PORTC,5,PIN_HIGH);
    while (1) 
    {	
		MDIO_SetPinValue(PORTC,5,PIN_HIGH);
	    MTIMER0_Delay_MS(1000);
	   MDIO_SetPinValue(PORTC,5,PIN_LOW);
	   MTIMER0_Delay_MS(1000);


    }
}

