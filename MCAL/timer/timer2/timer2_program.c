/**************************************************************************/
/*Author            : Amr Wahba                                           */
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

//#include "../GIE/GIE_int.h"
#include "timer2_config.h"
#include "timer2_interface.h"
#include "timer2_private.h"




void (*TIMER2_CALL_BACK_OverFlow)(void)=NULL_PTR;
void (*TIMER2_CALL_BACK_CompareMatch)(void)=NULL_PTR;




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
			return EN_timer2_Error_t =TIMER2_NOT_OK;
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
		return EN_timer2_Error_t =TIMER2_NOT_OK;

		break;
	}
}




/******************************************************************************/
/*                      MTIMER2_CompareOutputMode                             */
/*----------------------------------------------------------------------------*/
/* 1- Function Description -> Configures the compare output mode for Timer2    */
/*                            based on the specified mode and COM value.      */
/* 2- Function Input       ->                                                 */
/*                            @param Copy_u8Mode                              */
/*                            @param Copy_u8COM                               */
/* 3- Function Return      -> @return EN_timer2_Error_t                       */
/*       [ TIMER2_OK ,  TIMER2_NOT_OK ]                                       */
/******************************************************************************/

EN_timer2_Error_t MTIMER2_CompareOutputMode(u8 Copy_u8Mode,u8 Copy_u8COM)
{
	 EN_timerError_t errorStatus = TIMER0_OK;

	switch(Copy_u8Mode)
	{
		case TIMER2_CTC_MODE:
		//-----------------------" Compare Output Mode with NO PWM " --------------------------
		switch (Copy_u8COM)
		{
			case	TIMER2_COM_NOPWM_OC2_PIN_DISCONNETED:
			CLEAR_BIT(MTIMER2_TCCR2_REG,TCCR2_COM20_BIT);
			CLEAR_BIT(MTIMER2_TCCR2_REG,TCCR2_COM21_BIT);
			break;

			case	TIMER2_COM_NOPWM_OC2_PIN_TOGGLE:
			SET_BIT(MTIMER2_TCCR2_REG,TCCR2_COM20_BIT);
			CLEAR_BIT(MTIMER2_TCCR2_REG,TCCR2_COM21_BIT);
			break;

			case	TIMER2_COM_NOPWM_OC2_PIN_CLEAR:
			CLEAR_BIT(MTIMER2_TCCR2_REG,TCCR2_COM20_BIT);
			SET_BIT(MTIMER2_TCCR2_REG,TCCR2_COM21_BIT);
			break;

			case TIMER2_COM_NOPWM_OC2_PIN_SET:
			SET_BIT(MTIMER2_TCCR2_REG,TCCR2_COM20_BIT);
			SET_BIT(MTIMER2_TCCR2_REG,TCCR2_COM21_BIT);
			break;

			default:
				return EN_timer2_Error_t =TIMER2_NOT_OK;

			break;
		}
		break;


		//-----------------------" Compare Output Mode with PHASE CORRECT PWM " --------------------------
		case TIMER2_PWM_PHASECORRECT_MODE:
		switch (Copy_u8COM)
		{
			case TIMER2_COM_PHASECORRECTPWM_OC2_PIN_DISCONNETED:
			CLEAR_BIT(MTIMER2_TCCR2_REG,TCCR2_COM20_BIT);
			CLEAR_BIT(MTIMER2_TCCR2_REG,TCCR2_COM21_BIT);
			break;

			case TIMER2_COM_PHASECORRECTPWM_OC2_PIN_CLEAR_COUNTUP:
			CLEAR_BIT(MTIMER2_TCCR2_REG,TCCR2_COM20_BIT);
			SET_BIT(MTIMER2_TCCR2_REG,TCCR2_COM21_BIT);
			break;

			case TIMER2_COM_PHASECORRECTPWM_OC2_PIN_SET_COUNTUP:
			SET_BIT(MTIMER2_TCCR2_REG,TCCR2_COM20_BIT);
			SET_BIT(MTIMER2_TCCR2_REG,TCCR2_COM21_BIT);
			break;

			default:
				return EN_timer2_Error_t =TIMER2_NOT_OK;

			break;
		}
		break;

		//-----------------------" Compare Output Mode with FAST PWM " --------------------------
		case TIMER2_FAST_PWM_MODE:
		switch (Copy_u8COM)
		{
			case TIMER2_COM_FASTPWM_OC2_PIN_DISCONNETED:
			CLEAR_BIT(MTIMER2_TCCR2_REG,TCCR2_COM20_BIT);
			CLEAR_BIT(MTIMER2_TCCR2_REG,TCCR2_COM21_BIT);
			break;

			case TIMER2_COM_FASTPWM_OC2_PIN_CLEAR:
			CLEAR_BIT(MTIMER2_TCCR2_REG,TCCR2_COM20_BIT);
			SET_BIT(MTIMER2_TCCR2_REG,TCCR2_COM21_BIT);
			break;

			case TIMER2_COM_FASTPWM_OC2_PIN_SET:
			SET_BIT(MTIMER2_TCCR2_REG,TCCR2_COM20_BIT);
			SET_BIT(MTIMER2_TCCR2_REG,TCCR2_COM21_BIT);
			break;

			default:
			return EN_timer2_Error_t =TIMER2_NOT_OK;
			
			break;
		}
		break;

		default:
		return EN_timer2_Error_t =TIMER2_NOT_OK;
	
		break;
	}
}


/******************************************************************************/
/*                        MTIMER2_u8CheckOverFlow                             */
/*----------------------------------------------------------------------------*/
/* 1- Function Description -> Checks for Timer2 overflow and returns a flag.   */
/* 2- Function Input       -> None                                              */
/* 3- Function Return      -> @return u8                                       */
/*       [ 0: No overflow, 1: Overflow occurred ]                               */
/******************************************************************************/

u8  MTIMER2_u8CheckOverFlow(void)
{
	u8 Local_u8OverFlowFlag=0;
	while(GET_BIT(MTIMER_TIFR_REG, TIMER2_TOV2_BIT)!=1);
	Local_u8OverFlowFlag=1;

	// to clear Timer/Counter0 Overflow Flag
	SET_BIT(MTIMER_TIFR_REG, TIMER2_TOV2_BIT);
	return Local_u8OverFlowFlag;
}


/******************************************************************************/
/*                 MTIMER2_u8CheckCompareMatchMode                             */
/*----------------------------------------------------------------------------*/
/* 1- Function Description -> Checks for Timer2 compare match and returns a   */
/*                            flag.                                            */
/* 2- Function Input       -> None                                              */
/* 3- Function Return      -> @return u8                                       */
/*       [ 0: No compare match, 1: Compare match occurred ]                     */
/******************************************************************************/

u8    MTIMER2_u8CheckCompareMatchMode(void)
{
	u8 Local_u8CompareMatchFlag=0;
	while(GET_BIT(MTIMER_TIFR_REG, TIMER2_OCF2_BIT)!=1);
	Local_u8CompareMatchFlag=1;

	// to clear Timer/Counter0 CompareMatch Flag
	SET_BIT(MTIMER_TIFR_REG, TIMER2_OCF2_BIT);
	return Local_u8CompareMatchFlag;
}



/******************************************************************************/
/*                          MTIMER2_SetPreLoad                                */
/*----------------------------------------------------------------------------*/
/* 1- Function Description -> Sets the preload value for Timer2.              */
/* 2- Function Input       ->                                                 */
/*                            @param Copy_u16PreLoad                         */
/* 3- Function Return      -> @return EN_timer2_Error_t                       */
/*       [ TIMER2_OK ]                                                         */
/******************************************************************************/


EN_timer2_Error_t MTIMER2_SetPreLoad(u16 Copy_u16PreLoad)
{
	
	MTIMER2_OCR2_REG=Copy_u16PreLoad;
	return TIMER2_OK ;
}

/******************************************************************************/
/*                    MTIMER2_SetCompareMatchValue                         */
/*----------------------------------------------------------------------------*/
/* 1- Function Description -> Sets the compare match value for Timer2.         */
/* 2- Function Input       ->                                                 */
/*                            @param Copy_u8CompareMatchValue                 */
/* 3- Function Return      -> @return EN_timer2_Error_t                       */
/*       [ TIMER2_OK ]                                                         */
/******************************************************************************/

EN_timer2_Error_t MTIMER2_SetCompareMatchValue(u8 Copy_u8CompareMatchValue)
{
	MTIMER2_OCR2_REG=Copy_u8CompareMatchValue;
	
		return TIMER2_OK ;

}



/******************************************************************************/
/*                          MTIMER2_PWMDutyCycle                              */
/*----------------------------------------------------------------------------*/
/* 1- Function Description -> Sets the PWM duty cycle for Timer2.              */
/*                            Calculates the compare match value based on     */
/*                            the given duty cycle percentage.                 */
/* 2- Function Input       ->                                                 */
/*                            @param Copy_u8DutyCycle                         */
/* 3- Function Return      -> @return EN_timer2_Error_t                       */
/*       [ TIMER2_OK ]                                                         */
/******************************************************************************/

EN_timer2_Error_t MTIMER2_PWMDutyCycle(u8 Copy_u8DutyCycle)
{
	if (Copy_u8DutyCycle <= 100 && Copy_u8DutyCycle > 0)
	{
		u8 local_CompareMatchValue = (Copy_u8DutyCycle * TIMER2_OverFlowValue) / TIMER2_MaxDutyCycle;

		MTIMER2_OCR2_REG = local_CompareMatchValue;
	}
	return TIMER2_OK;
}


/******************************************************************************/
/*                MTIMER2_SetCallBack_OverFlow                                */
/*----------------------------------------------------------------------------*/
/* 1- Function Description -> Sets the callback function for Timer2 overflow   */
/*                            interrupt.                                      */
/* 2- Function Input       ->                                                 */
/*                            @param TIMER2_OF_ISR                            */
/*                              Pointer to the overflow interrupt service      */
/*                              routine.                                      */
/* 3- Function Return      -> @return EN_timer2_Error_t                       */
/*       [ TIMER2_OK ]                                                         */
/******************************************************************************/

EN_timer2_Error_t MTIMER2_SetCallBack_OverFlow(void (*TIMER2_OF_ISR)(void))
{
	TIMER2_CALL_BACK_OverFlow=TIMER2_OF_ISR;
	SET_BIT(MTIMER_TIMSK_REG,TIMSK_TOIE2_BIT);
	
		return TIMER2_OK ;

}


/******************************************************************************/
/*             MTIMER2_SetCallBack_CompareMatchValue                           */
/*----------------------------------------------------------------------------*/
/* 1- Function Description -> Sets the callback function for Timer2 compare    */
/*                            match interrupt.                                 */
/* 2- Function Input       ->                                                 */
/*                            @param TIMER2_CMV_ISR                           */
/*                              Pointer to the compare match interrupt        */
/*                              service routine.                              */
/* 3- Function Return      -> @return EN_timer2_Error_t                       */
/*       [ TIMER2_OK ]                                                         */
/******************************************************************************/


EN_timer2_Error_t MTIMER2_SetCallBack_CompareMatchValue(void (*TIMER2_CMV_ISR)(void))
{
	TIMER2_CALL_BACK_CompareMatch=TIMER2_CMV_ISR;
	SET_BIT(MTIMER_TIMSK_REG,TIMSK_OCIE2_BIT);
		return TIMER2_OK ;

}



/*******************************************************************************
 *                   Callback Function Setup                                   *
 *******************************************************************************/


//TIMER2 COMP Timer/Counter2 Compare Match  Interrupt Vector
void __vector_4(void) __attribute__((signal));
void __vector_4(void)
{
	if (TIMER2_CALL_BACK_CompareMatch!=NULL_PTR) {
		TIMER2_CALL_BACK_CompareMatch();
	}
}
// TIMER2 OVF Timer/Counter0 Overflow  Interrupt Vector
void __vector_5(void) __attribute__((signal));
void __vector_5(void)
{
	if (TIMER2_CALL_BACK_OverFlow!=NULL_PTR) {
		TIMER2_CALL_BACK_OverFlow();
	}
}
