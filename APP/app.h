/*
 * app.h
 *
 *  Author: Ahmed Reda
 */ 


#ifndef APP_H_
#define APP_H_
#include "../MCAL/dio/dio_config.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define LED_PORT            PORTB
#define LED_LongSide		PIN7
#define LED_ShortSide		PIN6
#define LED_Stop			PIN5
#define LED_Rotate			PIN4

#define STARTBUTTON_PIN     PIN3
#define STARTBUTTON_PORT    PORTD
/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	CAR_ForwardOnLongSide,CAR_ForwardOnShortSide,CAR_Rotate_RightShortSide,CAR_Rotate_RightLongSide,
	CAR_STOP_BeforeLongSide,CAR_STOP_BeforeShortSide,CAR_STOP_AfterLongSide,CAR_STOP_AfterShortSide,CAR_SuddenlyStop
}EN_CarStatus_t;
/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void App_Start(void);
void App_Init(void);
void MOVE_CAR(void);
void suddelly_Stop(void);
#endif /* APP_H_ */