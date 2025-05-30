/*
* StdTypes.h
*
* Created: 12/7/2023 5:57:53 AM
*  Author: ahmed
*/


#ifndef STDTYPES_H_
#define STDTYPES_H_

typedef unsigned char u8;
typedef signed char s8;
typedef char c8;
typedef unsigned int u16;
typedef signed int s16;
typedef unsigned long u32;
typedef signed long s32;
#define NULLPTR ((void*)0)
typedef enum{
	FALSE,
	TRUE
}bool_t;
typedef enum{
	ok,
	NULL_PTR,
	NOT_OK,
	OUT_OF_RANGE
}error_t;

#define MAX_U8 ((u8)255)
#define MIN_U8 ((u8)0)

#define MAX_S8 ((s8)127)
#define MIN_S8 ((s8)-128)
#define ZERO_S8 ((s8)0)





#endif /* STDTYPES_H_ */