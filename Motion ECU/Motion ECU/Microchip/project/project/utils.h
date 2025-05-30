/*
 * utils.h
 *
 * Created: 2/8/2024 7:03:22 PM
 *  Author: ahmed
 */ 


#ifndef UTILS_H_
#define UTILS_H_


#define TOG_BIT(reg, bit)  (reg ^= (1 << bit))
#define SET_BIT(reg,bit)   (reg|=(1<<bit))
#define CLR_BIT(reg,bit)   (reg&=~(1<<bit))
#define READ_BIT(reg,bit)   ((reg>>bit)&1)


#endif /* UTILS_H_ */