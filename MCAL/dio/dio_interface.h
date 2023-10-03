/*
 * dio_interface.h
 *
 * Created: 10/3/2023 11:42:42 AM
 *  Author: awahba
 */ 

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include "../../LIB/STD_TYPES.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3

#define PIN0  0
#define PIN1  1
#define PIN2  2
#define PIN3  3
#define PIN4  4
#define PIN5  5
#define PIN6  6
#define PIN7  7

#define PIN_OUT 1
#define PIN_IN  0
#define PIN_HIGH 1
#define PIN_LOW  0

#define PORT_OUT 0xff
#define PORT_IN  0x00

#define NUM_OF_PORTS           4
#define NUM_OF_PINS_PER_PORT   8

#define LOGIC_LOW	0
#define LOGIC_HIGH	1

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	DIO_OK,DIO_NOT_OK
}EN_dioError_t;
/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * Description :
 * Setup the direction of the required pin input/output and return error status.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
EN_dioError_t MDIO_SetPinDirection (u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Dir);


/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin and return error status.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
EN_dioError_t MDIO_SetPinValue (u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Value);

/*
 * Description :
 * Toggle The value of the pin and return error status.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the output is high, The function will toggle it to low.
 * If the output is low, The function will toggle it to high.
 */
EN_dioError_t MDIO_TogglePinValue (u8 Copy_u8Port,u8 Copy_u8Pin);


/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
u8   MDIO_u8GetPinValue (u8 Copy_u8Port,u8 Copy_u8Pin4); 


/*
 * Description :
 * Setup the direction of the required port all pins input/output and return error status.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
EN_dioError_t MDIO_SetPortDirection (u8 Copy_u8Port,u8 Copy_u8Dir);


/*
 * Description :
 * Write the value on the required port and return error status.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
EN_dioError_t MDIO_SetPortValue (u8 Copy_u8Port,u8 Copy_u8Value);


/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
u8 MDIO_GetPortValue (u8 Copy_u8Port);


/*
 * Description :
 * Setup the Pull-up Resistor and return error status.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
EN_dioError_t MDIO_SetPullupResistor (u8 Copy_u8Port,u8 Copy_u8Pin);


#endif /* DIO_INTERFACE_H_ */