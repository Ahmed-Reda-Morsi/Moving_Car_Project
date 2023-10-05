
#ifndef MOTOR_CONFIG_H_
#define MOTOR_CONFIG_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define MOTOR_1					1
#define MOTOR_2					2
#define MOTOR_3					3
#define MOTOR_4					4


#define	 MOTOR_STOP				0
#define  MOTOR_STATE_INTIAL		1
#define  MOTOR_LONG_SIDE		2
#define  MOTOR_SHORT_SIDE		3

#define  MOTOR_PIN_IN			0
#define  MOTOR_PIN_OUT			1

#define MOTOR_FORWARD			1
#define MOTOR_BACKWARD			0


//MOTOR CONDITION
#define MOTOR_HIGH				1
#define MOTOR_LOW				0



// Motor driver connections
#define MOTOR3_PORT				PORTD
#define MOTOR3_ENABLE_PIN		PIN1
#define MOTOR3_DIRECTION1_PIN 	PIN6
#define MOTOR3_DIRECTION2_PIN 	PIN5



#define MOTOR1_PORT				PORTB
			 
#define MOTOR1_ENABLE_PIN		PIN0
#define MOTOR1_DIRECTION1_PIN	PIN1
#define MOTOR1_DIRECTION2_PIN	PIN2


#define MOTOR2_PORT				PORTA
#define MOTOR2_ENABLE_PIN		PIN0
#define MOTOR2_DIRECTION1_PIN 	PIN1
#define MOTOR2_DIRECTION2_PIN 	PIN2


#define MOTOR4_PORT				PORTC

#define MOTOR4_ENABLE_PIN		PIN0
#define MOTOR4_DIRECTION1_PIN 	PIN1
#define MOTOR4_DIRECTION2_PIN 	PIN2




#endif /* MOTOR_CONFIG_H_ */