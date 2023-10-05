
#ifndef EXTI_INT_H
#define EXTI_INT_H
#include "../../LIB/STD_TYPES.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	EXTI_OK,EXTI_NOT_OK
}EN_extiError_t;
/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * This function enables the global interrupt by setting the global 
 * interrupt enable flag. It set the bit in the status register (SREG).
 * It returns an error status the success or failure of the operation.
 */
EN_extiError_t MEXTI_GlobalInterruptEnable(void);


/*
 * Description :
 * This function disables the global interrupt by clearing the global
 * interrupt enable flag. It set the bit in the status register (SREG).
 * It returns an error status the success or failure of the operation.
 */
EN_extiError_t MEXTI_GlobalInterruptDisable(void);


/*
 * Description :
 * This function enables an external interrupt on the specified interrupt pin
 * (INT0_PIN, INT1_PIN, or INT2_PIN) with the specified interrupt sensing level
 * (LOW_LEVEL, ANY_LOGICAL_CHANGE, FALLING_EDGE, or RISING_EDGE). It configures
 * the interrupt sensing level by setting or clearing the corresponding bits in 
 * the control registers. It also enables the specific external interrupt by setting
 * the corresponding bit in the general interrupt control register (GICR).
 */
EN_extiError_t MEXTI_EnableInterrupt(u8 u8_arg_InterruptPIN,u8 u8_arg_InterruptSensingLevel);


/*
 * Description :
 * This function disables an external interrupt on the specified interrupt pin
 * (INT0_PIN, INT1_PIN, or INT2_PIN). It clears the corresponding bit in the general 
 * interrupt control register (GICR) to disable the specific external interrupt.
 */
EN_extiError_t MEXTI_DisableInterrupt(u8 u8_arg_InterruptPIN);

EN_extiError_t MEXTI_0_SET_CALL_BACK(void(*Copy_Pfunction_ISR_INT0)(void));

EN_extiError_t MEXTI_1_SET_CALL_BACK(void(*Copy_Pfunction_ISR_INT1)(void));

EN_extiError_t MEXTI_2_SET_CALL_BACK(void(*Copy_Pfunction_ISR_INT2)(void));

#endif
