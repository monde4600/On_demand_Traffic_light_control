/*
 * EXTI_prog.c
 *
 * Created: 9/30/2022 9:57:39 PM
 *  Author: abano
 */ 
#include "../../LIBRARY/errorState.h"
#include "../../LIBRARY/stdTypes.h"
#include "../Atmega32_Registers.h"
#include "EXTI_config.h"
#include "EXTI_priv.h"

static void (*EXTI_ApfunISRfun[3])(void*);
static void  *EXTI_ApvidISRParameter[3];

ES_t EXTI_enuInit(void)
{
	ES_t Local_enuErrorState=ES_NOK;
#if	EXTI_INT0_STATE == ENABLE
	GICR |= (1<<INT0);	
#elif EXTI_INT0_STATE == DISABLE
	GICR &= ~(1<<INT0);
#else 
	return Local_enuErrorState;
#endif

#if	EXTI_INT1_STATE == ENABLE
	GICR |= (1<<INT1);
#elif EXTI_INT1_STATE == DISABLE
	GICR &= ~(1<<INT1);
#else
	return Local_enuErrorState;
#endif

#if	EXTI_INT2_STATE == ENABLE
	GICR |= (1<<INT2);
#elif EXTI_INT2_STATE == DISABLE
	GICR &= ~(1<<INT2);
#else
	return Local_enuErrorState;
#endif

#if EXTI_INT0_MOOD <= RISSING
	MCUCR &= ~((1<<ISC00)|(1<<ISC01));
	MCUCR |= (EXTI_INT0_MOOD<<ISC00);
#else
	return Local_enuErrorState;
#endif
#if EXTI_INT1_MOOD <= RISSING
	MCUCR &= ~((1<<ISC10)|(1<<ISC11));
	MCUCR |= (EXTI_INT1_MOOD<<ISC10);
	#else
	return Local_enuErrorState;
#endif
#if EXTI_INT2_MOOD == RISSING
	MCUCSR |= (1<<ISC2);
#elif EXTI_INT2_MOOD == FALLING
	MCUCSR &= ~(1<<ISC2);
#else
	return Local_enuErrorState;
#endif

	Local_enuErrorState = ES_OK;		

	return Local_enuErrorState;
}

ES_t EXTI_enuSetInterrubtMood(u8 Copy_u8IntPin,u8 Copy_u8IntMood)
{
	ES_t Local_enuErrorState=ES_NOK;
	switch(Copy_u8IntPin)
	{
		case INT0:
			if(Copy_u8IntMood<=RISSING)	
			{
				MCUCR &= ~((1<<ISC00)|(1<<ISC01));
				MCUCR |= (Copy_u8IntMood<<ISC00);
				Local_enuErrorState = ES_OK;
			}
			break;
		case INT1:
			if(Copy_u8IntMood<=RISSING)
			{
				MCUCR &= ~((1<<ISC10)|(1<<ISC11));
				MCUCR |= (Copy_u8IntMood<<ISC10);
				Local_enuErrorState = ES_OK;
			}
			break;
		case INT2:
			if(Copy_u8IntMood==RISSING )
			{
				MCUCSR |= (1<<ISC2);
				Local_enuErrorState = ES_OK;
			}
			else if (Copy_u8IntMood==FALLING)
			{
				MCUCSR &= ~(1<<ISC2);
				Local_enuErrorState = ES_OK;
			}
			break;
	}
	
	return Local_enuErrorState;
}

ES_t EXTI_enuEnableInterrupt(u8 Copy_u8IntPin)
{
	ES_t Local_enuErrorState=ES_NOK;
	if(Copy_u8IntPin<=INT1 && Copy_u8IntPin>= INT2)
	{
		GICR |=(1<<Copy_u8IntPin);		
		Local_enuErrorState = ES_OK;
	}
	return Local_enuErrorState;
}

ES_t EXTI_enuDisableIntrrubt(u8 Copy_u8IntPin)
{
	ES_t Local_enuErrorState=ES_NOK;
	if(Copy_u8IntPin<=INT1 && Copy_u8IntPin>= INT2)
	{
		GICR &=~(1<<Copy_u8IntPin);
		Local_enuErrorState = ES_OK;
	}
	return Local_enuErrorState;
}

ES_t EXTI_enuCallBackFun(void (*Copy_pfunAPPFun)(void*),void * Copy_pvidFunparameter,u8 Copy_u8IntPin)
{
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_pfunAPPFun)
		if(Copy_u8IntPin<=INT1 && Copy_u8IntPin>=INT2)
		{
			EXTI_ApfunISRfun[Copy_u8IntPin-INT2] = Copy_pfunAPPFun;
			EXTI_ApvidISRParameter[Copy_u8IntPin-INT2] = Copy_pvidFunparameter;
			Local_enuErrorState = ES_OK;
		}
	
	return Local_enuErrorState;
}

void __vector_1(void)__attribute__((signal));
void __vector_1(void)
{
	if(EXTI_ApfunISRfun[INT0-INT2])
	{
		EXTI_ApfunISRfun[INT0-INT2](EXTI_ApvidISRParameter[INT0-INT2]);
	}
}

void __vector_2(void)__attribute__((signal));
void __vector_2(void)
{
	if(EXTI_ApfunISRfun[INT1-INT2])
	{
		EXTI_ApfunISRfun[INT1-INT2](EXTI_ApvidISRParameter[INT1-INT2]);
	}
}

void __vector_3(void)__attribute__((signal));
void __vector_3(void)
{
	if(EXTI_ApfunISRfun[INT2-INT2])
	{
		EXTI_ApfunISRfun[INT2-INT2](EXTI_ApvidISRParameter[INT2-INT2]);
	}
	
}