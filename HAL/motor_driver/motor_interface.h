

#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_

/*******************************************************************************
 *                               LED Enum errorState                           *
 *******************************************************************************/
typedef enum
{
	MOTOR_OK,MOTOR_NOT_OK
}EN_MOTORErrorState_t;


/*******************************************************************************
 *                                LIB MATH                                     *
 *******************************************************************************/

#include "../../LIB/STD_TYPES.h"



/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description:
 * This function initializes the motor control module, setting up the necessary 
 * configurations and resources to control the motors.
 */
EN_MOTORErrorState_t	HMOTOR_init(void);


/*
 * Description:
 * This function sets the speed ratio for all motors, allowing control of the overall speed of the motors.
 */
EN_MOTORErrorState_t	HMOTOR_set_Allspeed(u8 u8_arg_motorSpeedRatio);


/*
 * Description:
 * This function controls the movement of a specific motor by specifying its number and the desired direction.
 */
EN_MOTORErrorState_t	HMOTOR_move(u8 u8_arg_MotorNumber,u8 u8_arg_MotorDirection);


/*
 * Description:
 * This function starts moving motors in the same direction with 50% of max speed and turns on the LED.
 */
EN_MOTORErrorState_t	HMOTORS_MovingForward(void);

/*
 * Description:
 * This function halts the movement of all motors, bringing them to a stop, and turns on the LED.
 */
EN_MOTORErrorState_t	HMOTOR_Allstop(void);


/*
 * Description:
 * This function rotates all motors in the right direction simultaneously.
 */
EN_MOTORErrorState_t	HMOTORS_RotateRight(void);

#endif /* MOTOR_INTERFACE_H_ */