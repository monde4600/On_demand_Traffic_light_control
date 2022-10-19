/*
 * APP.h
 *
 * Created: 10/7/2022 6:33:00 PM
 *  Author: abano
 */ 


#ifndef APP_H_
#define APP_H_

#define CARS_GREEN			DIO_GroupA,DIO_PIN_0
#define CARS_YELLOW			DIO_GroupA,DIO_PIN_1
#define CARS_RED			DIO_GroupA,DIO_PIN_2

#define PEDESTRAINS_GREEN	DIO_GroupB,DIO_PIN_0
#define PEDESTRAINS_YELLOW	DIO_GroupB,DIO_PIN_1
#define PEDESTRAINS_RED		DIO_GroupB,DIO_PIN_2				

#define PEDESTRAINS_BUTTON	DIO_GroupD,DIO_PIN_2

#define PEDESTRAINS_INT_PIN	EXTI_INT0

typedef enum{CARS_STOP,CARS_MOVE,CARS_STEADY}STATES;

#define ENABLED			1
#define DISABLED			0

#define ONE_SECOND_COUNTS		62						//1 +	F_CPU/1024/256 //61.
#define TCNT_PRELOAD			(u8)247						//256(1-	(F_CPU/1024/256).f-(F_CPU/1024/256).l)

#define TCNT0		*(( volatile u8*)0X52)	

void APP_vidInit(void);
void APP_vidStart(void);


#endif /* APP_H_ */