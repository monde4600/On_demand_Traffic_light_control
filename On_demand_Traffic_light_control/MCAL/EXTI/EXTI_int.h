/*
 * EXTI_int.h
 *
 * Created: 9/30/2022 9:57:16 PM
 *  Author: abano
 */ 


#ifndef EXTI_INT_H_
#define EXTI_INT_H_

#ifndef GLOBALINTERRUPT
#define GLOBALINTERRUPT
#define GLOBALINTERRUPT_EN()	asm("SEI")
#define GLOBALINTERRUPT_DI()	asm("CLI")

#endif

ES_t EXTI_enuInit(void);
ES_t EXTI_enuSetInterrubtMood(u8 Copy_u8IntPin,u8 Copy_u8IntMood);
ES_t EXTI_enuEnableInterrupt(u8 Copy_u8IntPin);
ES_t EXTI_enuDisableIntrrubt(u8 Copy_u8IntPin);
ES_t EXTI_enuCallBackFun(void (*Copy_pfunAPPFun)(void*),void * Copy_pvidFunparameter,u8 Copy_u8IntPin);


#define EXTI_INT1	7
#define EXTI_INT0	6
#define EXTI_INT2	5


#define EXTI_ANY_LOGICAL			1
#define EXTI_FALLING				2
#define EXTI_RISSING				3

#endif /* EXTI_INT_H_ */