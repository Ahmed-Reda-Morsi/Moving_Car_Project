 

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "dio_interface.h"
#include "dio_config.h"
#include "dio_private.h"

/*
 * Description :
 * Setup the direction of the required pin input/output and return error status.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
EN_dioError_t MDIO_SetPinDirection (u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Dir)
{
    /*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	
	EN_dioError_t errorStatus = DIO_OK;
	
	if (Copy_u8Pin >= NUM_OF_PINS_PER_PORT || Copy_u8Port >= NUM_OF_PORTS)
    {
				errorStatus = DIO_NOT_OK;
    }
	else
	{
				/* Setup the pin direction as required */
		switch (Copy_u8Port)
		{
			case PORTA:
			switch (Copy_u8Dir)
			{
				case PIN_IN :
				  CLEAR_BIT(MDIO_DDRA,Copy_u8Pin);
				   break;
				case PIN_OUT:
				  SET_BIT(MDIO_DDRA,Copy_u8Pin);
				     break;
				default     : 
					errorStatus = DIO_NOT_OK;
					break;
			}
			break;
			
			case PORTB:
			switch (Copy_u8Dir)
			{
				case PIN_IN :  
					CLEAR_BIT(MDIO_DDRB,Copy_u8Pin); 
					break;
				case PIN_OUT:  
					SET_BIT(MDIO_DDRB,Copy_u8Pin);   
					break;
				default     : 
					errorStatus = DIO_NOT_OK;
					break;
			}
			break;

			case PORTC:
			switch (Copy_u8Dir)
			{
				case PIN_IN :  
					CLEAR_BIT(MDIO_DDRC,Copy_u8Pin); 
					break;
				case PIN_OUT:  
					SET_BIT(MDIO_DDRC,Copy_u8Pin);   
					break;
				default     : 
					errorStatus = DIO_NOT_OK;
					break;
			}
			break;

			case PORTD:
			switch (Copy_u8Dir)
			{
				case PIN_IN :  
					CLEAR_BIT(MDIO_DDRD,Copy_u8Pin); 
					break;
				case PIN_OUT:  
					SET_BIT(MDIO_DDRD,Copy_u8Pin);   
					break;
				default     : 
					errorStatus = DIO_NOT_OK;
					break;
			}
			break;

			default:
				errorStatus = DIO_NOT_OK;
				break;
		}
	}
	return errorStatus;
}
/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin and return error status.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
EN_dioError_t MDIO_SetPinValue     (u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Value)
{   
    /*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	EN_dioError_t errorStatus = DIO_OK;
	if (Copy_u8Pin >= NUM_OF_PINS_PER_PORT || Copy_u8Port >= NUM_OF_PORTS)
    {
						errorStatus = DIO_NOT_OK;
    } 
    else
    {
		switch (Copy_u8Port)
		{
			case PORTA:
			switch (Copy_u8Value)
			{
				case PIN_LOW :  
					CLEAR_BIT(MDIO_PORTA,Copy_u8Pin); 
					break;
				case PIN_HIGH:  
					SET_BIT(MDIO_PORTA,Copy_u8Pin);   
					break;
				default      : 
					errorStatus = DIO_NOT_OK;
					break;
			}
			break;
			
			case PORTB:
			switch (Copy_u8Value)
			{
				case PIN_LOW :  
					CLEAR_BIT(MDIO_PORTB,Copy_u8Pin); 
					break;
				case PIN_HIGH:  
					SET_BIT(MDIO_PORTB,Copy_u8Pin);   
					break;
				default      : 
					errorStatus = DIO_NOT_OK;
					break;
			}
			break;

			case PORTC:
			switch (Copy_u8Value)
			{
				case PIN_LOW :  
					CLEAR_BIT(MDIO_PORTC,Copy_u8Pin); 
					break;
				case PIN_HIGH:  
					SET_BIT(MDIO_PORTC,Copy_u8Pin);   
					break;
				default      : 
					errorStatus = DIO_NOT_OK;
					break;
			}
			break;

			case PORTD:
			switch (Copy_u8Value)
			{
				case PIN_LOW :  
					CLEAR_BIT(MDIO_PORTD,Copy_u8Pin); 
					break;
				case PIN_HIGH:  
					SET_BIT(MDIO_PORTD,Copy_u8Pin);   
					break;
				default      : 
					errorStatus = DIO_NOT_OK;
					break;
			}
			break;

			default:
				errorStatus = DIO_NOT_OK;
				break;
		}
    }
	return errorStatus;
	
}
/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
u8   MDIO_GetPinValue       (u8 Copy_u8Port,u8 Copy_u8Pin)
{
    u8 Local_u8Data = LOGIC_LOW;
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if((Copy_u8Port >= NUM_OF_PINS_PER_PORT) || (Copy_u8Pin >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
				/* Read the pin value as required */
		switch (Copy_u8Port)
		{
		case PORTA:
			Local_u8Data=GET_BIT(MDIO_PINA,Copy_u8Pin);
			break; 
    
		case PORTB:
			Local_u8Data=GET_BIT(MDIO_PINB,Copy_u8Pin);
			break; 

		case PORTC:
			Local_u8Data=GET_BIT(MDIO_PINC,Copy_u8Pin);
			break;

		case PORTD:
			Local_u8Data=GET_BIT(MDIO_PIND,Copy_u8Pin);
			break;

		default:
			break;
		}
	}
    return Local_u8Data;
} 

/*
 * Description :
 * Setup the direction of the required port all pins input/output and return error status.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
EN_dioError_t MDIO_SetPortDirection (u8 Copy_u8Port,u8 Copy_u8Dir)
{
    /*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	EN_dioError_t errorStatus = DIO_OK;
	if(Copy_u8Port >= NUM_OF_PORTS)
	{
		errorStatus = DIO_NOT_OK;
	}
	else
	{
				/* Setup the port direction as required */
		switch (Copy_u8Port)
		{
			case PORTA:  
				MDIO_DDRA = Copy_u8Dir;
				break;
			
			case PORTB:  
				MDIO_DDRB = Copy_u8Dir; 
				break;

			case PORTC:  
				MDIO_DDRC = Copy_u8Dir; 
				break;

			case PORTD:  
				MDIO_DDRD = Copy_u8Dir; 
				break;

			default:
				errorStatus = DIO_NOT_OK;
				break;
		}	
	}
	return errorStatus;
	
}
/*
 * Description :
 * Write the value on the required port and return error status.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
EN_dioError_t MDIO_SetPortValue (u8 Copy_u8Port,u8 Copy_u8Value)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	EN_dioError_t errorStatus = DIO_OK;
	if(Copy_u8Port >= NUM_OF_PORTS)
	{
		errorStatus = DIO_NOT_OK;
	}
	else
	{
				/* Write the port value as required */
		switch (Copy_u8Port)
		{
		case PORTA:   
			MDIO_PORTA = Copy_u8Value; 
			break;

		case PORTB:  
			MDIO_PORTB = Copy_u8Value; 
			break;

		case PORTC:  
			MDIO_PORTC = Copy_u8Value; 
			break;

		case PORTD:  
			MDIO_PORTD = Copy_u8Value; 
			break;

		default:
			errorStatus = DIO_NOT_OK;
			break;
		}
	}
	return errorStatus;
}
/*
 * Description :
 * Toggle The value of the pin and return error status.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the output is high, The function will toggle it to low.
 * If the output is low, The function will toggle it to high.
 */
EN_dioError_t MDIO_TogglePinValue (u8 Copy_u8Port,u8 Copy_u8Pin)
{
	EN_dioError_t errorStatus = DIO_OK;
	if((Copy_u8Port >= NUM_OF_PINS_PER_PORT) || (Copy_u8Pin >= NUM_OF_PORTS))
	{
		errorStatus = DIO_NOT_OK;
	}
	else
	{
		/* Toggle the Pin value as required */
		switch (Copy_u8Port)
		{
			case PORTA:
			TOGGLE_BIT(MDIO_PORTA,Copy_u8Pin);
			break;

			case PORTB:
			TOGGLE_BIT(MDIO_PORTB,Copy_u8Pin);
			break;

			case PORTC:
			TOGGLE_BIT(MDIO_PORTC,Copy_u8Pin);
			break;

			case PORTD:
			TOGGLE_BIT(MDIO_PORTD,Copy_u8Pin);
			break;

			default:
			errorStatus = DIO_NOT_OK;
			break;
		}
	}
	return errorStatus;
	
}
/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
u8 MDIO_GetPortValue (u8 Copy_u8Port)
{
    u8 Local_u8Data = LOGIC_LOW;
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(Copy_u8Port >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
				/* Read the port value as required */
		switch (Copy_u8Port)
		{
		case PORTA: 
			Local_u8Data = MDIO_PINA; 
			break; 
    
		case PORTB: 
			Local_u8Data = MDIO_PINB; 
			break; 

		case PORTC: 
			Local_u8Data = MDIO_PINC; 
			break; 

		case PORTD: 
			Local_u8Data = MDIO_PIND; 
			break; 
		default:
			break;
		}
	}
    return Local_u8Data;

}

/*
 * Description :
 * Setup the Pull-up Resistor and return error status.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
EN_dioError_t MDIO_SetPullupResistor (u8 Copy_u8Port,u8 Copy_u8Pin)
{
    EN_dioError_t errorStatus = DIO_OK;
	if((Copy_u8Port >= NUM_OF_PINS_PER_PORT) || (Copy_u8Pin >= NUM_OF_PORTS))
    {
	    errorStatus = DIO_NOT_OK;
    }
	else
	{
		switch (Copy_u8Port)
		{
		case PORTA: 
			if (((MDIO_DDRA>>Copy_u8Pin)&0x01)==0)
				{
					SET_BIT(MDIO_PORTA,Copy_u8Pin);
				}
			break;

		case PORTB:
			if (((MDIO_DDRB>>Copy_u8Pin)&0x01)==0)
				{
					SET_BIT(MDIO_PORTB,Copy_u8Pin);
				}
			break;
		case PORTC:
			if (((MDIO_DDRC>>Copy_u8Pin)&0x01)==0)
				{
					SET_BIT(MDIO_PORTC,Copy_u8Pin);
				}
			break;
		case PORTD:
			if (((MDIO_DDRD>>Copy_u8Pin)&0x01)==0)
				{
					SET_BIT(MDIO_PORTD,Copy_u8Pin);
				}
			break;
		default:
			errorStatus = DIO_NOT_OK;
			break;
		}
	}
	return errorStatus;
}
