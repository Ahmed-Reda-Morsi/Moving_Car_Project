/*******************************************************************************
 *                              REQUIRED INCLUDES                              *
 *******************************************************************************/
#include "../../../LIB/STD_TYPES.h"
#include "../../../LIB/BIT_MATH.h"
#include "../../dio/dio_interface.h"

#include "timer2_config.h"
#include "timer2_interface.h"
#include "timer2_private.h"


/*******************************************************************************
 *                              REQUIRED Variables                             *
 *******************************************************************************/
static u8 u8_GLOBAL_TIMER2_PRELOAD_ONTIME=0;
static u8 u8_GLOBAL_TIMER2_PRELOAD_OFFTIME=0;


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description:
 * This function is used to initialize Timer2 with the specified mode and prescaler.
 * It takes two parameters: u8_arg_Mode: The desired mode of Timer2. This can be either
 * normal mode or PWM mode. u8_arg_PreScaler: The desired prescaler value to set the timer's 
 * clock frequency.
 */

EN_timer2_Error_t MTIMER2_Init(u8 u8_arg_Mode,u8 u8_arg_PreScaler)
{
		 EN_timer2_Error_t enum_Local_errorStatus = TIMER2_OK;


	switch(u8_arg_Mode)
	{
		case TIMER2_NORMAL_MODE:
		CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_WGM20_BIT);
		CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_WGM21_BIT);
		break;

		case TIMER2_CTC_MODE:
		// set OC2 as OUTPUT for generate  wave.
		SET_BIT(OC2_DDR,OC2_PIN);
		CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_WGM20_BIT);
		SET_BIT(MTIMER2_TCCR2_REG, TCCR2_WGM21_BIT);
		break;

		case TIMER2_PWM_PHASECORRECT_MODE:
		// set OC2 as OUTPUT for generate  wave.
		SET_BIT(OC2_DDR,OC2_PIN);
		SET_BIT(MTIMER2_TCCR2_REG, TCCR2_WGM20_BIT);
		CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_WGM21_BIT);
		break;

		case TIMER2_FAST_PWM_MODE:
		// set OC2 as OUTPUT for generate  wave.
		SET_BIT(OC2_DDR,OC2_PIN);
		SET_BIT(MTIMER2_TCCR2_REG, TCCR2_WGM20_BIT);
		SET_BIT(MTIMER2_TCCR2_REG, TCCR2_WGM21_BIT);
		break;

		default:
			return enum_Local_errorStatus =TIMER2_NOT_OK;
		break;

	}

	//________________________________| Clock Select MODE|_________________________

	switch(u8_arg_PreScaler)
	{
		case TIMER2_CS_STOP:
		CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_CS20_BIT);
		CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_CS21_BIT);
		CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_CS22_BIT);
		break;

		case TIMER2_CS_NOPRESCALLER:
		SET_BIT(MTIMER2_TCCR2_REG, TCCR2_CS20_BIT);
		CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_CS21_BIT);
		CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_CS22_BIT);
		break;

		case TIMER2_CS_PRESCALLER_8:
		CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_CS20_BIT);
		SET_BIT(MTIMER2_TCCR2_REG, TCCR2_CS21_BIT);
		CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_CS22_BIT);
		break;

		case TIMER2_CS_PRESCALLER_32:
		SET_BIT(MTIMER2_TCCR2_REG, TCCR2_CS20_BIT);
		SET_BIT(MTIMER2_TCCR2_REG, TCCR2_CS21_BIT);
		CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_CS22_BIT);
		break;

		case TIMER2_CS_PRESCALLER_64:
		CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_CS20_BIT);
		CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_CS21_BIT);
		SET_BIT(MTIMER2_TCCR2_REG, TCCR2_CS22_BIT);
			break;

		case TIMER2_CS_PRESCALLER_128:
		SET_BIT(MTIMER2_TCCR2_REG, TCCR2_CS20_BIT);
		CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_CS21_BIT);
		SET_BIT(MTIMER2_TCCR2_REG, TCCR2_CS22_BIT);
		break;

		case TIMER2_CS_PRESCALLER_256:
		CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_CS20_BIT);
		SET_BIT(MTIMER2_TCCR2_REG, TCCR2_CS21_BIT);
		SET_BIT(MTIMER2_TCCR2_REG, TCCR2_CS22_BIT);
		break;

		case TIMER2_CS_PRESCALLER_1024:
		SET_BIT(MTIMER2_TCCR2_REG, TCCR2_CS20_BIT);
		SET_BIT(MTIMER2_TCCR2_REG, TCCR2_CS21_BIT);
		SET_BIT(MTIMER2_TCCR2_REG, TCCR2_CS22_BIT);
		break;

		default:
		return  enum_Local_errorStatus =TIMER2_NOT_OK;

		break;
	}
	
	return enum_Local_errorStatus;
}

/*
 * Description:
 * This function is used to initialize Timer2 in PWM mode. It configures the necessary settings
 * to enable PWM generation using Timer2. The function returns an EN_timer2_Error_t enumeration 
 * indicating whether the PWM initialization was successful or if there was an error.
 */
EN_timer2_Error_t MTIMER2_PWM_init(void)
{
	EN_timer2_Error_t enum_Local_errorStatus=TIMER2_OK;

	enum_Local_errorStatus= MDIO_SetPinDirection(PWM_NORMAL_MODE_PORT,PWM_NORMAL_MODE_PIN,PIN_OUT);
	enum_Local_errorStatus= MDIO_SetPinValue(PWM_NORMAL_MODE_PORT,PWM_NORMAL_MODE_PIN,PIN_LOW);
	if (enum_Local_errorStatus!=TIMER2_OK)
	{
		enum_Local_errorStatus=TIMER2_NOT_OK;
	}
     return enum_Local_errorStatus;

}


/*
 * Description:
 * This function is used to set the duty cycle for the PWM signal when Timer2 is operating in normal mode.
 * It takes one parameter: u8_arg_DutyCycle: The desired duty cycle for the PWM signal represented as a 
 * value from 0 to 100.
 */

EN_timer2_Error_t MTIMER2_SetPWMNormalMode_DutyCycle(u8 u8_arg_DutyCycle)
{
	EN_timer2_Error_t enum_Local_errorStatus=TIMER2_OK;
	if (u8_arg_DutyCycle<100 && u8_arg_DutyCycle>0)
	{
		u8_GLOBAL_TIMER2_PRELOAD_ONTIME=(u8)(TIMER2_OverFlowValue-((u8_arg_DutyCycle*PWM_NORMAL_MODE_PERIOD)/100));
		u8_GLOBAL_TIMER2_PRELOAD_OFFTIME=(u8)(TIMER2_OverFlowValue-(((100-u8_arg_DutyCycle)*PWM_NORMAL_MODE_PERIOD)/100));
		MTIMER2_TCNT2_REG=u8_GLOBAL_TIMER2_PRELOAD_ONTIME;
		//Enable overflow interrupt for timer2
		SET_BIT(MTIMER_TIMSK_REG,TIMSK_TOIE2_BIT);
	}
	else if (u8_arg_DutyCycle==100)
	{
		MDIO_SetPinValue(PWM_NORMAL_MODE_PORT,PWM_NORMAL_MODE_PIN,PIN_HIGH);
	}
	else if (u8_arg_DutyCycle==0)
	{
		MDIO_SetPinValue(PWM_NORMAL_MODE_PORT,PWM_NORMAL_MODE_PIN,PIN_LOW);
		CLEAR_BIT(MTIMER_TIMSK_REG,TIMSK_TOIE2_BIT);

	}
	else
	{
		enum_Local_errorStatus=TIMER2_NOT_OK;
	}

	return enum_Local_errorStatus;
}


/*******************************************************************************
 *                     Overflow  Interrupt Vector Definition                   *
 *******************************************************************************/
// TIMER2 OVF Timer/Counter2 Overflow  Interrupt Vector
void __vector_5(void) __attribute__((signal));
void __vector_5(void)
{
	
	static u8 u8_Local_Counter=0;
	if (u8_Local_Counter==0)
	{  
		//SET ONTIME PERIOD
		MDIO_TogglePinValue(PWM_NORMAL_MODE_PORT,PWM_NORMAL_MODE_PIN);
		MTIMER2_TCNT2_REG=u8_GLOBAL_TIMER2_PRELOAD_ONTIME;
	   u8_Local_Counter++;
	}
	else if (u8_Local_Counter==1)
	{
		//SET OFFTIME PERIOD
	    MDIO_TogglePinValue(PWM_NORMAL_MODE_PORT,PWM_NORMAL_MODE_PIN);
		MTIMER2_TCNT2_REG=u8_GLOBAL_TIMER2_PRELOAD_OFFTIME;
		u8_Local_Counter=0;
	}
	
}
