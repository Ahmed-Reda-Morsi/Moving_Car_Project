


#ifndef TIMER2_PRIVATE_H_
#define TIMER2_PRIVATE_H_


#include "../../LIB/STD_TYPES.h"


//_________________|Timer/Counter2 Control Register|____________________
#define MTIMER2_TCCR2_REG 			*(( volatile u8*)0x45)

/*
 The FOC7 bit is only active when the WGM20 bit specifies a non-PWM mode. However,
for ensuring compatibility with future devices, this bit must be set to zero when TCCR2 is
written when operating in PWM mode
 */
// Bit 7  FOC7: Force Output Compare
#define TCCR2_FOC7_BIT							7

/*
  These bits control the counting sequence of the counter, the source for the maximum
(TOP) counter value, and what type of Waveform Generation to be used. Modes of
operation supported by the Timer/Counter unit are: Normal mode,
Clear Timer on Compare Match (CTC) mode, and two types of Pulse Width Modulation (PWM) modes.
  */
//Bit 6, 3  WGM21:0: Waveform Generation Mode(Timer/Counter Mode of Operation)
#define TCCR2_WGM20_BIT							6
#define TCCR2_WGM21_BIT							3

/*
 These bits control the Output Compare pin (OC2) behavior
 */
//Bit 5:4  COM21:0: Compare Match Output Mode
#define TCCR2_COM21_BIT							5
#define TCCR2_COM20_BIT							4

/*
 The three Clock Select bits
  select the clock source to be used by the Timer/Counter.
 */
//Bit 2:0  CS22:0: Clock Select
#define TCCR2_CS22_BIT							2
#define TCCR2_CS21_BIT							1
#define TCCR2_CS20_BIT							0

//_________________________|Timer/Counter2 Register|_____________________
/*
 The Timer/Counter Register gives direct access, both for read and write operations, to
the Timer/Counter unit 8-bit counter. Writing to the TCNT2 Register blocks (removes)
the compare match on the following timer clock. Modifying the counter (TCNT2) while
the counter is running, introduces a risk of missing a compare match between TCNT2
and the OCR2 Register
 */
#define MTIMER2_TCNT2_REG							*(( volatile u8*)0x44)

//_________________________|Timer/Counter2 Output Compare Register|_____________________
/*
The Output Compare Register contains an 8-bit value that is continuously compared
with the counter value (TCNT2). A match can be used to generate an output compare
interrupt, or to generate a waveform output on the OC2 pin.
 */
#define MTIMER2_OCR2_REG							*(( volatile u8*)0x43)

//_________________________| Asynchronous Status Register – ASSR For Timer2 |____________
//Asynchronous Operation of the Timer/Counter
#define MTIMER2_ASSR_REG							*(( volatile u8*)0x42)

/*When AS2 is written to zero, Timer/Counter 2 is clocked from the I/O clock, clkI/O. When
AS2 is written to one,Timer/Counter2 is clocked from a Crystal Oscillator connected to
the Timer Oscillator 1 (TOSC1) pin.*/
// Bit 3 – AS2: Asynchronous Timer/Counter2
#define ASSR_AS2_BIT									3

/*When Timer/Counter2 operates asynchronously and TCNT2 is written, this bit becomes
set. When TCNT2 has been updated from the temporary storage register, this bit is
cleared by hardware. A logical zero in this bit indicates that TCNT2 is ready to be
updated with a new value*/
//Bit 2 – TCN2UB: Timer/Counter2 Update Busy
#define ASSR_TCN2UB2_BIT								2


/*When Timer/Counter2 operates asynchronously and OCR2 is written, this bit becomes
set. When OCR2 has been updated from the temporary storage register, this bit is
cleared by hardware. A logical zero in this bit indicates that OCR2 is ready to be
updated with a new value*/
//Bit 1 – OCR2UB: Output Compare Register2 Update Busy
#define ASSR_OCR2UB1_BIT								1


/*When Timer/Counter2 operates asynchronously and TCCR2 is written, this bit becomes
set. When TCCR2 has been updated from the temporary storage register, this bit is
cleared by hardware. A logical zero in this bit indicates that TCCR2 is ready to be
updated with a new value.
If a write is performed to any of the three Timer/Counter2 Registers while its update
busy flag is set, the updated value might get corrupted and cause an unintentional interrupt to occur.
The mechanisms for reading TCNT2, OCR2, and TCCR2 are different. When reading
TCNT2, the actual timer value is read. When reading OCR2 or TCCR2, the value in the
temporary storage register is read.*/
// Bit 0 – TCR2UB: Timer/Counter Control Register2 Update Busy
#define ASSR_OCR2UB0_BIT								0

//_________________________|Timer/Counter Interrupt Mask Register|_______________________
/*
The Output Compare Register contains an 8-bit value that is continuously compared
with the counter value (TCNT2). A match can be used to generate an output compare
interrupt, or to generate a waveform output on the OC2 pin.
 */
#define MTIMER_TIMSK_REG							*(( volatile u8*)0x59)

/*
 When the TOIE2 bit is written to one, and the I-bit in the Status Register is set (one), the
Timer/Counter0 Overflow interrupt is enabled
*/
//Bit 6  TOIE2: Timer/Counter2 Overflow Interrupt Enable
#define TIMSK_TOIE2_BIT													6

/*
 When the OCIE2 bit is written to one, and the I-bit in the Status Register is set (one), the
Timer/Counter2 Compare Match interrupt is enabled
*/
//Bit 7  OCIE2: Timer/Counter2 Output Compare Match Interrupt Enable
#define TIMSK_OCIE2_BIT													7


//________________________|Timer/Counter Interrupt Flag Register |_______________


#define MTIMER_TIFR_REG											*(( volatile u8*)0x58)


/*
 The OCF2 bit is set (one) when a compare match occurs between the Timer/Counter2
and the data in OCR2  Output Compare Register2. OCF2 is cleared by hardware when
executing the corresponding interrupt handling vector. Alternatively, OCF2 is cleared by
writing a logic one to the flag. When the I-bit in SREG, OCIE2 (Timer/Counter2 Compare Match Interrupt Enable), and OCF2 are set (one), the Timer/Counter0 Compare
Match Interrupt is executed
 */
// Bit 6  TOV2: Timer/Counter2 Overflow Flag
#define TIMER2_TOV2_BIT											6

/*
 The bit TOV2 is set (one) when an overflow occurs in Timer/Counter0. TOV2 is cleared
by hardware when executing the corresponding interrupt handling vector. Alternatively,
TOV0 is cleared by writing a logic one to the flag. When the SREG I-bit, TOIE2
(Timer/Counter2 Overflow Interrupt Enable), and TOV2 are set (one), the
Timer/Counter2 Overflow interrupt is executed. In phase correct PWM mode, this bit is
set when Timer/Counter2 changes counting direction at $00.
 */
//Bit 7  OCF2: Output Compare Flag 2
#define TIMER2_OCF2_BIT											7

//______________________________________________________________

// OC2 Data Direction Register for set as output
#define OC2_DDR     				*((volatile u8*)0x31)
#define OC2_PIN						7

#define TIMER2_OverFlowValue		255
#define TIMER2_MaxDutyCycle			100



#endif /* TIMER2_PRIVATE_H_ */