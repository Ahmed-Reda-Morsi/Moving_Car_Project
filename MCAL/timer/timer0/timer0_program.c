#include "../../../LIB/STD_TYPES.h"
#include "../../../LIB/BIT_MATH.h"
#include <math.h>

//#include "../GIE/GIE_int.h"
#include "timer0_config.h"
#include "timer0_interface.h"
#include "timer0_private.h"

void (*TIMER0_CALL_BACK_OverFlow)(void)=NULL_PTR;
void (*TIMER0_CALL_BACK_REQUIREDTIME)(void)=NULL_PTR;
void (*TIMER0_CALL_BACK_CompareMatch)(void)=NULL_PTR;

/*******************************************************************************
 *                               Static-Variables                              *
 *******************************************************************************/
static u16 GLOBAL_TIMER0_PRESCALER=0;

static u32 GLOBAL_TIMER0_NO_OVERFLOW=0;
static u32 GLOBAL_TIMER0_PRELOAD=0;

static u8 GLOBAL_u8TickTime=0;
static u16 GLOBAL_u16TimeOverFlow=0;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description:
 * This function initializes Timer0 with the specified mode and prescaler,
 * and returns error status.
 * open cfg  header to configure TIMER0
 */
EN_timerError_t MTIMER0_Init(u8 Copy_u8Mode,u8 Copy_u8PreScaler)
{
	 EN_timerError_t errorStatus = TIMER0_OK;
	 switch(Copy_u8Mode)
	 {
		case TIMER0_NORMAL_MODE:
			CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_WGM00_BIT);
			CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_WGM01_BIT);
			break;

		case TIMER0_CTC_MODE:
			// set OC0 as OUTPUT for generate  wave.
			SET_BIT(OC0_DDR,OC0_PIN);
			CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_WGM00_BIT);
			SET_BIT(MTIMER0_TCCR0_REG, TCCR0_WGM01_BIT);
			break;

		case TIMER0_PWM_PHASECORRECT_MODE:
			// set OC0 as OUTPUT for generate  wave.
			SET_BIT(OC0_DDR,OC0_PIN);
			SET_BIT(MTIMER0_TCCR0_REG, TCCR0_WGM00_BIT);
			CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_WGM01_BIT);
			break;

		case TIMER0_FAST_PWM_MODE:
			// set OC0 as OUTPUT for generate  wave.
			SET_BIT(OC0_DDR,OC0_PIN);
			SET_BIT(MTIMER0_TCCR0_REG, TCCR0_WGM00_BIT);
			SET_BIT(MTIMER0_TCCR0_REG, TCCR0_WGM01_BIT);
			break;

		default:
			errorStatus = TIMER0_NOT_OK;

	 }

	 //________________________________| Clock Select MODE|_________________________

	 switch(Copy_u8PreScaler)
	 {
		 case TIMER0_CS_STOP:
			 CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_CS00_BIT);
			 CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_CS01_BIT);
			 CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_CS02_BIT);
				break;

		 case TIMER0_CS_NOPRESCALLER:
			 SET_BIT(MTIMER0_TCCR0_REG, TCCR0_CS00_BIT);
			 CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_CS01_BIT);
			 CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_CS02_BIT);
				break;

		 case TIMER0_CS_PRESCALLER_8:
			 CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_CS00_BIT);
			 SET_BIT(MTIMER0_TCCR0_REG, TCCR0_CS01_BIT);
			 CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_CS02_BIT);
			 GLOBAL_TIMER0_PRESCALER=8;
				break;

		 case TIMER0_CS_PRESCALLER_64:
			 SET_BIT(MTIMER0_TCCR0_REG, TCCR0_CS00_BIT);
			 SET_BIT(MTIMER0_TCCR0_REG, TCCR0_CS01_BIT);
			 CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_CS02_BIT);
			 GLOBAL_TIMER0_PRESCALER=64;
				break;

		 case TIMER0_CS_PRESCALLER_256:
			 CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_CS00_BIT);
			 CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_CS01_BIT);
			 SET_BIT(MTIMER0_TCCR0_REG, TCCR0_CS02_BIT);
			 GLOBAL_TIMER0_PRESCALER=256;
				break;

		 case TIMER0_CS_PRESCALLER_1024:
			 SET_BIT(MTIMER0_TCCR0_REG, TCCR0_CS00_BIT);
			 SET_BIT(MTIMER0_TCCR0_REG, TCCR0_CS01_BIT);
			 CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_CS02_BIT);
			 GLOBAL_TIMER0_PRESCALER=1024;
				break;

		 case TIMER0_CS_EXTERNAL_T0_PIN_FALLINGEDGE:
			 CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_CS00_BIT);
			 SET_BIT(MTIMER0_TCCR0_REG, TCCR0_CS01_BIT);
			 SET_BIT(MTIMER0_TCCR0_REG, TCCR0_CS02_BIT);
				break;

		 case TIMER0_CS_EXTERNAL_T0_PIN_RISINGEDGE:
			 SET_BIT(MTIMER0_TCCR0_REG, TCCR0_CS00_BIT);
			 SET_BIT(MTIMER0_TCCR0_REG, TCCR0_CS01_BIT);
			 SET_BIT(MTIMER0_TCCR0_REG, TCCR0_CS02_BIT);
				break;

		 default:
			 errorStatus = TIMER0_NOT_OK;
 		 }

 		 /*calucate in init func. becuase they are depend of Prescaler*/
 		 //calucate Tick time in microsecond unit.
		 GLOBAL_u8TickTime=(GLOBAL_TIMER0_PRESCALER*1000000UL)/CPU_F;
		//overflow time for Timer0 in microsecond unit.
		  GLOBAL_u16TimeOverFlow=GLOBAL_u8TickTime*(pow(2,TIMER0_RESOLUTION));
		  return errorStatus;

}


/*
 * Description:
 * This function sets the preload and returns error status.
 */
EN_timerError_t MTIMER0_SetPreLoad(u16 Copy_u16PreLoad)
{
	MTIMER0_OCR0_REG=Copy_u16PreLoad;
	return TIMER0_OK;
}


/*
 * Description:
 * This function is used to delay the program execution for a specified amount of time using Timer0 interrupts.
 * The delay time is provided in milliseconds and converted to microseconds.
 * The function calculates the number of Timer0 overflow cycles required to achieve the desired delay time.
 * If the delay time exceeds the maximum overflow time of Timer0, the function splits the delay into multiple overflow cycles.
 * The remainder time is stored in the preload value to be loaded into Timer0 registers after the required number of overflows.
 * The function enables the overflow interrupt for Timer0 to start the delay operation.
 */
EN_timerError_t MTIMER0_DelayInterrupt_MS(u32 Copy_u32Delay)
{
	// user delay in microsecond unit.
	Copy_u32Delay=Copy_u32Delay*1000UL;

	if (Copy_u32Delay>=GLOBAL_u16TimeOverFlow) {

		//number of overflow needed to required time.
		GLOBAL_TIMER0_NO_OVERFLOW=Copy_u32Delay/GLOBAL_u16TimeOverFlow;

		//remainder time needed to after number of overflow required time. in  microsecond unit.
		GLOBAL_TIMER0_PRELOAD=(Copy_u32Delay%GLOBAL_u16TimeOverFlow)*(pow(2,TIMER0_RESOLUTION));

	} else if(Copy_u32Delay<GLOBAL_u16TimeOverFlow)
	{
		//remainder required time. in  microsecond unit.
		GLOBAL_TIMER0_PRELOAD=(Copy_u32Delay%GLOBAL_u16TimeOverFlow)*(pow(2,TIMER0_RESOLUTION));

	}
	//Enable overflow interrupt for timer0
	SET_BIT(MTIMER_TIMSK_REG,TIMSK_TOIE0_BIT);
	return TIMER0_OK;
}


/*
 * Description:
 * This function is used to delay the program execution for a specified amount of time using Timer0 without interrupts.
 * The delay time is provided in milliseconds and converted to microseconds.
 * The function calculates the number of Timer0 overflow cycles required to achieve the desired delay time.
 * If the delay time exceeds the maximum overflow time of Timer0, the function performs multiple overflow cycles using a loop.
 * The remainder time is stored in the preload value to be loaded into Timer0 registers after the required number of overflows.
 * The function waits for the overflow flag to be set and clears it before returning.
 */
EN_timerError_t MTIMER0_Delay_MS(u32 Copy_u32Delay)
{

	Copy_u32Delay=Copy_u32Delay*1000UL;  // for microsecond unit.

	//timer counter
	u32 Local_counter=0,Local_NO_OVERFLOW=0,Local_PRELOAD=0;

	if (Copy_u32Delay>=GLOBAL_u16TimeOverFlow) {

		//number of overflow needed to required time.
		Local_NO_OVERFLOW=Copy_u32Delay/GLOBAL_u16TimeOverFlow;

		while(Local_counter!=Local_NO_OVERFLOW)
		{
			 // Clear the overflow flag
			SET_BIT(MTIMER_TIFR_REG,TIMER0_TOV0_BIT);
			while(GET_BIT(MTIMER_TIFR_REG,TIMER0_TOV0_BIT)==0);

			Local_counter++;
		}
		//remainder time needed to after number of overflow required time. in  microsecond unit.
		Local_PRELOAD=(Copy_u32Delay%GLOBAL_u16TimeOverFlow)*(pow(2,TIMER0_RESOLUTION));

		MTIMER0_TCNT0_REG=Local_PRELOAD;

		// Clear the overflow flag
		SET_BIT(MTIMER_TIFR_REG,TIMER0_TOV0_BIT);
		while(GET_BIT(MTIMER_TIFR_REG,TIMER0_TOV0_BIT)==0);

	} else if(Copy_u32Delay<GLOBAL_u16TimeOverFlow)
	{
		//remainder required time. in  microsecond unit.
		Local_PRELOAD=(Copy_u32Delay%GLOBAL_u16TimeOverFlow)*(pow(2,TIMER0_RESOLUTION));
		MTIMER0_TCNT0_REG=Local_PRELOAD;
		// Clear the overflow flag
		SET_BIT(MTIMER_TIFR_REG,TIMER0_TOV0_BIT);
		while(GET_BIT(MTIMER_TIFR_REG,TIMER0_TOV0_BIT)==0);
	}

	return TIMER0_OK;
}



/*
 * Description:
 * This function is used to configure the compare output mode of Timer0 based on the selected mode and compare output settings.
 * The function takes two parameters: Copy_u8Mode for the Timer0 mode and Copy_u8COM for the compare output settings.
 * The function uses nested switch statements to handle different modes and compare output options.
 * It sets or clears the necessary bits in the Timer0 Control Register (TCCR0) based on the selected mode and compare output settings.
 * If an invalid mode or compare output option is provided, the function returns a NOT_OK error status.
 */
 EN_timerError_t MTIMER0_CompareOutputMode(u8 Copy_u8Mode,u8 Copy_u8COM)
 {
	EN_timerError_t errorStatus = TIMER0_OK;
	 switch(Copy_u8Mode)
	 {
		case TIMER0_CTC_MODE:
			//-----------------------" Compare Output Mode with NO PWM " --------------------------
			switch (Copy_u8COM)
					{
					case	TIMER0_COM_NOPWM_OC0_PIN_DISCONNETED:
							CLEAR_BIT(MTIMER0_TCCR0_REG,TCCR0_COM00_BIT);
							CLEAR_BIT(MTIMER0_TCCR0_REG,TCCR0_COM01_BIT);
							break;

					case	TIMER0_COM_NOPWM_OC0_PIN_TOGGLE:
							SET_BIT(MTIMER0_TCCR0_REG,TCCR0_COM00_BIT);
							CLEAR_BIT(MTIMER0_TCCR0_REG,TCCR0_COM01_BIT);
							break;

					case	TIMER0_COM_NOPWM_OC0_PIN_CLEAR:
							CLEAR_BIT(MTIMER0_TCCR0_REG,TCCR0_COM00_BIT);
							SET_BIT(MTIMER0_TCCR0_REG,TCCR0_COM01_BIT);
							break;

					case TIMER0_COM_NOPWM_OC0_PIN_SET:
							SET_BIT(MTIMER0_TCCR0_REG,TCCR0_COM00_BIT);
							SET_BIT(MTIMER0_TCCR0_REG,TCCR0_COM01_BIT);
							break;

					default:
						errorStatus = TIMER0_NOT_OK;
				}
			break;


		//-----------------------" Compare Output Mode with PHASE CORRECT PWM " --------------------------
		case TIMER0_PWM_PHASECORRECT_MODE:
				switch (Copy_u8COM)
				{
				case TIMER0_COM_PHASECORRECTPWM_OC0_PIN_DISCONNETED:
					CLEAR_BIT(MTIMER0_TCCR0_REG,TCCR0_COM00_BIT);
					CLEAR_BIT(MTIMER0_TCCR0_REG,TCCR0_COM01_BIT);
					break;

				case TIMER0_COM_PHASECORRECTPWM_OC0_PIN_CLEAR_COUNTUP:
					CLEAR_BIT(MTIMER0_TCCR0_REG,TCCR0_COM00_BIT);
					SET_BIT(MTIMER0_TCCR0_REG,TCCR0_COM01_BIT);
					 break;

				case TIMER0_COM_PHASECORRECTPWM_OC0_PIN_SET_COUNTUP:
					SET_BIT(MTIMER0_TCCR0_REG,TCCR0_COM00_BIT);
					SET_BIT(MTIMER0_TCCR0_REG,TCCR0_COM01_BIT);
					break;

			  default:
					errorStatus = TIMER0_NOT_OK;
			}
		break;

		//-----------------------" Compare Output Mode with FAST PWM " --------------------------
		case TIMER0_FAST_PWM_MODE:
			switch (Copy_u8COM)
				{
					case TIMER0_COM_FASTPWM_OC0_PIN_DISCONNETED:
						    CLEAR_BIT(MTIMER0_TCCR0_REG,TCCR0_COM00_BIT);
						    CLEAR_BIT(MTIMER0_TCCR0_REG,TCCR0_COM01_BIT);
						    break;

					case TIMER0_COM_FASTPWM_OC0_PIN_CLEAR:
						    CLEAR_BIT(MTIMER0_TCCR0_REG,TCCR0_COM00_BIT);
						    SET_BIT(MTIMER0_TCCR0_REG,TCCR0_COM01_BIT);
						    break;

					case TIMER0_COM_FASTPWM_OC0_PIN_SET:
						    SET_BIT(MTIMER0_TCCR0_REG,TCCR0_COM00_BIT);
						    SET_BIT(MTIMER0_TCCR0_REG,TCCR0_COM01_BIT);
						break;

					default:
						errorStatus = TIMER0_NOT_OK;
				}
			break;

	    default:
	        errorStatus = TIMER0_NOT_OK;
	 	}
		 
		 return errorStatus;
 }

/*
 * Description:
 * This function is used to check if an overflow event has occurred for Timer0.
 * The function continuously checks the Timer/Counter0 Overflow Flag (TOV0) until it becomes set.
 * Once the overflow flag is set, the function sets a local variable Local_u8OverFlowFlag to indicate the overflow event.
 * After that, the function clears the Timer/Counter0 Overflow Flag by setting the corresponding bit in the Timer/Counter0 Interrupt Flag Register (TIFR).
 * Finally, the function returns the value of Local_u8OverFlowFlag.
 */
u8  MTIMER0_u8CheckOverFlow(void)
{
	u8 Local_u8OverFlowFlag=0;
	while(GET_BIT(MTIMER_TIFR_REG, TIMER0_TOV0_BIT)!=1);
	Local_u8OverFlowFlag=1;

	// to clear Timer/Counter0 Overflow Flag
	SET_BIT(MTIMER_TIFR_REG, TIMER0_TOV0_BIT);
	 return Local_u8OverFlowFlag;
}

/*
 * Description:
 * This function is used to check if a compare match event has occurred for Timer0.
 * The function continuously checks the Timer/Counter0 Compare Match Flag (OCF0) until it becomes set.
 * Once the compare match flag is set, the function sets a local variable Local_u8CompareMatchFlag to indicate the compare match event.
 * After that, the function clears the Timer/Counter0 Compare Match Flag by setting the corresponding bit in the Timer/Counter0 Interrupt Flag Register (TIFR).
 * Finally, the function returns the value of Local_u8CompareMatchFlag.
 */
u8    MTIMER0_u8CheckCompareMatchMode(void)
{
	u8 Local_u8CompareMatchFlag=0;
	while(GET_BIT(MTIMER_TIFR_REG, TIMER0_OCF0_BIT)!=1);
		Local_u8CompareMatchFlag=1;

	// to clear Timer/Counter0 CompareMatch Flag
	SET_BIT(MTIMER_TIFR_REG, TIMER0_OCF0_BIT);
	 return Local_u8CompareMatchFlag;
}


/*
 * Description :
 * This function is used to set the compare match value for Timer/Counter0 in Timer0 of the microcontroller.
 * It takes an 8-bit value Copy_u8CompareMatchValue as a parameter, which represents the compare match value to be set.
 * The function sets the compare match value by assigning it to the MTIMER0_OCR0_REG register.
 * It returns OK to indicate that the operation was successful.
 */
EN_timerError_t MTIMER0_SetCompareMatchValue(u8 Copy_u8CompareMatchValue)
{
	MTIMER0_OCR0_REG=Copy_u8CompareMatchValue;
	return TIMER0_OK;
}


/*
 * Description :
 * This function is used to set the PWM duty cycle for Timer/Counter0 in Timer0 of the micro controller.
 * It takes an 8-bit value Copy_u8DutyCycle as a parameter, which represents the desired duty cycle as a percentage (0-100).
 * The function calculates the compare match value based on the duty cycle and the maximum duty cycle value.
 * If the duty cycle is within the valid range (0-100), it sets the compare match value by assigning it to the MTIMER0_OCR0_REG register.
 * It returns OK to indicate that the operation was successful.
 */
EN_timerError_t MTIMER0_PWMDutyCycle(u8 Copy_u8DutyCycle)
{
	if(Copy_u8DutyCycle<=100&&Copy_u8DutyCycle>0)
	{
		u8 local_CompareMatchValue=(Copy_u8DutyCycle*TIMER0_OverFlowValue)/TIMER0_MaxDutyCycle;

		MTIMER0_OCR0_REG=local_CompareMatchValue;
	}
	return TIMER0_OK;
}


/*
 * Description :
 * This function is used to set the callback function for the Timer/Counter0 overflow interrupt in Timer0 of the microcontroller.
 * It takes a function pointer TIMER0_OF_ISR as a parameter, which represents the callback function to be set.
 * The function assigns the callback function to the TIMER0_CALL_BACK_OverFlow function pointer.
 * It returns OK to indicate that the operation was successful.
 */
EN_timerError_t MTIMER0_voidSetCallBack_OverFlow(void (*TIMER0_OF_ISR)(void))
{
	TIMER0_CALL_BACK_OverFlow=TIMER0_OF_ISR;
	//SET_BIT(MTIMER_TIMSK_REG,TIMSK_TOIE0_BIT);
	return TIMER0_OK;
}

/*
 * Description :
 * This function is used to set the callback function for the required time interrupt in Timer0 of the microcontroller.
 * It takes a function pointer TIMER0_OF_RT_ISR as a parameter, which represents the callback function to be set.
 * The function assigns the callback function to the TIMER0_CALL_BACK_REQUIREDTIME function pointer.
 * It returns OK to indicate that the operation was successful.
 */
EN_timerError_t MTIMER0_voidSetCallBack_REQUIREDTIME(void (*TIMER0_OF_RT_ISR)(void))
{
	TIMER0_CALL_BACK_REQUIREDTIME=TIMER0_OF_RT_ISR;
	//SET_BIT(MTIMER_TIMSK_REG,TIMSK_TOIE0_BIT);
	return TIMER0_OK;
}


/*
 * Description :
 * This function is used to set the callback function for the Timer/Counter0 compare match interrupt in Timer0 of the microcontroller.
 * It takes a function pointer TIMER0_CMV_ISR as a parameter, which represents the callback function to be set.
 * The function assigns the callback function to the TIMER0_CALL_BACK_CompareMatch function pointer.
 * It also enables the compare match interrupt by setting the appropriate bit in the MTIMER_TIMSK_REG register.
 * It returns OK to indicate that the operation was successful.
 */
EN_timerError_t MTIMER0_voidSetCallBack_CompareMatchValue(void (*TIMER0_CMV_ISR)(void))
{
	TIMER0_CALL_BACK_CompareMatch=TIMER0_CMV_ISR;
	SET_BIT(MTIMER_TIMSK_REG,TIMSK_OCIE0_BIT);
	return TIMER0_OK;
}

//TIMER0 COMP Timer/Counter0 Compare Match  Interrupt Vector
void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	if (TIMER0_CALL_BACK_CompareMatch!=NULL_PTR) {
		TIMER0_CALL_BACK_CompareMatch();
	}
}


// TIMER0 OVF Timer/Counter0 Overflow  Interrupt Vector
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	static u32 Local_Counter=0;
	 // to indicate that the no. overflow needed is done.
	static u8  NO_OVERFLOW_Done=0;

	// to indicate that the  preload needed is done.
	//static PreLoad_Done=0;

	if((Local_Counter<GLOBAL_TIMER0_NO_OVERFLOW) && NO_OVERFLOW_Done!=1 )
	{
		Local_Counter++;
	}
	else if((Local_Counter==GLOBAL_TIMER0_NO_OVERFLOW) && NO_OVERFLOW_Done!=1 )
	{
		if(GLOBAL_TIMER0_PRELOAD!=0)
		{
			//set preload
			MTIMER0_TCNT0_REG=GLOBAL_TIMER0_PRELOAD;
		}

		NO_OVERFLOW_Done=1;

	}
			//to guard executing ISR for required time
	else if(NO_OVERFLOW_Done==1&&(GLOBAL_TIMER0_NO_OVERFLOW!=0||GLOBAL_TIMER0_PRELOAD!=0))
	{
		if (TIMER0_CALL_BACK_REQUIREDTIME!=NULL_PTR)
		{
			//REQUIRED TIME time ISR Calling
			TIMER0_CALL_BACK_REQUIREDTIME();

			//disable overflow interrupt for timer0
			CLEAR_BIT(MTIMER_TIMSK_REG,TIMSK_TOIE0_BIT);
		}

		//reset the delay valiable for new time.
		Local_Counter=0;
		NO_OVERFLOW_Done=0;
	}

//normal overflow time ISR Calling
	if (TIMER0_CALL_BACK_OverFlow!=NULL_PTR)
	{
	TIMER0_CALL_BACK_OverFlow();
	}
}






