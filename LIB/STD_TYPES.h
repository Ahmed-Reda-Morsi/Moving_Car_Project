#ifndef STD_TYPES_H
#define STD_TYPES_H


// 1 byte unsigned char
typedef unsigned char       u8;
// 1 byte signed char
typedef signed   char       s8;
// 2 byte unsigned int
typedef unsigned short int  u16;
// 2 byte signed int
typedef signed   short int  s16;
// 4 byte unsigned long int
typedef unsigned long int   u32;
// 4 byte signed long int
typedef signed   long int   s32;
// 4 byte float
typedef float               f32;
// 8 byte  double
typedef double              f64;

#define NULL 					0

#define NULL_PTR				((void*)0)
#endif
//.................................
/* bluid test cases to ensure the reserved positions 
   in memory is right choosen or not */
