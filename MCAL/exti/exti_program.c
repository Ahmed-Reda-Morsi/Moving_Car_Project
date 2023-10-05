#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "exti_config.h"
#include "exti_interface.h"
#include "exti_private.h"

//#define _VECTOR(N) __vector_ ## N
//
//#define INT0_vect _VECTOR(1)  /* External Interrupt Request 0*/

// global pointers to functions for INT0 , INT1 and INT2 ISRs
void (*EXTI_0_CALL_BACK)(void)=NULL;
void (*EXTI_1_CALL_BACK)(void)=NULL;
void (*EXTI_2_CALL_BACK)(void)=NULL;

/*
 * Description :
 * This function enables the global interrupt by setting the global 
 * interrupt enable flag. It set the bit in the status register (SREG).
 * It returns an error status the success or failure of the operation.
 */
EN_extiError_t MEXTI_GlobalInterruptEnable(void)
{
	SET_BIT(MEXTINT_SREG_REG, GEI_PIN);
	return EXTI_OK;
}


/*
 * Description :
 * This function disables the global interrupt by clearing the global
 * interrupt enable flag. It set the bit in the status register (SREG).
 * It returns an error status the success or failure of the operation.
 */
EN_extiError_t MEXTI_GlobalInterruptDisable(void)
{
	CLEAR_BIT(MEXTINT_SREG_REG, GEI_PIN);
	return EXTI_OK;
}


/*
 * Description :
 * This function enables an external interrupt on the specified interrupt pin
 * (INT0_PIN, INT1_PIN, or INT2_PIN) with the specified interrupt sensing level
 * (LOW_LEVEL, ANY_LOGICAL_CHANGE, FALLING_EDGE, or RISING_EDGE). It configures
 * the interrupt sensing level by setting or clearing the corresponding bits in 
 * the control registers. It also enables the specific external interrupt by setting
 * the corresponding bit in the general interrupt control register (GICR).
 */
EN_extiError_t MEXTI_EnableInterrupt(u8 u8_arg_InterruptPIN, u8 u8_arg_InterruptSensingLevel)
{
	EN_extiError_t enum_Local_errorStatus = EXTI_OK;
	
	switch (u8_arg_InterruptPIN)
	{
	case INT0_PIN:
			switch (u8_arg_InterruptSensingLevel)
			{
			case LOW_LEVEL:
				//The low level of INT0 generates an interrupt request.
				CLEAR_BIT(MEXTINT_MCUCR_REG, INT0_ISC00_PIN);
				CLEAR_BIT(MEXTINT_MCUCR_REG, INT0_ISC01_PIN);
				break;

			case ANY_LOGICAL_CHANGE:
				//Any logical change on INT0 generates an interrupt request
				SET_BIT(MEXTINT_MCUCR_REG, INT0_ISC00_PIN);
				CLEAR_BIT(MEXTINT_MCUCR_REG, INT0_ISC01_PIN);
				break;

			case FALLING_EDGE:
				//The falling edge of INT0 generates an interrupt request
				CLEAR_BIT(MEXTINT_MCUCR_REG, INT0_ISC00_PIN);
				SET_BIT(MEXTINT_MCUCR_REG, INT0_ISC01_PIN);
				break;

			case RISING_EDGE:
				// The rising edge of INT0 generates an interrupt request.
				SET_BIT(MEXTINT_MCUCR_REG, INT0_ISC00_PIN);
				SET_BIT(MEXTINT_MCUCR_REG, INT0_ISC01_PIN);
				break;
			}
		//enable external interrupt  INT0.
		SET_BIT(MEXTINT_GICR_REG, INT0_PIN);
		break;

	case INT1_PIN:
			switch (u8_arg_InterruptSensingLevel)
			{
			case LOW_LEVEL:
				//The low level of INT1 generates an interrupt request.
				CLEAR_BIT(MEXTINT_MCUCR_REG, INT1_ISC10_PIN);
				CLEAR_BIT(MEXTINT_MCUCR_REG, INT1_ISC11_PIN);
				break;

			case ANY_LOGICAL_CHANGE:
				//Any logical change on INT1 generates an interrupt request
				SET_BIT(MEXTINT_MCUCR_REG, INT1_ISC10_PIN);
				CLEAR_BIT(MEXTINT_MCUCR_REG, INT1_ISC11_PIN);
				break;

			case FALLING_EDGE:
				//The falling edge of INT1 generates an interrupt request
				CLEAR_BIT(MEXTINT_MCUCR_REG, INT1_ISC10_PIN);
				SET_BIT(MEXTINT_MCUCR_REG, INT1_ISC11_PIN);
				break;

			case RISING_EDGE:
				// The rising edge of INT1 generates an interrupt request.
				SET_BIT(MEXTINT_MCUCR_REG, INT1_ISC10_PIN);
				SET_BIT(MEXTINT_MCUCR_REG, INT1_ISC11_PIN);
				break;
			}
		//enable external interrupt  INT1.
		SET_BIT(MEXTINT_GICR_REG, INT1_PIN);
		break;

	case INT2_PIN:
			switch (u8_arg_InterruptSensingLevel)
			{
			case FALLING_EDGE:
				//The falling edge of INT2 generates an interrupt request
				CLEAR_BIT(MEXTINT_MCUCSR_REG, INT2_ISC2_PIN);
				break;
			case RISING_EDGE:
				// The rising edge of INT2 generates an interrupt request.
				SET_BIT(MEXTINT_MCUCSR_REG, INT2_ISC2_PIN);
				break;
			}
	    //enable external interrupt  INT2.
		SET_BIT(MEXTINT_GICR_REG, INT2_PIN);
		break;
	default:
		enum_Local_errorStatus = EXTI_NOT_OK;
	}
	return enum_Local_errorStatus;
}


/*
 * Description :
 * This function disables an external interrupt on the specified interrupt pin
 * (INT0_PIN, INT1_PIN, or INT2_PIN). It clears the corresponding bit in the general 
 * interrupt control register (GICR) to disable the specific external interrupt.
 */
EN_extiError_t MEXTI_DisableInterrupt(u8 u8_arg_InterruptPIN)
{
		EN_extiError_t enum_Local_errorStatus = EXTI_OK;
		switch (u8_arg_InterruptPIN)
		{
		case INT0_PIN:
			//disable external interrupt  INT0.
			CLEAR_BIT(MEXTINT_GICR_REG, INT0_PIN);
			break;
		case INT1_PIN:
			//disable external interrupt  INT0.
			CLEAR_BIT(MEXTINT_GICR_REG, INT1_PIN);
			break;
		case INT2_PIN:
			//disable external interrupt  INT0.
			CLEAR_BIT(MEXTINT_GICR_REG, INT2_PIN);
			break;
		default:
			enum_Local_errorStatus = EXTI_NOT_OK;
		}
		return enum_Local_errorStatus;
	
}


//================== Set call back functions(ISR) for external interrupts.=====================

/*
 * Description :
 * This function sets the callback function for the external interrupt INT0.
 * It assigns the specified function pointer Copy_Pfunction_ISR_INT0 to the global
 * variable EXTI_0_CALL_BACK, which represents the interrupt service routine (ISR) for INT0.
 */
EN_extiError_t MEXTI_0_SET_CALL_BACK(void (*Copy_Pfunction_ISR_INT0)(void))
{
	EXTI_0_CALL_BACK = Copy_Pfunction_ISR_INT0;
	return EXTI_OK;
}


/*
 * Description :
 * This function sets the callback function for the external interrupt INT1.
 * It assigns the specified function pointer Copy_Pfunction_ISR_INT1 to the 
 * global variable EXTI_1_CALL_BACK, which represents the interrupt service routine (ISR) for INT1.
 */
EN_extiError_t MEXTI_1_SET_CALL_BACK(void(*Copy_Pfunction_ISR_INT1)(void))
{
	EXTI_1_CALL_BACK=Copy_Pfunction_ISR_INT1;
	return EXTI_OK;
}

/*
 * Description :
 * This function sets the callback function for the external interrupt INT2.
 * It assigns the specified function pointer Copy_Pfunction_ISR_INT2 to the global 
 * variable EXTI_2_CALL_BACK, which represents the interrupt service routine (ISR) for INT2.
  */
EN_extiError_t MEXTI_2_SET_CALL_BACK(void(*Copy_Pfunction_ISR_INT2)(void))
{
	EXTI_2_CALL_BACK=Copy_Pfunction_ISR_INT2;
	return EXTI_OK;
}


//=================== set vectors for External Interrupt Requests of interrupt vector table (IVT) ==================================
/*
vector 1  of IVT for External Interrupt Request 0
 */
// disable Linker optimization process for vector_1
void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
	//call the ISR for INT0 implemented in the APP layer.
	EXTI_0_CALL_BACK();
}

/*
vector 2 of IVT for External Interrupt Request 1
 */
// disable Linker optimization process for vector_2
void __vector_2(void)  __attribute__((signal));
void __vector_2(void)
{
	EXTI_1_CALL_BACK();
}

/*
vector 3 of IVT for External Interrupt Request 2
 */
// disable Linker optimization process for vector_3
void __vector_3(void)  __attribute__((signal));
void __vector_3(void)
{
	EXTI_2_CALL_BACK();
}