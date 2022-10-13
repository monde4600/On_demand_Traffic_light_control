/*
 * EXTI_privit.h
 *
 * Created: 9/30/2022 9:56:09 PM
 *  Author: abano
 */ 


#ifndef EXTI_PRIVIT_H_
#define EXTI_PRIVIT_H_

//GICR
#define INT1	7
#define INT0	6
#define INT2	5
//MCUCR
#define ISC11	3
#define ISC10	2
#define ISC01	1
#define ISC00	0
//MCUCSR
#define	ISC2	6 

#define ENABLE				1
#define DISABLE				0

#define ANY_LOGICAL			1
#define FALLING				2
#define RISSING				3

#endif /* EXTI_PRIVIT_H_ */