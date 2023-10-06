#include "../../../LIB/STD_TYPES.h"
#include "../../../LIB/BIT_MATH.h"
#include <math.h>


#include "timer0_config.h"
#include "timer0_interface.h"
#include "timer0_private.h"

void (*TIMER0_CALL_BACK_REQUIREDTIME)(void)=NULL_PTR;

/*******************************************************************************
 *                               Static-Variables                              *
 *******************************************************************************/
static u16 u16_GLOBAL_TIMER0_PRESCALER=0;

static u32 u32_GLOBAL_TIMER0_NO_OVERFLOW=0;
static u32 u32_GLOBAL_TIMER0_PRELOAD=0;

static u8 u8_GLOBAL_TickTime=0;
static u16 u16_GLOBAL_TimeOverFlow=0;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description:
 * This function initializes Timer0 with the specified mode and prescaler,
 * and returns error status.
 * open cfg  header to configure TIMER0
 */
EN_timerError_t MTIMER0_Init(u8 u8_arg_Mode,u8 u8_arg_PreScaler)
{
	 EN_timerError_t enum_Local_errorStatus = TIMER0_OK;
	 switch(u8_arg_Mode)
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
			enum_Local_errorStatus = TIMER0_NOT_OK;

	 }

	 //________________________________| Clock Select MODE|_________________________

	 switch(u8_arg_PreScaler)
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
			 u16_GLOBAL_TIMER0_PRESCALER=8;
				break;

		 case TIMER0_CS_PRESCALLER_64:
			 SET_BIT(MTIMER0_TCCR0_REG, TCCR0_CS00_BIT);
			 SET_BIT(MTIMER0_TCCR0_REG, TCCR0_CS01_BIT);
			 CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_CS02_BIT);
			 u16_GLOBAL_TIMER0_PRESCALER=64;
				break;

		 case TIMER0_CS_PRESCALLER_256:
			 CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_CS00_BIT);
			 CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_CS01_BIT);
			 SET_BIT(MTIMER0_TCCR0_REG, TCCR0_CS02_BIT);
			 u16_GLOBAL_TIMER0_PRESCALER=256;
				break;

		 case TIMER0_CS_PRESCALLER_1024:
			 SET_BIT(MTIMER0_TCCR0_REG, TCCR0_CS00_BIT);
			 SET_BIT(MTIMER0_TCCR0_REG, TCCR0_CS01_BIT);
			 CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_CS02_BIT);
			 u16_GLOBAL_TIMER0_PRESCALER=1024;
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
			 enum_Local_errorStatus = TIMER0_NOT_OK;
 		 }

 		 /*calucate in init func. becuase they are depend of Prescaler*/
 		 //calucate Tick time in microsecond unit.
		 u8_GLOBAL_TickTime=(u16_GLOBAL_TIMER0_PRESCALER*1000000UL)/CPU_F;
		//overflow time for Timer0 in microsecond unit.
		  u16_GLOBAL_TimeOverFlow=u8_GLOBAL_TickTime*(pow(2,TIMER0_RESOLUTION));
		  return enum_Local_errorStatus;

}


/*
 * Description:
 * This function is used to interrupt the program execution for a specified amount of time using Timer0 interrupts.
 * The delay time is provided in milliseconds and converted to microseconds.
 * The function calculates the number of Timer0 overflow cycles required to achieve the desired delay time.
 * If the delay time exceeds the maximum overflow time of Timer0, the function splits the delay into multiple overflow cycles.
 * The remainder time is stored in the preload value to be loaded into Timer0 registers after the required number of overflows.
 * The function enables the overflow interrupt for Timer0 to start the delay operation.
 */
EN_timerError_t MTIMER0_DelayInterrupt_MS(u32 u32_arg_Delay)
{
	// user delay in microsecond unit.
	u32_arg_Delay=u32_arg_Delay*1000UL;

	if (u32_arg_Delay>=u16_GLOBAL_TimeOverFlow) {

		//number of overflow needed to required time.
		u32_GLOBAL_TIMER0_NO_OVERFLOW=u32_arg_Delay/u16_GLOBAL_TimeOverFlow;

		//remainder time needed to after number of overflow required time. in  microsecond unit.
		u32_GLOBAL_TIMER0_PRELOAD=(u32_arg_Delay%u16_GLOBAL_TimeOverFlow)*(pow(2,TIMER0_RESOLUTION));

	} else if(u32_arg_Delay<u16_GLOBAL_TimeOverFlow)
	{
		//remainder required time. in  microsecond unit.
		u32_GLOBAL_TIMER0_PRELOAD=(u32_arg_Delay%u16_GLOBAL_TimeOverFlow)*(pow(2,TIMER0_RESOLUTION));

	}
	//Enable overflow interrupt for timer0
	SET_BIT(MTIMER_TIMSK_REG,TIMSK_TOIE0_BIT);
	return TIMER0_OK;
}


/*
 * Description :
 * This function is used to set the callback function for the required time interrupt in Timer0 of the microcontroller.
 * It takes a function pointer TIMER0_OF_RT_ISR as a parameter, which represents the callback function to be set.
 * The function assigns the callback function to the TIMER0_CALL_BACK_REQUIREDTIME function pointer.
 * It returns OK to indicate that the operation was successful.
 */
EN_timerError_t MTIMER0_SetCallBack_REQUIREDTIME(void (*TIMER0_OF_RT_ISR)(void))
{
	TIMER0_CALL_BACK_REQUIREDTIME=TIMER0_OF_RT_ISR;
	
	return TIMER0_OK;
}



// TIMER0 OVF Timer/Counter0 Overflow  Interrupt Vector
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{ 
	static u32 Local_Counter=0;
	 // to indicate that the no. overflow needed is done.
	static u8  NO_OVERFLOW_Done=0;

	if((Local_Counter<u32_GLOBAL_TIMER0_NO_OVERFLOW) && NO_OVERFLOW_Done!=1 )
	{
		Local_Counter++;
	}
	else if((Local_Counter==u32_GLOBAL_TIMER0_NO_OVERFLOW) && NO_OVERFLOW_Done!=1 )
	{
		if(u32_GLOBAL_TIMER0_PRELOAD!=0)
		{
			//set preload
			MTIMER0_TCNT0_REG=u32_GLOBAL_TIMER0_PRELOAD;
		}

		NO_OVERFLOW_Done=1;

	}
			//to guard executing ISR for required time
	else if(NO_OVERFLOW_Done==1&&(u32_GLOBAL_TIMER0_NO_OVERFLOW!=0||u32_GLOBAL_TIMER0_PRELOAD!=0))
	{
		if (TIMER0_CALL_BACK_REQUIREDTIME!=NULL_PTR)
		{
			//REQUIRED TIME time ISR Calling
			TIMER0_CALL_BACK_REQUIREDTIME();

		}

		//reset the delay valiable for new time.
		Local_Counter=0;
		NO_OVERFLOW_Done=0;
	}

}






