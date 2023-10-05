
#include "../HAL/button_driver/button_interface.h"
#include "../HAL/led_driver/led_interface.h"
#include "../HAL/led_driver/led_config.h"
#include "../HAL/motor_driver/motor_interface.h"
#include "../HAL/motor_driver/motor_config.h"
#include "../MCAL/timer/timer0/timer0_interface.h"
#include "../MCAL/timer/timer0/timer0_config.h"
#include "../MCAL/exti/exti_interface.h"
#include "../MCAL/dio/dio_interface.h"
#include "../MCAL/dio/dio_config.h"

#include  "app.h"


static EN_CarStatus_t 	enum_Satic_CarStatus=CAR_ForwardOnLongSide;
static u8 u8_Static_gaurd_EXTI=0;


/*
 * Description :
 * The functions stops the motor suddenly when the stop push button is pressed and turns the Stop LED ON
 */
void suddelly_Stop(void)
{
	if(u8_Static_gaurd_EXTI!=0)
	{
		HMOTOR_Allstop();
		HMOTOR_set_Allspeed(0);
		HLED_TurnOFF(LED_PORT,LED_LongSide);
		HLED_TurnOFF(LED_PORT,LED_ShortSide);
		HLED_TurnOn(LED_PORT,LED_Stop);
		HLED_TurnOFF(LED_PORT,LED_Rotate);
		
		enum_Satic_CarStatus=CAR_SuddenlyStop;
	}
}


/*
 * Description :
 * The functions moves the car on the long side for a period of time ,then it stop, rotates, stop again and then move on the short
 * side then stops,rotates right, stops again and then move on the long side, repeatedly.
 */
void MOVE_CAR(void)
{
	if (enum_Satic_CarStatus!=CAR_SuddenlyStop)
	{
		u8_Static_gaurd_EXTI=1;
		HLED_TurnOFF(LED_PORT,LED_LongSide);
		HLED_TurnOFF(LED_PORT,LED_ShortSide);
		HLED_TurnOFF(LED_PORT,LED_Stop);
		HLED_TurnOFF(LED_PORT,LED_Rotate);
		
		switch(enum_Satic_CarStatus)
		{
			case CAR_ForwardOnLongSide:
			HLED_TurnOn(LED_PORT,LED_LongSide);
			HMOTORS_MovingForward();
			HMOTOR_set_Allspeed(50);
			MTIMER0_DelayInterrupt_MS(3000);
			enum_Satic_CarStatus=CAR_STOP_AfterLongSide;
			break;
			case CAR_STOP_AfterLongSide:
			HLED_TurnOn(LED_PORT,LED_Stop);
			HMOTOR_Allstop();
			MTIMER0_DelayInterrupt_MS(500);
			enum_Satic_CarStatus=CAR_Rotate_RightShortSide;
			break;
			case CAR_Rotate_RightShortSide:
			HLED_TurnOn(LED_PORT,LED_Rotate);
			HMOTORS_RotateRight();
			HMOTOR_set_Allspeed(10);
			MTIMER0_DelayInterrupt_MS(3000);
			enum_Satic_CarStatus=CAR_STOP_BeforeShortSide;
			break;
			
			case CAR_STOP_BeforeShortSide:
			HLED_TurnOn(LED_PORT,LED_Stop);
			HMOTOR_Allstop();
			MTIMER0_DelayInterrupt_MS(500);
			enum_Satic_CarStatus=CAR_ForwardOnShortSide;
			break;
			
			case CAR_ForwardOnShortSide:
			HLED_TurnOn(LED_PORT,LED_ShortSide);
			HMOTORS_MovingForward();
			HMOTOR_set_Allspeed(30);
			MTIMER0_DelayInterrupt_MS(2000);
			enum_Satic_CarStatus=CAR_STOP_AfterShortSide;
			break;
			
			case CAR_STOP_AfterShortSide:
			HLED_TurnOn(LED_PORT,LED_Stop);
			HMOTOR_Allstop();
			MTIMER0_DelayInterrupt_MS(500);
			enum_Satic_CarStatus=CAR_Rotate_RightLongSide;
			break;
			
			case CAR_Rotate_RightLongSide:
			HLED_TurnOn(LED_PORT,LED_Rotate);
			HMOTORS_RotateRight();
			HMOTOR_set_Allspeed(10);
			MTIMER0_DelayInterrupt_MS(3000);
			enum_Satic_CarStatus=CAR_STOP_BeforeLongSide;
			break;
			
			case CAR_STOP_BeforeLongSide:
			HLED_TurnOn(LED_PORT,LED_Stop);
			HMOTOR_Allstop();
			MTIMER0_DelayInterrupt_MS(500);
			enum_Satic_CarStatus=CAR_ForwardOnLongSide;
			break;
			default:
			break;
		}
	}
	else
	{
		
	}
	
}


/*
 * Description :
 * The functions initializes the LEDs and The Pin directions for the buttons and enable timer
 */
void App_Init(void)
{
		HLED_Init(LED_PORT,LED_LongSide);
		HLED_Init(LED_PORT,LED_ShortSide);
		HLED_Init(LED_PORT,LED_Stop);
		HLED_Init(LED_PORT,LED_Rotate);
		MDIO_SetPinDirection(PORTD,PIN3,PIN_IN);
		MDIO_SetPullupResistor(PORTD,PIN3);
		
		MEXTI_GlobalInterruptEnable();
		HMOTOR_init();
		MTIMER0_Init(TIMER0_NORMAL_MODE,TIMER0_CS_PRESCALLER_8);
}


/*
 * Description :
 * The functions is responsible for starting the app.
 */
void App_Start(void)
{

	while(MDIO_u8GetPinValue(PORTD,PIN3)!=0);
	HBTTN_SetButtonPressedCallBack(suddelly_Stop,EXTI0);
	MTIMER0_DelayInterrupt_MS(1000);
	MTIMER0_SetCallBack_REQUIREDTIME(MOVE_CAR);
}

