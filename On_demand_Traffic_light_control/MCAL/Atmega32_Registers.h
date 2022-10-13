/*
 * Atmega32_Registers.h
 *
 * Created: 9/22/2022 10:30:44 PM
 *  Author: abano
 */ 


#ifndef ATMEGA32_REGISTERS_H_
#define ATMEGA32_REGISTERS_H_

/************************************
*			DIO_REGS				*
*************************************/

#define	PORTA		*((volatile u8*)0X3B)
#define DDRA		*((volatile u8*)0X3A)
#define PINA		*((volatile u8*)0X39)

#define	PORTB		*((volatile u8*)0X38)
#define DDRB		*((volatile u8*)0X37)		
#define PINB		*((volatile u8*)0X36)	

#define	PORTC		*((volatile u8*)0X35)
#define DDRC		*((volatile u8*)0X34)
#define PINC		*((volatile u8*)0X33)

#define	PORTD		*((volatile u8*)0X32)
#define DDRD		*((volatile u8*)0X31)
#define PIND		*((volatile u8*)0X30)

/************************************
*			TIMER_REGS				*
*************************************/

#define TIMSK		*(( volatile u8*)0X59)	
#define TIFR		*(( volatile u8*)0X58)
#define SFIOR		*(( volatile u8*)0X50)
//Timer0
#define TCCR0		*(( volatile u8*)0X53)
#define TCNT0		*(( volatile u8*)0X52)	
#define OCR0		*(( volatile u8*)0X5C)
//Timer1
#define	TCCR1A		*((volatile u8*)0X4F)
#define TCCR1B		*((volatile u8*)0X4E)			
#define TCNT1H		*((volatile u8*)0X4D)
#define TCNT1L		*((volatile u8*)0X4C)
#define	OCR1AH		*((volatile u8*)0X4B)
#define OCR1AL		*((volatile u8*)0X4A)
#define OCR1BH		*((volatile u8*)0X49)
#define OCR1BL		*((volatile u8*)0X48)
#define ICR1H		*((volatile u8*)0X47)
#define ICR1L		*((volatile u8*)0X46)
//Timer
#define TCCR2		*((volatile u8*)0X45)
#define TCNT2		*((volatile u8*)0X44)
#define OCR2		*((volatile u8*)0X43)
//watch dog
#define ASSR		*((volatile u8*)0X42)
#define WDTCR		*((volatile u8*)0X41)

/************************************
*			EXTI_INT				*
*************************************/
#define MCUCR				*(( volatile u8*)0X55)
#define MCUCSR				*(( volatile u8*)0X54)
#define GICR				*(( volatile u8*)0X5B)
#define GIFR				*(( volatile u8*)0X5A)




#define SREG		*(( volatile u8*)0X5F)

#endif /* ATMEGA32_REGISTERS_H_ */