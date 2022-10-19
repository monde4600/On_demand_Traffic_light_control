/*
 * EXTI_config.h
 *
 * Created: 9/30/2022 9:55:46 PM
 *  Author: abano
 */ 


#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_

//ENABLE  or DISABLE
#define EXTI_INT0_STATE			ENABLE
#define EXTI_INT1_STATE			DISABLE
#define EXTI_INT2_STATE			DISABLE
//FALLING  RISSING ANY_LOGICAL 
#define EXTI_INT0_MOOD			RISSING    
#define EXTI_INT1_MOOD			ANY_LOGICAL
//FALLING     RISSING
#define EXTI_INT2_MOOD			RISSING


#endif /* EXTI_CONFIG_H_ */