
#include "MCAL/timer/timer0/timer0_interface.h"
#include "MCAL/timer/timer0/timer0_config.h"
#include "MCAL/exti/exti_interface.h"
#include "HAL/button_driver/button_interface.h"
#include "HAL/led_driver/led_interface.h"
#include "HAL/led_driver/led_config.h"
#include "HAL/motor_driver/motor_interface.h"
#include "HAL/motor_driver/motor_config.h"
//_______________________________________

typedef enum
{
	CAR_ForwardOnLongSide,CAR_ForwardOnShortSide,CAR_Rotate_RightShortSide,CAR_Rotate_RightLongSide,
	CAR_STOP_BeforeLongSide,CAR_STOP_BeforeShortSide,CAR_STOP_AfterLongSide,CAR_STOP_AfterShortSide,CAR_SuddenlyStop
}EN_CarStatus_t;


static EN_CarStatus_t 	CarStatus=CAR_ForwardOnLongSide;

static u8 gaurd_EXTI=0;

void suddelly_Stop(void)
{
	HLED_TurnOn(LED_PORT,LED_LongSide);
	if(gaurd_EXTI!=0)
	{
    HMOTOR_Allstop();
	HMOTOR_set_Allspeed(0);
	HLED_TurnOFF(LED_PORT,LED_LongSide);
	HLED_TurnOFF(LED_PORT,LED_ShortSide);
	HLED_TurnOn(LED_PORT,LED_Stop);
	HLED_TurnOFF(LED_PORT,LED_Rotate);
	
	CarStatus=CAR_SuddenlyStop;
	}
}

void MOVE_CAR(void)
{
	if (CarStatus!=CAR_SuddenlyStop)
	{
		gaurd_EXTI=1;
		HLED_TurnOFF(LED_PORT,LED_LongSide);
		HLED_TurnOFF(LED_PORT,LED_ShortSide);
		HLED_TurnOFF(LED_PORT,LED_Stop);
		HLED_TurnOFF(LED_PORT,LED_Rotate);
		
		switch(CarStatus)
		{
			case CAR_ForwardOnLongSide:
				HLED_TurnOn(LED_PORT,LED_LongSide);
				HMOTORS_MovingForward();
				HMOTOR_set_Allspeed(50);
				MTIMER0_DelayInterrupt_MS(3000);
				CarStatus=CAR_STOP_AfterLongSide;
				break;
			case CAR_STOP_AfterLongSide:
				HLED_TurnOn(LED_PORT,LED_Stop);
				HMOTOR_Allstop();
				MTIMER0_DelayInterrupt_MS(500);
				CarStatus=CAR_Rotate_RightShortSide;
				break;
			case CAR_Rotate_RightShortSide:
				HLED_TurnOn(LED_PORT,LED_Rotate);
				HMOTORS_RotateRight();
				MTIMER0_DelayInterrupt_MS(1000);
				CarStatus=CAR_STOP_BeforeShortSide;
				break;
			
			case CAR_STOP_BeforeShortSide:
				HLED_TurnOn(LED_PORT,LED_Stop);
				HMOTOR_Allstop();
				MTIMER0_DelayInterrupt_MS(500);
				CarStatus=CAR_ForwardOnShortSide;
				break;
			
			case CAR_ForwardOnShortSide:
				HLED_TurnOn(LED_PORT,LED_ShortSide);
				HMOTORS_MovingForward();
				HMOTOR_set_Allspeed(30);
				MTIMER0_DelayInterrupt_MS(2000);
				CarStatus=CAR_STOP_AfterShortSide;
				break;
			
			case CAR_STOP_AfterShortSide:
				HLED_TurnOn(LED_PORT,LED_Stop);
				HMOTOR_Allstop();
				MTIMER0_DelayInterrupt_MS(500);
				CarStatus=CAR_Rotate_RightLongSide;
				break;
			
			case CAR_Rotate_RightLongSide:
				HLED_TurnOn(LED_PORT,LED_Rotate);
				HMOTORS_RotateRight();
				MTIMER0_DelayInterrupt_MS(1000);
				CarStatus=CAR_STOP_BeforeLongSide;
				break;
			
			case CAR_STOP_BeforeLongSide:
				HLED_TurnOn(LED_PORT,LED_Stop);
				HMOTOR_Allstop();
				MTIMER0_DelayInterrupt_MS(500);
				CarStatus=CAR_ForwardOnLongSide;
				break;
			default:
			break;
		}
	}
	else
	{
		
	}
	
}

void Initial_Start(void)
{
	MTIMER0_DelayInterrupt_MS(1000);
}

int main(void)
{
	HLED_Init(LED_PORT,LED_LongSide);
	//HLED_Init(LED_PORT,LED_ShortSide);
	//HLED_Init(LED_PORT,LED_Stop);
	//HLED_Init(LED_PORT,LED_Rotate);
	MEXTI_GlobalInterruptEnable();
	//HMOTOR_init();
	
	//MTIMER0_Init(TIMER0_NORMAL_MODE,TIMER0_CS_PRESCALLER_8);
	
	HBTTN_SetButtonPressedCallBack(suddelly_Stop,EXTI0);
	//HBTTN_SetButtonPressedCallBack(Initial_Start,EXTI1);
	
//	MTIMER0_SetCallBack_REQUIREDTIME(MOVE_CAR);

    while (1) 
	
    {	
	
    }
	return 0;
}

