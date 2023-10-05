#ifndef EXT_INT_PRV_H
#define EXT_INT_PRV_H
#include "../../LIB/STD_TYPES.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define NULL								0

// Global Interrupt Enable
#define GEI_PIN                     		7 		//PIN7

// EXT Interrupt Sense Control for INT0 ,INT1 and INT2

#define INT0_ISC00_PIN              		0		//PIN0
#define INT0_ISC01_PIN              		1		//PIN1

#define INT1_ISC10_PIN              		2		//PIN2
#define INT1_ISC11_PIN              		3		//PIN3

#define INT2_ISC2_PIN               		6		//PIN6

// EXT pins enables
#define INT0_PIN                   			6		//PIN6
#define INT1_PIN                     		7 		//PIN7
#define INT2_PIN                    		5 		//PIN5


// AVR Status Register.
#define MEXTINT_SREG_REG            	*((volatile u8 *)0x5F)
// MCU Control Register contains control bits for interrupt sense control for INT0 and INT1
#define MEXTINT_MCUCR_REG          	 	*((volatile u8 *)0x55)
//MCU Control and Status Register contains control bits for interrupt sense control for INT2
#define MEXTINT_MCUCSR_REG          	*((volatile u8 *)0x54)
//General Interrupt Control Register to enable or disable interrupts.
#define MEXTINT_GICR_REG            	*((volatile u8 *)0x5B)

#endif
