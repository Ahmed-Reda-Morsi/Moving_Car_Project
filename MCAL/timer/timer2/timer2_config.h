


#ifndef TIMER2_CONFIG_H_
#define TIMER2_CONFIG_H_

#define CPU_F				8000000UL
#define TIMER2_RESOLUTION	8

#define PWM_NORMAL_MODE_PIN       5
#define PWM_NORMAL_MODE_PORT      2
#define PWM_NORMAL_MODE_PERIOD   200

//__________________|Timer/Counter Mode of Operations |_____________________
//TCCR2->   WGM21=0      WGM20 = 0
#define	TIMER2_NORMAL_MODE											0

//TIMER2->	WGM21=0      WGM20 = 1
#define	TIMER2_PWM_PHASECORRECT_MODE								1

// Clear Timer on Compare    --.> TCCR2->	WGM21=1      WGM20 = 0
#define	TIMER2_CTC_MODE												2


//TCCR2->	WGM21=1      WG20 = 1
#define	TIMER2_FAST_PWM_MODE										3

//__________________| Compare Output Mode |____________________________
//  1) non-PWM Mode
//TCCR2->	COM21=0      COM20 = 0
#define	TIMER2_COM_NOPWM_OC2_PIN_DISCONNETED						0
//TCCR2->	COM21=0      COM20 = 1
#define	TIMER2_COM_NOPWM_OC2_PIN_TOGGLE								1
//TCCR2->	COM21=1      COM20 = 0
#define	TIMER2_COM_NOPWM_OC2_PIN_CLEAR								2
//TCCR2->	COM21=1      COM20 = 1
#define	TIMER2_COM_NOPWM_OC2_PIN_SET								3

// 2) Fast PWM Mode
//TCCR2->	COM21=0      COM20 = 0
#define	TIMER2_COM_FASTPWM_OC2_PIN_DISCONNETED						4
//TCCR2->	COM21=1      COM20 = 0  ||set OC2 at TOP
#define	TIMER2_COM_FASTPWM_OC2_PIN_CLEAR							5
//TCCR2->	COM21=1      COM20 = 1  ||clear OC2 at TOP
#define	TIMER2_COM_FASTPWM_OC2_PIN_SET								6

// 3)  Phase Correct PWM Mode
//TCCR2->	COM21=0      COM20 = 0
#define	TIMER2_COM_PHASECORRECTPWM_OC2_PIN_DISCONNETED				7
//TCCR2 -> 	COM21=1      COM20 = 0     ||Clear OC2 on compare match when up-counting. Set OC2 on compare  match when downcounting
#define	TIMER2_COM_PHASECORRECTPWM_OC2_PIN_CLEAR_COUNTUP			8
//TCCR2 ->	COM21=1      COM20 = 1	 ||Set OC2 on compare match when up-counting. Clear OC2 on compare match when downcounting
#define	TIMER2_COM_PHASECORRECTPWM_OC2_PIN_SET_COUNTUP				9

//________________________| Clock Select Bit Description|________________________
//TCCR2-> CS22=0     CS21=0     CS20=0
#define TIMER2_CS_STOP												0

//TCCR2-> CS22=0     CS21=0     CS20=1
#define TIMER2_CS_NOPRESCALLER										1

//TCCR2-> CS22=0     CS21=1     CS20=0
#define TIMER2_CS_PRESCALLER_8										2

//TCCR2-> CS22=0     CS21=1     CS20=1
#define TIMER2_CS_PRESCALLER_32	     								3

//TCCR2-> CS22=1     CS21=0     CS20=0
#define TIMER2_CS_PRESCALLER_64	     								4

//TCCR2-> CS22=1     CS21=0     CS20=1
#define TIMER2_CS_PRESCALLER_128									5

//TCCR2-> CS22=1     CS21=1     CS20=0
#define TIMER2_CS_PRESCALLER_256									6

//TCCR2-> CS22=1     CS21=1     CS20=1
#define TIMER2_CS_PRESCALLER_1024									7

//_______________________________________________________________________________________




#endif /* TIMER2_CONFIG_H_ */