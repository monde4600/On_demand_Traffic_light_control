/*
 * TIMER0_config.h
 *
 * Created: 9/23/2022 1:27:36 PM
 *  Author: abano
 */ 


#ifndef TIMER0_CONFIG_H_
#define TIMER0_CONFIG_H_

#ifndef F_CPU
#define F_CPU						(16000000ul)
#endif

/*WAVE moods

 TIMER0_Normal					
 TIMER0_PhaseCorrectPWM			
 TIMER0_CTC						
 TIMER0_FastPWM					

*/

#define TIMER0_WAV_Mood				(TIMER0_Normal)

/* out moods
 TIMER0_OC0_Normal				
 TIMER0_OC0_Toggle				
 TIMER0_OC0_ClearSet				
 TIMER0_OC0_SetClear				
*/
#define TIMER0_OUT_MOOD				(TIMER0_OC0_Normal)

/* 
 TIMER0_PRESC_1					
 TIMER0_PRESC_8					
 TIMER0_PRESC_64				
 TIMER0_PRESC_256				
 TIMER0_PRESC_1024				

*/
#define TMER0_Prescaller			TIMER0_PRESC_1024
/*Interrupt moods
TIMER0_OVFSInterrEN
TIMER0_CompMatchInterrENI
TIMER0_CompMatchInterrEN|TMER0_OVFSInterrEN
0
*/
#define TIMER0_Interr_Mood			((TIMER0_OVFSInterrEN))

#endif /* TIMER0_CONFIG_H_ */