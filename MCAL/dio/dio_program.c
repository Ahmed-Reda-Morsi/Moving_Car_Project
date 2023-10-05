 

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
EN_dioError_t MDIO_SetPinDirection (u8 u8_arg_portNum,u8 u8_arg_pinNum,u8 u8_arg_pinDir)
{
    /*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	
	EN_dioError_t en_Local_errorStatus = DIO_OK;
	
	if (u8_arg_pinNum >= NUM_OF_PINS_PER_PORT || u8_arg_portNum >= NUM_OF_PORTS)
    {
				en_Local_errorStatus = DIO_NOT_OK;
    }
	else
	{
				/* Setup the pin direction as required */
		switch (u8_arg_portNum)
		{
			case PORTA:
			switch (u8_arg_pinDir)
			{
				case PIN_IN :
				  CLEAR_BIT(MDIO_DDRA,u8_arg_pinNum);
				   break;
				case PIN_OUT:
				  SET_BIT(MDIO_DDRA,u8_arg_pinNum);
				     break;
				default     : 
					en_Local_errorStatus = DIO_NOT_OK;
					break;
			}
			break;
			
			case PORTB:
			switch (u8_arg_pinDir)
			{
				case PIN_IN :  
					CLEAR_BIT(MDIO_DDRB,u8_arg_pinNum); 
					break;
				case PIN_OUT:  
					SET_BIT(MDIO_DDRB,u8_arg_pinNum);   
					break;
				default     : 
					en_Local_errorStatus = DIO_NOT_OK;
					break;
			}
			break;

			case PORTC:
			switch (u8_arg_pinDir)
			{
				case PIN_IN :  
					CLEAR_BIT(MDIO_DDRC,u8_arg_pinNum); 
					break;
				case PIN_OUT:  
					SET_BIT(MDIO_DDRC,u8_arg_pinNum);   
					break;
				default     : 
					en_Local_errorStatus = DIO_NOT_OK;
					break;
			}
			break;

			case PORTD:
			switch (u8_arg_pinDir)
			{
				case PIN_IN :  
					CLEAR_BIT(MDIO_DDRD,u8_arg_pinNum); 
					break;
				case PIN_OUT:  
					SET_BIT(MDIO_DDRD,u8_arg_pinNum);   
					break;
				default     : 
					en_Local_errorStatus = DIO_NOT_OK;
					break;
			}
			break;

			default:
				en_Local_errorStatus = DIO_NOT_OK;
				break;
		}
	}
	return en_Local_errorStatus;
}
/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin and return error status.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
EN_dioError_t MDIO_SetPinValue     (u8 u8_arg_portNum,u8 u8_arg_pinNum,u8 u8_arg_value)
{   
    /*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	EN_dioError_t en_Local_errorStatus = DIO_OK;
	if (u8_arg_pinNum >= NUM_OF_PINS_PER_PORT || u8_arg_portNum >= NUM_OF_PORTS)
    {
						en_Local_errorStatus = DIO_NOT_OK;
    } 
    else
    {
		switch (u8_arg_portNum)
		{
			case PORTA:
			switch (u8_arg_value)
			{
				case PIN_LOW :  
					CLEAR_BIT(MDIO_PORTA,u8_arg_pinNum); 
					break;
				case PIN_HIGH:  
					SET_BIT(MDIO_PORTA,u8_arg_pinNum);   
					break;
				default      : 
					en_Local_errorStatus = DIO_NOT_OK;
					break;
			}
			break;
			
			case PORTB:
			switch (u8_arg_value)
			{
				case PIN_LOW :  
					CLEAR_BIT(MDIO_PORTB,u8_arg_pinNum); 
					break;
				case PIN_HIGH:  
					SET_BIT(MDIO_PORTB,u8_arg_pinNum);   
					break;
				default      : 
					en_Local_errorStatus = DIO_NOT_OK;
					break;
			}
			break;

			case PORTC:
			switch (u8_arg_value)
			{
				case PIN_LOW :  
					CLEAR_BIT(MDIO_PORTC,u8_arg_pinNum); 
					break;
				case PIN_HIGH:  
					SET_BIT(MDIO_PORTC,u8_arg_pinNum);   
					break;
				default      : 
					en_Local_errorStatus = DIO_NOT_OK;
					break;
			}
			break;

			case PORTD:
			switch (u8_arg_value)
			{
				case PIN_LOW :  
					CLEAR_BIT(MDIO_PORTD,u8_arg_pinNum); 
					break;
				case PIN_HIGH:  
					SET_BIT(MDIO_PORTD,u8_arg_pinNum);   
					break;
				default      : 
					en_Local_errorStatus = DIO_NOT_OK;
					break;
			}
			break;

			default:
				en_Local_errorStatus = DIO_NOT_OK;
				break;
		}
    }
	return en_Local_errorStatus;
	
}
/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
u8   MDIO_GetPinValue       (u8 u8_arg_portNum,u8 u8_arg_pinNum)
{
    u8 u8_Local_value = LOGIC_LOW;
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if((u8_arg_pinNum >= NUM_OF_PINS_PER_PORT) || (u8_arg_portNum >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
				/* Read the pin value as required */
		switch (u8_arg_portNum)
		{
		case PORTA:
			u8_Local_value=GET_BIT(MDIO_PINA,u8_arg_pinNum);
			break; 
    
		case PORTB:
			u8_Local_value=GET_BIT(MDIO_PINB,u8_arg_pinNum);
			break; 

		case PORTC:
			u8_Local_value=GET_BIT(MDIO_PINC,u8_arg_pinNum);
			break;

		case PORTD:
			u8_Local_value=GET_BIT(MDIO_PIND,u8_arg_pinNum);
			break;

		default:
			break;
		}
	}
    return u8_Local_value;
} 

/*
 * Description :
 * Setup the direction of the required port all pins input/output and return error status.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
EN_dioError_t MDIO_SetPortDirection (u8 u8_arg_portNum,u8 u8_arg_portDir)
{
    /*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	EN_dioError_t en_Local_errorStatus = DIO_OK;
	if(u8_arg_portNum >= NUM_OF_PORTS)
	{
		en_Local_errorStatus = DIO_NOT_OK;
	}
	else
	{
				/* Setup the port direction as required */
		switch (u8_arg_portNum)
		{
			case PORTA:  
				MDIO_DDRA = u8_arg_portDir;
				break;
			
			case PORTB:  
				MDIO_DDRB = u8_arg_portDir; 
				break;

			case PORTC:  
				MDIO_DDRC = u8_arg_portDir; 
				break;

			case PORTD:  
				MDIO_DDRD = u8_arg_portDir; 
				break;

			default:
				en_Local_errorStatus = DIO_NOT_OK;
				break;
		}	
	}
	return en_Local_errorStatus;
	
}
/*
 * Description :
 * Write the value on the required port and return error status.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
EN_dioError_t MDIO_SetPortValue (u8 u8_arg_portNum,u8 u8_arg_value)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	EN_dioError_t en_Local_errorStatus = DIO_OK;
	if(u8_arg_portNum >= NUM_OF_PORTS)
	{
		en_Local_errorStatus = DIO_NOT_OK;
	}
	else
	{
				/* Write the port value as required */
		switch (u8_arg_portNum)
		{
		case PORTA:   
			MDIO_PORTA = u8_arg_value; 
			break;

		case PORTB:  
			MDIO_PORTB = u8_arg_value; 
			break;

		case PORTC:  
			MDIO_PORTC = u8_arg_value; 
			break;

		case PORTD:  
			MDIO_PORTD = u8_arg_value; 
			break;

		default:
			en_Local_errorStatus = DIO_NOT_OK;
			break;
		}
	}
	return en_Local_errorStatus;
}
/*
 * Description :
 * Toggle The value of the pin and return error status.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the output is high, The function will toggle it to low.
 * If the output is low, The function will toggle it to high.
 */
EN_dioError_t MDIO_TogglePinValue (u8 u8_arg_portNum,u8 u8_arg_pinNum)
{
	EN_dioError_t en_Local_errorStatus = DIO_OK;
	if((u8_arg_pinNum >= NUM_OF_PINS_PER_PORT) || (u8_arg_portNum >= NUM_OF_PORTS))
	{
		en_Local_errorStatus = DIO_NOT_OK;
	}
	else
	{
		/* Toggle the Pin value as required */
		switch (u8_arg_portNum)
		{
			case PORTA:
			TOGGLE_BIT(MDIO_PORTA,u8_arg_pinNum);
			break;

			case PORTB:
			TOGGLE_BIT(MDIO_PORTB,u8_arg_pinNum);
			break;

			case PORTC:
			TOGGLE_BIT(MDIO_PORTC,u8_arg_pinNum);
			break;

			case PORTD:
			TOGGLE_BIT(MDIO_PORTD,u8_arg_pinNum);
			break;

			default:
			en_Local_errorStatus = DIO_NOT_OK;
			break;
		}
	}
	return en_Local_errorStatus;
	
}
/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
u8 MDIO_GetPortValue (u8 u8_arg_portNum)
{
    u8 Local_u8Data = LOGIC_LOW;
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(u8_arg_portNum >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
				/* Read the port value as required */
		switch (u8_arg_portNum)
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
EN_dioError_t MDIO_SetPullupResistor (u8 u8_arg_portNum,u8 u8_arg_pinNum)
{
    EN_dioError_t en_Local_errorStatus = DIO_OK;
	if((u8_arg_pinNum >= NUM_OF_PINS_PER_PORT) || (u8_arg_portNum >= NUM_OF_PORTS))
    {
	    en_Local_errorStatus = DIO_NOT_OK;
    }
	else
	{
		switch (u8_arg_portNum)
		{
		case PORTA: 
			if (((MDIO_DDRA>>u8_arg_pinNum)&0x01)==0)
				{
					SET_BIT(MDIO_PORTA,u8_arg_pinNum);
				}
			break;

		case PORTB:
			if (((MDIO_DDRB>>u8_arg_pinNum)&0x01)==0)
				{
					SET_BIT(MDIO_PORTB,u8_arg_pinNum);
				}
			break;
		case PORTC:
			if (((MDIO_DDRC>>u8_arg_pinNum)&0x01)==0)
				{
					SET_BIT(MDIO_PORTC,u8_Local_pinNum);
				}
			break;
		case PORTD:
			if (((MDIO_DDRD>>u8_arg_pinNum)&0x01)==0)
				{
					SET_BIT(MDIO_PORTD,u8_arg_pinNum);
				}
			break;
		default:
			en_Local_errorStatus = DIO_NOT_OK;
			break;
		}
	}
	return en_Local_errorStatus;
}
