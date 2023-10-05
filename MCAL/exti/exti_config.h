#ifndef EXT_INT_CFG_H
#define EXT_INT_CFG_H
#include "exti_private.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
// EXT pins enables
#define INT0_PIN                   					6		//PIN6
#define INT1_PIN                     				7 		//PIN7
#define INT2_PIN                    				5 		//PIN5

// Sensing Control Levels
#define LOW_LEVEL                  					1
#define ANY_LOGICAL_CHANGE							2
#define FALLING_EDGE                				3
#define RISING_EDGE                 				4

//Global interrupt control
#define GLOBAL_INTERRUPT_ENABLE						1
#define GLOBAL_INTERRUPT_DISABLE	 				0

#endif
