#ifndef  TIMER_PRV_H
#define TIMER_PRV_H
#include "../../LIB/STD_TYPES.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
//_________________|Timer/Counter0 Control Register|____________________
#define MTIMER0_TCCR0_REG 			*(( volatile u8*)0x53)

/*
 The FOC0 bit is only active when the WGM00 bit specifies a non-PWM mode. However,
for ensuring compatibility with future devices, this bit must be set to zero when TCCR0 is
written when operating in PWM mode
 */
// Bit 7 � FOC0: Force Output Compare
#define TCCR0_FOC0_BIT							7

/*
  These bits control the counting sequence of the counter, the source for the maximum
(TOP) counter value, and what type of Waveform Generation to be used. Modes of
operation supported by the Timer/Counter unit are: Normal mode,
Clear Timer on Compare Match (CTC) mode, and two types of Pulse Width Modulation (PWM) modes.
  */
//Bit 6, 3  WGM01:0: Waveform Generation Mode(Timer/Counter Mode of Operation)
#define TCCR0_WGM00_BIT						6
#define TCCR0_WGM01_BIT						3

/*
 These bits control the Output Compare pin (OC0) behavior
 */
//Bit 5:4  COM01:0: Compare Match Output Mode
#define TCCR0_COM01_BIT						5
#define TCCR0_COM00_BIT						4

/*
 The three Clock Select bits
  select the clock source to be used by the Timer/Counter.
 */
//Bit 2:0  CS02:0: Clock Select
#define TCCR0_CS02_BIT							2
#define TCCR0_CS01_BIT							1
#define TCCR0_CS00_BIT							0

//_________________________|Timer/Counter0 Register|_____________________
/*
 The Timer/Counter Register gives direct access, both for read and write operations, to
the Timer/Counter unit 8-bit counter. Writing to the TCNT0 Register blocks (removes)
the compare match on the following timer clock. Modifying the counter (TCNT0) while
the counter is running, introduces a risk of missing a compare match between TCNT0
and the OCR0 Register
 */
#define MTIMER0_TCNT0_REG							*(( volatile u8*)0x52)

//_________________________|Timer/Counter0 Output Compare Register|_____________________
/*
The Output Compare Register contains an 8-bit value that is continuously compared
with the counter value (TCNT0). A match can be used to generate an output compare
interrupt, or to generate a waveform output on the OC0 pin.
 */
#define MTIMER0_OCR0_REG							*(( volatile u8*)0x5C)


//_________________________|Timer/Counter Interrupt Mask Register|_____________________
/*
The Output Compare Register contains an 8-bit value that is continuously compared
with the counter value (TCNT0). A match can be used to generate an output compare
interrupt, or to generate a waveform output on the OC0 pin.
 */
#define MTIMER_TIMSK_REG							*(( volatile u8*)0x59)

/*
 When the TOIE0 bit is written to one, and the I-bit in the Status Register is set (one), the
Timer/Counter0 Overflow interrupt is enabled
*/
//Bit 0  TOIE0: Timer/Counter0 Overflow Interrupt Enable
#define TIMSK_TOIE0_BIT													0

/*
 When the OCIE0 bit is written to one, and the I-bit in the Status Register is set (one), the
Timer/Counter0 Compare Match interrupt is enabled
*/
//Bit 1  OCIE0: Timer/Counter0 Output Compare Match Interrupt Enable
#define TIMSK_OCIE0_BIT													1


//________________________|Timer/Counter Interrupt Flag Register |_______________


#define MTIMER_TIFR_REG											*(( volatile u8*)0x58)


/*
 The OCF0 bit is set (one) when a compare match occurs between the Timer/Counter0
and the data in OCR0  Output Compare Register0. OCF0 is cleared by hardware when
executing the corresponding interrupt handling vector. Alternatively, OCF0 is cleared by
writing a logic one to the flag. When the I-bit in SREG, OCIE0 (Timer/Counter0 Compare Match Interrupt Enable), and OCF0 are set (one), the Timer/Counter0 Compare
Match Interrupt is executed
 */
// Bit 0  TOV0: Timer/Counter0 Overflow Flag
#define TIMER0_TOV0_BIT											0

/*
 The bit TOV0 is set (one) when an overflow occurs in Timer/Counter0. TOV0 is cleared
by hardware when executing the corresponding interrupt handling vector. Alternatively,
TOV0 is cleared by writing a logic one to the flag. When the SREG I-bit, TOIE0
(Timer/Counter0 Overflow Interrupt Enable), and TOV0 are set (one), the
Timer/Counter0 Overflow interrupt is executed. In phase correct PWM mode, this bit is
set when Timer/Counter0 changes counting direction at $00.
 */
//Bit 1  OCF0: Output Compare Flag 0
#define TIMER0_OCF0_BIT											1

//______________________________________________________________

// OC0 Data Direction Register for set as output
#define OC0_DDR     *((volatile u8*)0x37)
# define OC0_PIN		3

#define TIMER0_OverFlowValue		256
#define TIMER0_MaxDutyCycle			100

#endif
