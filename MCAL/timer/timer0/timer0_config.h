#ifndef  TIMER_CFG_H
#define TIMER_CFG_H

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define CPU_F				8000000UL
#define TIMER0_RESOLUTION	8


//__________________|Timer/Counter Mode of Operations |_____________________
			//TCCR0->   WGM01=0      WGM00 = 0
#define	TIMER0_NORMAL_MODE													0

			//TIMER0->	WGM01=0      WGM00 = 1
#define	TIMER0_PWM_PHASECORRECT_MODE										1

// Clear Timer on Compare    --.> TCCR0->	WGM01=1      WGM00 = 0
#define	TIMER0_CTC_MODE														2


			//TCCR0->	WGM01=1      WGM00 = 1
#define	TIMER0_FAST_PWM_MODE												3

//__________________| Compare Output Mode |____________________________
//  1) non-PWM Mode
		//TCCR0->	COM01=0      COM00 = 0
#define	TIMER0_COM_NOPWM_OC0_PIN_DISCONNETED							0
		//TCCR0->	COM01=0      COM00 = 1
#define	TIMER0_COM_NOPWM_OC0_PIN_TOGGLE									1
		//TCCR0->	COM01=1      COM00 = 0
#define	TIMER0_COM_NOPWM_OC0_PIN_CLEAR									2
		//TCCR0->	COM01=1      COM00 = 1
#define	TIMER0_COM_NOPWM_OC0_PIN_SET									3

// 2) Fast PWM Mode
		//TCCR0->	COM01=0      COM00 = 0
#define	TIMER0_COM_FASTPWM_OC0_PIN_DISCONNETED								4
		//TCCR0->	COM01=1      COM00 = 0  ||set OC0 at TOP
#define	TIMER0_COM_FASTPWM_OC0_PIN_CLEAR									5
		//TCCR0->	COM01=1      COM00 = 1  ||clear OC0 at TOP
#define	TIMER0_COM_FASTPWM_OC0_PIN_SET										6

// 3)  Phase Correct PWM Mode
		//TCCR0->	COM01=0      COM00 = 0
#define	TIMER0_COM_PHASECORRECTPWM_OC0_PIN_DISCONNETED		7
//TCCR0 -> 	COM01=1      COM00 = 0     ||Clear OC0 on compare match when up-counting. Set OC0 on compare  match when downcounting
#define	TIMER0_COM_PHASECORRECTPWM_OC0_PIN_CLEAR_COUNTUP	8
//TCCR0 ->	COM01=1      COM00 = 1	 ||Set OC0 on compare match when up-counting. Clear OC0 on compare match when downcounting
#define	TIMER0_COM_PHASECORRECTPWM_OC0_PIN_SET_COUNTUP		9

//________________________| Clock Select Bit Description|________________________
 //TCCR0-> CS02=0    | CS01=0  |   CS00=0
#define TIMER0_CS_STOP																		0
 //TCCR0-> CS02=0  |   CS01=0  |  CS00=1
#define TIMER0_CS_NOPRESCALLER										1
 //TCCR0-> CS02=0   |  CS01=1   |  CS00=0
#define TIMER0_CS_PRESCALLER_8										2
 //TCCR0-> CS02=0     CS01=1     CS00=1
#define TIMER0_CS_PRESCALLER_64	     								3
 //TCCR0-> CS02=1     CS01=0     CS00=0
#define TIMER0_CS_PRESCALLER_256									4
 //TCCR0-> CS02=1     CS01=0     CS00=1
#define TIMER0_CS_PRESCALLER_1024									5

/*
 If external pin modes are used for the Timer/Counter0, transitions on the T0 pin will
clock the counter even if the pin is configured as an output. This feature allows software
control of the counting.*/
 //TCCR0 -> 	CS02=1     CS01=1     CS00=0
#define TIMER0_CS_EXTERNAL_T0_PIN_FALLINGEDGE						6
 //TCCR0 ->		CS02=1     CS01=1     CS00=1
#define TIMER0_CS_EXTERNAL_T0_PIN_RISINGEDGE						7
//_______________________________________________________________________________________




#endif
