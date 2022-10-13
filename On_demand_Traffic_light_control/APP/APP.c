/*
 * APP.c
 *
 * Created: 10/7/2022 6:42:14 PM
 *  Author: abano
 */ 
#include "../LIBRARY/stdTypes.h"
#include "../LIBRARY/errorState.h"

#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/EXTI/EXTI_int.h"
#include "../MCAL/TIMER0/TIMER0_int.h"
#include "APP.h"

static u16 APP_u16TimeCounter;
static STATES APP_enuTraficStates;
static u8 ToggleFlag =1;
static u8 Five_secondFLAG=5;
static STATES Prevus_TraficState;

static void TIMER_ISRfun(void* x)
{
	
	APP_u16TimeCounter--;
	if(!APP_u16TimeCounter)
	{
		TCNT0 = TCNT_PRELOAD;
		Five_secondFLAG--;
		if(!Five_secondFLAG)
		{
			Five_secondFLAG = 5;
			if(CARS_STOP == APP_enuTraficStates || CARS_MOVE == APP_enuTraficStates)
			{
				Prevus_TraficState = APP_enuTraficStates;
				APP_enuTraficStates = CARS_STEADY; 
			}
			else if(Prevus_TraficState == CARS_MOVE)	APP_enuTraficStates = CARS_STOP;	
			else										APP_enuTraficStates = CARS_MOVE;
		}
		
		ToggleFlag |=1;
		APP_u16TimeCounter = ONE_SECOND_COUNTS;
		TCNT0 = TCNT_PRELOAD;
	}
}

static u8 INT0State = ENABLED;
static void INT0_ISRFun(void*x)
{
	EXTI_enuDisableIntrrubt(EXTI_INT0);
	INT0State = DISABLED;
	if(CARS_STEADY == APP_enuTraficStates || CARS_MOVE == APP_enuTraficStates)
	{
		
		Prevus_TraficState = CARS_MOVE;
		if( CARS_MOVE == APP_enuTraficStates)
		{
			Five_secondFLAG = 5;
			APP_u16TimeCounter = ONE_SECOND_COUNTS;
			TCNT0 = TCNT_PRELOAD;
		}
		APP_enuTraficStates = CARS_STEADY;
	}	
	else
	{
		Five_secondFLAG = 5;
		APP_u16TimeCounter = ONE_SECOND_COUNTS;
		TCNT0 = TCNT_PRELOAD;
	}
}

void APP_vidInit(void)
{
	DIO_enuSetPinDirection(PEDESTRAINS_BUTTON,DIO_INPUT);
	DIO_enuSetPinValue(PEDESTRAINS_BUTTON,DIO_HIGH);
	
	DIO_enuSetPinDirection(CARS_GREEN,DIO_OUTPUT);	
	DIO_enuSetPinDirection(CARS_YELLOW,DIO_OUTPUT);
	DIO_enuSetPinDirection(CARS_RED,DIO_OUTPUT);
	
	DIO_enuSetPinValue(CARS_GREEN,DIO_LOW);
	DIO_enuSetPinValue(CARS_YELLOW,DIO_LOW);
	DIO_enuSetPinValue(CARS_RED,DIO_LOW);
	
	DIO_enuSetPinDirection(PEDESTRAINS_GREEN,DIO_OUTPUT);
	DIO_enuSetPinDirection(PEDESTRAINS_YELLOW,DIO_OUTPUT);
	DIO_enuSetPinDirection(PEDESTRAINS_RED,DIO_OUTPUT);
	
	DIO_enuSetPinValue(PEDESTRAINS_GREEN,DIO_LOW);
	DIO_enuSetPinValue(PEDESTRAINS_YELLOW,DIO_LOW);
	DIO_enuSetPinValue(PEDESTRAINS_RED,DIO_LOW);
	
	APP_enuTraficStates = CARS_MOVE;
	APP_u16TimeCounter = ONE_SECOND_COUNTS;
	TIMER0_enuInit();
	EXTI_enuInit();
	EXTI_enuCallBackFun(INT0_ISRFun,NULL,EXTI_INT0);
	TIMER0_enuCallBackFun(TIMER_ISRfun,NULL,TIMER0_OVFSInterr);
	TCNT0 = TCNT_PRELOAD;
	GLOBALINTERRUPT_EN();
}

void APP_vidStart(void)
{
	if(CARS_MOVE==APP_enuTraficStates)	
	{
		DIO_enuSetPinValue(CARS_GREEN,DIO_HIGH);
		DIO_enuSetPinValue(CARS_RED,DIO_LOW);
		DIO_enuSetPinValue(CARS_YELLOW,DIO_LOW);
		
		DIO_enuSetPinValue(PEDESTRAINS_GREEN,DIO_LOW);
		DIO_enuSetPinValue(PEDESTRAINS_YELLOW,DIO_LOW);
		DIO_enuSetPinValue(PEDESTRAINS_RED,DIO_HIGH);
		while(CARS_MOVE == APP_enuTraficStates);
	}
	else if(CARS_STEADY == APP_enuTraficStates)
	{
		DIO_enuSetPinValue(CARS_GREEN,DIO_LOW);
		DIO_enuSetPinValue(CARS_RED,DIO_LOW);
		//DIO_enuSetPinValue(CARS_YELLOW,DIO_LOW);
		
		DIO_enuSetPinValue(PEDESTRAINS_GREEN,DIO_LOW);
		//DIO_enuSetPinValue(PEDESTRAINS_YELLOW,DIO_LOW);
		DIO_enuSetPinValue(PEDESTRAINS_RED,DIO_LOW);
		while(CARS_STEADY == APP_enuTraficStates)
		{
			if(ToggleFlag)
			{
				ToggleFlag &= 0;
				DIO_enuTogglePin(PEDESTRAINS_YELLOW);
				DIO_enuTogglePin(CARS_YELLOW);	
			}
			
		}
	}
	else
	{
		DIO_enuSetPinValue(CARS_GREEN,DIO_LOW);
		DIO_enuSetPinValue(CARS_RED,DIO_HIGH);
		DIO_enuSetPinValue(CARS_YELLOW,DIO_LOW);
		
		DIO_enuSetPinValue(PEDESTRAINS_GREEN,DIO_HIGH);
		DIO_enuSetPinValue(PEDESTRAINS_YELLOW,DIO_LOW);
		DIO_enuSetPinValue(PEDESTRAINS_RED,DIO_LOW);
		while(CARS_STOP == APP_enuTraficStates)
		{
			if(Five_secondFLAG<3 && INT0State == DISABLED)
			{
				EXTI_enuEnableInterrupt(EXTI_INT0);
				INT0State = ENABLED;
			}
			
		}	
	}
	
}