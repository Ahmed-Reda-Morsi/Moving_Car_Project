

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


EN_MOTORErrorState_t	HMOTOR_init(void);
EN_MOTORErrorState_t	HMOTOR_set_Allspeed(u8 u8_argument_motorSpeedRatio);
EN_MOTORErrorState_t	HMOTOR_move(u8 u8_argument_MotorNumber,u8 u8_argument_MotorDirection);
EN_MOTORErrorState_t	HMOTORS_MovingForward(void);
EN_MOTORErrorState_t	HMOTOR_Allstop(void);
EN_MOTORErrorState_t	HMOTORS_RotateRight(void);

#endif /* MOTOR_INTERFACE_H_ */