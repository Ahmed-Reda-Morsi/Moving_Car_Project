
#include "motor_config.h"
#include "motor_interface.h"
#include "motor_private.h"

/*******************************************************************************
 *                                LIB MATH                                     *
 *******************************************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"


/*******************************************************************************
 *                                DIO LIB                                      *
 *******************************************************************************/
#include "../../MCAL/dio/dio_interface.h"
#include "../../MCAL/exti/exti_interface.h"
#include "../../MCAL/exti/exti_config.h"
#include "../../MCAL/timer/timer2/timer2_interface.h"
#include "../../MCAL/timer/timer2/timer2_config.h"
EN_MOTORErrorState_t	HMOTOR_init(void)
{
	EN_MOTORErrorState_t enum_Local_errorStatus=MOTOR_OK;
	enum_Local_errorStatus= MDIO_SetPinDirection ( MOTOR1_PORT, MOTOR1_ENABLE_PIN, MOTOR_PIN_OUT);
	enum_Local_errorStatus= MDIO_SetPinDirection ( MOTOR1_PORT, MOTOR1_DIRECTION1_PIN, MOTOR_PIN_OUT);
	enum_Local_errorStatus= MDIO_SetPinDirection ( MOTOR1_PORT, MOTOR1_DIRECTION2_PIN, MOTOR_PIN_OUT);


	enum_Local_errorStatus= MDIO_SetPinDirection ( MOTOR2_PORT, MOTOR2_ENABLE_PIN, MOTOR_PIN_OUT);
	enum_Local_errorStatus= MDIO_SetPinDirection ( MOTOR2_PORT, MOTOR2_DIRECTION1_PIN, MOTOR_PIN_OUT);
	enum_Local_errorStatus= MDIO_SetPinDirection ( MOTOR2_PORT, MOTOR2_DIRECTION2_PIN, MOTOR_PIN_OUT);

	enum_Local_errorStatus= MDIO_SetPinDirection ( MOTOR3_PORT, MOTOR3_ENABLE_PIN, MOTOR_PIN_OUT);
	enum_Local_errorStatus= MDIO_SetPinDirection ( MOTOR3_PORT,  MOTOR3_DIRECTION1_PIN, MOTOR_PIN_OUT);
	enum_Local_errorStatus= MDIO_SetPinDirection ( MOTOR3_PORT, MOTOR3_DIRECTION2_PIN, MOTOR_PIN_OUT);

	enum_Local_errorStatus= MDIO_SetPinDirection ( MOTOR4_PORT, MOTOR4_ENABLE_PIN, MOTOR_PIN_OUT);
	enum_Local_errorStatus= MDIO_SetPinDirection ( MOTOR4_PORT, MOTOR4_DIRECTION1_PIN, MOTOR_PIN_OUT);
	enum_Local_errorStatus= MDIO_SetPinDirection ( MOTOR4_PORT, MOTOR4_DIRECTION2_PIN, MOTOR_PIN_OUT);
	 
	enum_Local_errorStatus= MTIMER2_PWM_init();
	enum_Local_errorStatus= MTIMER2_Init(TIMER2_NORMAL_MODE,TIMER2_CS_PRESCALLER_8);
	
	if (enum_Local_errorStatus!=MOTOR_OK)
	{
		enum_Local_errorStatus=MOTOR_NOT_OK;
	}
	return enum_Local_errorStatus;
}

EN_MOTORErrorState_t	HMOTOR_set_Allspeed(u8 u8_arg_motorSpeedRatio)
{
	EN_MOTORErrorState_t errorStatus=MOTOR_OK;
	if(MTIMER2_SetPWMNormalMode_DutyCycle(u8_arg_motorSpeedRatio)==TIMER2_NOT_OK)
	{
		errorStatus=MOTOR_NOT_OK;
	}
	else
	{
		//"DO NOTHING."
	}
	return errorStatus;
}

EN_MOTORErrorState_t	HMOTOR_move(u8 u8_arg_MotorNumber,u8 u8_arg_MotorDirection)
{
	EN_MOTORErrorState_t errorStatus=MOTOR_OK;
	switch(u8_arg_MotorNumber)
	{
		case MOTOR_1:
			MDIO_SetPinValue(MOTOR1_PORT,MOTOR1_ENABLE_PIN,MOTOR_HIGH);
			switch(u8_arg_MotorDirection)
			{
				case MOTOR_FORWARD:
					MDIO_SetPinValue(MOTOR1_PORT,MOTOR1_DIRECTION1_PIN,MOTOR_HIGH);
					MDIO_SetPinValue(MOTOR1_PORT,MOTOR1_DIRECTION2_PIN,MOTOR_LOW);
					break;
				case MOTOR_BACKWARD:
					MDIO_SetPinValue(MOTOR1_PORT,MOTOR1_DIRECTION2_PIN,MOTOR_HIGH);
					MDIO_SetPinValue(MOTOR1_PORT,MOTOR1_DIRECTION1_PIN,MOTOR_LOW);
					break;
			 default:
				errorStatus=MOTOR_NOT_OK;
				break;
			}
			break;
	case MOTOR_2:
		MDIO_SetPinValue(MOTOR2_PORT,MOTOR2_ENABLE_PIN,MOTOR_HIGH);
		switch(u8_arg_MotorDirection)
		{
			case MOTOR_FORWARD:
				MDIO_SetPinValue(MOTOR2_PORT,MOTOR2_DIRECTION1_PIN,MOTOR_HIGH);
				MDIO_SetPinValue(MOTOR2_PORT,MOTOR2_DIRECTION2_PIN,MOTOR_LOW);
				break;
			case MOTOR_BACKWARD:
				MDIO_SetPinValue(MOTOR2_PORT,MOTOR2_DIRECTION2_PIN,MOTOR_HIGH);
				MDIO_SetPinValue(MOTOR2_PORT,MOTOR2_DIRECTION1_PIN,MOTOR_LOW);
				break;
			default:
				errorStatus=MOTOR_NOT_OK;
				break;
		}
		break;
	
case MOTOR_3:
		MDIO_SetPinValue(MOTOR3_PORT,MOTOR3_ENABLE_PIN,MOTOR_HIGH);
		switch(u8_arg_MotorDirection)
		{
			case MOTOR_FORWARD:
				MDIO_SetPinValue(MOTOR3_PORT,MOTOR3_DIRECTION1_PIN,MOTOR_HIGH);
				MDIO_SetPinValue(MOTOR3_PORT,MOTOR3_DIRECTION2_PIN,MOTOR_LOW);
				break;
			case MOTOR_BACKWARD:
				MDIO_SetPinValue(MOTOR3_PORT,MOTOR3_DIRECTION2_PIN,MOTOR_HIGH);
				MDIO_SetPinValue(MOTOR3_PORT,MOTOR3_DIRECTION1_PIN,MOTOR_LOW);
				break;
			default:
				errorStatus=MOTOR_NOT_OK;
				break;
		}
		break;
	
	case MOTOR_4:
		MDIO_SetPinValue(MOTOR4_PORT,MOTOR4_ENABLE_PIN,MOTOR_HIGH);
		switch(u8_arg_MotorDirection)
		{
		case MOTOR_FORWARD:
			MDIO_SetPinValue(MOTOR4_PORT,MOTOR4_DIRECTION1_PIN,MOTOR_HIGH);
			MDIO_SetPinValue(MOTOR4_PORT,MOTOR4_DIRECTION2_PIN,MOTOR_LOW);
			break;
		case MOTOR_BACKWARD:
			MDIO_SetPinValue(MOTOR4_PORT,MOTOR4_DIRECTION2_PIN,MOTOR_HIGH);
			MDIO_SetPinValue(MOTOR4_PORT,MOTOR4_DIRECTION1_PIN,MOTOR_LOW);
			break;
		default:
			errorStatus=MOTOR_NOT_OK;
			break;
		}
		break;
	default:
		errorStatus=MOTOR_NOT_OK;	
		break;
	}
	return errorStatus;
}


EN_MOTORErrorState_t	HMOTORS_MovingForward(void)
{
	EN_MOTORErrorState_t enum_Local_errorStatus=MOTOR_OK;
	enum_Local_errorStatus=HMOTOR_move(MOTOR_1,MOTOR_FORWARD);
	enum_Local_errorStatus=HMOTOR_move(MOTOR_2,MOTOR_FORWARD);
	enum_Local_errorStatus=HMOTOR_move(MOTOR_3,MOTOR_FORWARD);
	enum_Local_errorStatus=HMOTOR_move(MOTOR_4,MOTOR_FORWARD);
	 return enum_Local_errorStatus;
}

EN_MOTORErrorState_t	HMOTORS_RotateRight(void)
{
	EN_MOTORErrorState_t enum_Local_errorStatus=MOTOR_OK;
	enum_Local_errorStatus=HMOTOR_move(MOTOR_1,MOTOR_FORWARD);
	enum_Local_errorStatus=HMOTOR_move(MOTOR_2,MOTOR_BACKWARD);
	enum_Local_errorStatus=HMOTOR_move(MOTOR_3,MOTOR_FORWARD);
	enum_Local_errorStatus=HMOTOR_move(MOTOR_4,MOTOR_BACKWARD);
	return enum_Local_errorStatus;
}
EN_MOTORErrorState_t	HMOTOR_Allstop(void)
{
	EN_MOTORErrorState_t enum_Local_errorStatus=MOTOR_OK;
	
	enum_Local_errorStatus=MDIO_SetPinValue(MOTOR1_PORT,MOTOR1_ENABLE_PIN,MOTOR_LOW);
	enum_Local_errorStatus=MDIO_SetPinValue(MOTOR2_PORT,MOTOR2_ENABLE_PIN,MOTOR_LOW);
	enum_Local_errorStatus=MDIO_SetPinValue(MOTOR3_PORT,MOTOR3_ENABLE_PIN,MOTOR_LOW);
	enum_Local_errorStatus=MDIO_SetPinValue(MOTOR4_PORT,MOTOR4_ENABLE_PIN,MOTOR_LOW);
	if(enum_Local_errorStatus==MOTOR_OK)
	{
		enum_Local_errorStatus=MOTOR_NOT_OK;
	}

	return enum_Local_errorStatus;
}
