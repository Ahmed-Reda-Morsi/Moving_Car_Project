/**************************************************************************/
/*Author            : Ahmed Reda                                          */
/*Version           : V1.0.0                                              */
/*Date              : 2 10 2023                                           */
/*Description       : timer2_program.c                                    */
/*Features          :                                                     */
/*        - MTIMER2_voidInit()                                            */
/*        - MTIMER2_CompareOutputMode()                                   */
/*        - MTIMER2_u8CheckOverFlow()                                     */
/*        - MTIMER2_u8CheckCompareMatchMode()                             */
/*        - MTIMER2_SetPreLoad()                                          */
/*        - MTIMER2_voidSetCompareMatchValue()                            */
/*        - MTIMER2_PWMDutyCycle()                                        */
/*        - MTIMER2_SetCallBack_OverFlow()                                 */
/*        - MTIMER2_SetCallBack_CompareMatchValue()                        */
/**************************************************************************/


/*******************************************************************************
 *                               standard LIBS                                  *
 *******************************************************************************/
#include "../../../LIB/STD_TYPES.h"
#include "../../../LIB/BIT_MATH.h"
#include <math.h>

#include "timer2_config.h"
#include "timer2_interface.h"
#include "timer2_private.h"

#include "../../dio/dio_interface.h"
void (*TIMER2_CALL_BACK_OverFlow)(void)=NULL_PTR;
void (*TIMER2_CALL_BACK_REQUIREDTIME)(void)=NULL_PTR;

static u8 GLOBAL_TIMER2_PRELOAD_ONTIME=0;
static u8 GLOBAL_TIMER2_PRELOAD_OFFTIME=0;


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


/******************************************************************************/
/*                             MTIMER2_voidInit                              */
/*----------------------------------------------------------------------------*/
/* 1- Function Description -> Initializes Timer2  for specified    */
/*                            mode and prescaler.                             */
/* 2- Function Input       ->                                                 */
/*                            @param Copy_u8Mode                              */
/*                            @param Copy_u8PreScaler                          */
/* 3- Function Return      -> @return EN_timer2_Error_t                       */
/*       [ TIMER2_OK ,  TIMER2_NOT_OK ]                                       */
/******************************************************************************/

EN_timer2_Error_t MTIMER2_Init(u8 Copy_u8Mode,u8 Copy_u8PreScaler)
{
		 EN_timer2_Error_t errorStatus = TIMER2_OK;


	switch(Copy_u8Mode)
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
			return errorStatus =TIMER2_NOT_OK;
		break;

	}

	//________________________________| Clock Select MODE|_________________________

	switch(Copy_u8PreScaler)
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
		return  errorStatus =TIMER2_NOT_OK;

		break;
	}
	
	return errorStatus;
}

EN_timer2_Error_t MTIMER2_PWM_init(void)
{
	EN_timer2_Error_t errorStatus=TIMER2_OK;

	errorStatus= MDIO_SetPinDirection(PWM_NORMAL_MODE_PORT,PWM_NORMAL_MODE_PIN,PIN_OUT);
	errorStatus= MDIO_SetPinValue(PWM_NORMAL_MODE_PORT,PWM_NORMAL_MODE_PIN,PIN_LOW);
	if (errorStatus!=TIMER2_OK)
	{
		errorStatus=TIMER2_NOT_OK;
	}
     return errorStatus;

}


EN_timer2_Error_t MTIMER2_SetPWMNormalMode_DutyCycle(u8 u8_Local_DutyCycle)
{
	EN_timer2_Error_t errorStatus=TIMER2_OK;
	if (u8_Local_DutyCycle<100 && u8_Local_DutyCycle>0)
	{
		//GLOBAL_TIMER2_PRELOAD_ONTIME=(u8)((pow(2,TIMER2_RESOLUTION)-1)-((u8_Local_DutyCycle*PWM_NORMAL_MODE_PERIOD)/100));
	    //GLOBAL_TIMER2_PRELOAD_OFFTIME=(u8)((pow(2,TIMER2_RESOLUTION)-1)-(((100-u8_Local_DutyCycle)*PWM_NORMAL_MODE_PERIOD)/100));
		GLOBAL_TIMER2_PRELOAD_ONTIME=(u8)(TIMER2_OverFlowValue-((u8_Local_DutyCycle*PWM_NORMAL_MODE_PERIOD)/100));
		GLOBAL_TIMER2_PRELOAD_OFFTIME=(u8)(TIMER2_OverFlowValue-(((100-u8_Local_DutyCycle)*PWM_NORMAL_MODE_PERIOD)/100));
		MTIMER2_TCNT2_REG=GLOBAL_TIMER2_PRELOAD_ONTIME;
		//Enable overflow interrupt for timer2
		SET_BIT(MTIMER_TIMSK_REG,TIMSK_TOIE2_BIT);
	}
	else if (u8_Local_DutyCycle==100)
	{
		MDIO_SetPinValue(PWM_NORMAL_MODE_PORT,PWM_NORMAL_MODE_PIN,PIN_HIGH);
	}
	else if (u8_Local_DutyCycle==0)
	{
		MDIO_SetPinValue(PWM_NORMAL_MODE_PORT,PWM_NORMAL_MODE_PIN,PIN_LOW);
		CLEAR_BIT(MTIMER_TIMSK_REG,TIMSK_TOIE2_BIT);

	}
	else
	{
		errorStatus=TIMER2_NOT_OK;
	}

	return errorStatus;
}

EN_timer2_Error_t MTIMER2_SetCallBack_OverFlow(void(*TIMER2_OF_ISR)(void))
{
	
	TIMER2_CALL_BACK_OverFlow=TIMER2_OF_ISR;
	return TIMER2_OK;
}



/*******************************************************************************
 *                   Callback Function Setup                                   *
 *******************************************************************************/




// TIMER2 OVF Timer/Counter2 Overflow  Interrupt Vector
void __vector_5(void) __attribute__((signal));
void __vector_5(void)
{
	
	static u8 u8_Local_Counter=0;
	if (u8_Local_Counter==0)
	{
		MDIO_TogglePinValue(PWM_NORMAL_MODE_PORT,PWM_NORMAL_MODE_PIN);
		MTIMER2_TCNT2_REG=GLOBAL_TIMER2_PRELOAD_ONTIME;
	   u8_Local_Counter++;
	}
	else if (u8_Local_Counter==1)
	{
	    MDIO_TogglePinValue(PWM_NORMAL_MODE_PORT,PWM_NORMAL_MODE_PIN);
		MTIMER2_TCNT2_REG=GLOBAL_TIMER2_PRELOAD_OFFTIME;
		u8_Local_Counter=0;
	}
	
	
	
	if (TIMER2_CALL_BACK_OverFlow!=NULL_PTR) {
		TIMER2_CALL_BACK_OverFlow();
	}
}
