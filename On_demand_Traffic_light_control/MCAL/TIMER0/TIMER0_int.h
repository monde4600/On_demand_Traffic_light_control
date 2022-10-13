/*
 * TIMER0_int.h
 *
 * Created: 9/23/2022 1:27:06 PM
 *  Author: abano
 */ 


#ifndef TIMER0_INT_H_
#define TIMER0_INT_H_

ES_t TIMER0_enuInit();
ES_t TIMER0_enuDelay_MS(u16 Copy_u16DelayMs);
ES_t TIMER0_enuDelay_US(u16 Copy_u16Delayus);
ES_t TIMER0_enuWrightPWMFastMood(u8 Copy_u8Duty);
ES_t TIMER0_enuWrightPWMPhaseCorrect(u8 Copy_u8Duty);
ES_t TIMER0_enuSetCTCValue(u8 Copy_CTCVvalue);
ES_t TIMER0_enuSetWaveMood(u8 Copy_u8WaveMood);
ES_t TIMER0_enuSetOutPinMood(u8 Copy_u8OutPinMood);
ES_t TIMER0_enuEnableInterrupt(u8 Copy_u8Interrupt);
ES_t TIMER0_enudisableInterrupt(u8 Copy_u8Interrupt);

ES_t TIMER0_enuCallBackFun(void (*Copy_pfunAPPFun)(void*) ,void * Copy_pvidParameter,u8 Copy_InterruptMood);

#define OCIE0							1
#define TOIE0							0
#define TIMER0_OVFSInterr				(1<<TOIE0)
#define TIMER0_CompMatchInterr			(1<<OCIE0)
#ifndef GLOBALINTERRUPT
#define GLOBALINTERRUPT
#define GLOBALINTERRUPT_EN()	asm("SEI")
#define GLOBALINTERRUPT_DI()	asm("CLI")

#endif

#endif /* TIMER0_INT_H_ */