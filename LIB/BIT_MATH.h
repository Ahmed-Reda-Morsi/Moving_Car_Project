/*
 *  @Author: 
 */ 


#ifndef BITMATH_H
#define BITMATH_H

// functions macros
#define SET_BIT(VAR,BITNO) ((VAR) |= (1<<(BITNO)))// set 1
#define CLEAR_BIT(VAR,BITNO) ((VAR) &= ~(1<<(BITNO))) // set 0
#define TOGGLE_BIT(VAR,BITNO) ((VAR) ^= (1<<(BITNO)) )// toggle
#define GET_BIT(VAR,BITNO)  (((VAR)>>(BITNO))&0x01) // get  pin 


#endif