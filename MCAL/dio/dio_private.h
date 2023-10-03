


#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
//port A
#define  MDIO_PORTA	     *((volatile u8*)0x3B)
#define  MDIO_DDRA	     *((volatile u8*)0x3A)
#define  MDIO_PINA		 *((volatile u8*)0x39)
//port B
#define  MDIO_PORTB	     *((volatile u8*)0x38)
#define  MDIO_DDRB	     *((volatile u8*)0x37)
#define  MDIO_PINB		 *((volatile u8*)0x36)

//port C
#define  MDIO_PORTC	     *((volatile u8*)0x35)
#define  MDIO_DDRC	     *((volatile u8*)0x34)
#define  MDIO_PINC		 *((volatile u8*)0x33)
//port D
#define  MDIO_PORTD	     *((volatile u8*)0x32)
#define  MDIO_DDRD	     *((volatile u8*)0x31)
#define  MDIO_PIND		 *((volatile u8*)0x30)


#endif /* DIO_PRIVATE_H_ */