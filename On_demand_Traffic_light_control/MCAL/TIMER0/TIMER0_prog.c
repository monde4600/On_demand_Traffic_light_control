/*
 * TIMER0_prog.c
 *
 * Created: 9/23/2022 1:27:57 PM
 *  Author: abano
 */ 
#include "../../LIBRARY/errorState.h"
#include "../../LIBRARY/stdTypes.h"
#include "../Atmega32_Registers.h"
#include "TIMER0_priv.h"
#include "TIMER0_config.h"
static void (*TIMER0_ApfunISRfun[2])(void*);
static void *TIMER0_ApvidISRParameter[2];

ES_t TIMER0_enuInit()
{
	ES_t Local_enuErrorState=ES_NOK;
#if !(TIMER0_WAV_Mood & ~((1<<WGM01)|(1<<WGM00))) && !(TIMER0_OUT_MOOD & ~((1<<COM01)|(1<<COM00))) && TMER0_Prescaller <= TIMER0_PRESC_1024\
     && TMER0_Prescaller >= TIMER0_PRESC_1
	#if TIMER0_Interr_Mood <= (TIMER0_CompMatchInterrEN|TIMER0_OVFSInterrEN)
		Local_enuErrorState = ES_OK;
		TCCR0 = (TIMER0_WAV_Mood)|(TIMER0_OUT_MOOD)|(TMER0_Prescaller);
		TIMSK &=~(TIMER0_CompMatchInterrEN|TIMER0_OVFSInterrEN);
		TIMSK |= TIMER0_Interr_Mood;
	#endif
#endif
	return Local_enuErrorState ;
}

ES_t TIMER0_enuDelay_MS(u16 Copy_u16DelayMs)
{
	ES_t Local_enuErrorState=ES_NOK;
	
	
	if (!(TIMSK & (TIMER0_OVFSInterrEN)))
	{
		u16 Local_u16Top ;
		if((TCCR0 & (TIMER0_FastPWM)) == (TIMER0_FastPWM)||(TCCR0 & (TIMER0_FastPWM)) == (TIMER0_Normal))
			Local_u16Top = TIMER0_PWMTOP;
		else if((TCCR0 & (TIMER0_FastPWM)) == (TIMER0_CTC))
			Local_u16Top = OCR0;
		else  Local_u16Top = TIMER0_PWMTOP*2;     	
		
		#if TMER0_Prescaller == TIMER0_PRESC_1
		f32 Local_f32Counter = (F_CPU/1000)*Copy_u16DelayMs /(Local_u16Top+1)/1; 
		#elif TMER0_Prescaller == TIMER0_PRESC_8
		f32 Local_f32Counter = (F_CPU/1000)*Copy_u16DelayMs /(Local_u16Top+1)/8;
		#elif TMER0_Prescaller == TIMER0_PRESC_64
		f32 Local_f32Counter = (F_CPU/1000)*Copy_u16DelayMs /(Local_u16Top+1)/64;
		#elif TMER0_Prescaller == TIMER0_PRESC_256
		f32 Local_f32Counter = (F_CPU/1000)*Copy_u16DelayMs /(Local_u16Top+1)/256;
		#elif TMER0_Prescaller == TIMER0_PRESC_1024
		f32 Local_f32Counter = (F_CPU/1000)*Copy_u16DelayMs /(Local_u16Top+1)/1024;
		#endif
		u16 Local_u16Counter = (u16)Local_f32Counter;
		TCNT0 = (1.f-(Local_f32Counter-(u32)Local_f32Counter))*Local_u16Top;  
		Local_u16Counter++;
		while(Local_u16Counter)
			if(TIFR &(1<<TOV0))
			{
				Local_u16Counter--;
				TIFR |=1;	
			}
			Local_enuErrorState = ES_OK;
	}
 
	return Local_enuErrorState ;
}

ES_t TIMER0_enuDelay_US(u16 Copy_u16Delayus)
{
	ES_t Local_enuErrorState=ES_NOK;
	#if F_CPU == 16000000
	u16 Conts = ((Copy_u16Delayus) * 16/7)-14 ;
	# warning "TIMER0_enuDelay_US could take number less than 7 us"
	#elif F_CPU == 8000000
	u16 Conts = ((Copy_u16Delayus) * 8/7)-14 ;
	# warning "TIMER0_enuDelay_US could take number less than 14 us"
	#elif F_CPU == 4000000
	u16 Conts = ((Copy_u16Delayus) * 4/7)-14 ;
	# warning "TIMER0_enuDelay_US could take number less than 25 us"
	#elif F_CPU == 1000000
	u16 Conts = ((Copy_u16Delayus) * 1/7)-14 ;
	# warning "TIMER0_enuDelay_US could take number less than 100 us"
	#endif
	while(Conts--);
	return Local_enuErrorState ;
}

ES_t TIMER0_enuWrightPWMFastMood(u8 Copy_u8Duty)
{
	ES_t Local_enuErrorState=ES_NOK;
	if((TCCR0 & (TIMER0_FastPWM)) == (TIMER0_FastPWM))
	{	if((TCCR0 &(TIMER0_OC0_SetClear))==(TIMER0_OC0_ClearSet))
		{
			Local_enuErrorState = ES_OK;
			if(!Copy_u8Duty)
				OCR0 = 0;
			else	OCR0 = ((f32)TIMER0_PWMTOP+1)*Copy_u8Duty/100.f -1;
		}
		else if((TCCR0 &(TIMER0_OC0_SetClear)) ==(TIMER0_OC0_SetClear))
		{
			Local_enuErrorState = ES_OK;
			if(100 == Copy_u8Duty)
				OCR0 = 0;
			else	OCR0 = TIMER0_PWMTOP-((f32)TIMER0_PWMTOP+1) * Copy_u8Duty/100.f ;
		}
	}
	return Local_enuErrorState ;
}

ES_t TIMER0_enuWrightPWMPhaseCorrect(u8 Copy_u8Duty)
{
	ES_t Local_enuErrorState=ES_NOK;
	if((TCCR0 & (TIMER0_FastPWM)) == (TIMER0_PhaseCorrectPWM))
	{
		if((TCCR0 &(TIMER0_OC0_SetClear)) == (TIMER0_OC0_ClearSet))
		{
			Local_enuErrorState = ES_OK;
			OCR0 = (f32)TIMER0_PWMTOP*Copy_u8Duty/100.f;
		}
		else if((TCCR0 &(TIMER0_OC0_SetClear)) == (TIMER0_OC0_SetClear))
		{
			Local_enuErrorState = ES_OK;
			OCR0 = TIMER0_PWMTOP -((f32)TIMER0_PWMTOP*Copy_u8Duty/100.f) ;
		}
	}
	return Local_enuErrorState ;
}

ES_t TIMER0_enuSetCTCValue(u8 Copy_CTCVvalue)
{
	ES_t Local_enuErrorState=ES_NOK;
	if((TCCR0 & (TIMER0_FastPWM)) == (TIMER0_CTC))
	{
		Local_enuErrorState = ES_OK;
		OCR0 = Copy_CTCVvalue;
	}
	return Local_enuErrorState ;
}

ES_t TIMER0_enuSetWaveMood(u8 Copy_u8WaveMood)
{
	ES_t Local_enuErrorState=ES_NOK;
	if(!(Copy_u8WaveMood & ~(TIMER0_FastPWM)))
	{
		Local_enuErrorState=ES_OK;
		TCCR0 &= ~(TIMER0_FastPWM);
		TCCR0 |= Copy_u8WaveMood;
	}
	return Local_enuErrorState ;
}

ES_t TIMER0_enuSetOutPinMood(u8 Copy_u8OutPinMood)
{
	ES_t Local_enuErrorState=ES_NOK;
	if(!(Copy_u8OutPinMood & ~(TIMER0_OC0_SetClear)))
	{
		Local_enuErrorState=ES_OK;
		TCCR0 &= ~(TIMER0_OC0_SetClear);
		TCCR0 |= Copy_u8OutPinMood;
	}
	return Local_enuErrorState ;
}
ES_t TIMER0_enuEnableInterrupt(u8 Copy_u8Interrupt)
{
	ES_t Local_enuErrorState=ES_NOK;
	if(!(Copy_u8Interrupt & ~(TIMER0_OVFSInterrEN | TIMER0_CompMatchInterrEN)) && Copy_u8Interrupt)
	{
		Local_enuErrorState=ES_OK;
		TCCR0 |= Copy_u8Interrupt;
	}
	return Local_enuErrorState ;
}

ES_t TIMER0_enudisableInterrupt(u8 Copy_u8Interrupt)
{
	ES_t Local_enuErrorState=ES_NOK;
	if(!(Copy_u8Interrupt & ~(TIMER0_OVFSInterrEN | TIMER0_CompMatchInterrEN)) && Copy_u8Interrupt)
	{
		Local_enuErrorState=ES_OK;
		TCCR0 &= ~(Copy_u8Interrupt);
	}
	return Local_enuErrorState ;
}

ES_t TIMER0_enuCallBackFun(void (*Copy_pfunAPPFun)(void*) ,void * Copy_pvidParameter,u8 Copy_InterruptMood)
{
	ES_t Local_enuErrorState=ES_NOK;
	if(Copy_pfunAPPFun)
	{
		if((TIMER0_OVFSInterrEN)==Copy_InterruptMood)
		{
			TIMER0_ApfunISRfun[0] = Copy_pfunAPPFun;
			TIMER0_ApvidISRParameter[0]= Copy_pvidParameter;
			Local_enuErrorState = ES_OK;
		}
		else if((TIMER0_CompMatchInterrEN)==Copy_InterruptMood)
		{
			TIMER0_ApfunISRfun[1] = Copy_pfunAPPFun;
			TIMER0_ApvidISRParameter[1]= Copy_pvidParameter;
			Local_enuErrorState = ES_OK;
		}
	}
	else	Local_enuErrorState = ES_NULL_POINTER;
	return Local_enuErrorState ;
}
void __vector_11(void)__attribute__((signal));	//OVF
void __vector_11(void)	//OVF		0
{
	
	if(TIMER0_ApfunISRfun[0] )	
		TIMER0_ApfunISRfun[0](TIMER0_ApvidISRParameter[0]);
	
}
void __vector_10(void)__attribute__((signal));  //CM
void __vector_10(void)  //CM		1
{
	if(TIMER0_ApfunISRfun[1] )
	TIMER0_ApfunISRfun[1](TIMER0_ApvidISRParameter[1]);	
}
