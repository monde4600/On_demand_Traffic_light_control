/*
 * TIMER0_priv.h
 *
 * Created: 9/23/2022 1:26:37 PM
 *  Author: abano
 */ 


#ifndef TIMER0_PRIV_H_
#define TIMER0_PRIV_H_
//control BITS
#define FOC0					7 
#define WGM00					6
#define COM01					5
#define COM00					4
#define WGM01					3
#define CS02					2
#define CS01					1
#define CS00					0

#define TIMER0_Normal					(0<<WGM01)|(0<<WGM00)	
#define TIMER0_PhaseCorrectPWM			(0<<WGM01)|(1<<WGM00)
#define TIMER0_CTC						(1<<WGM01)|(0<<WGM00)
#define TIMER0_FastPWM					(1<<WGM01)|(1<<WGM00)

#define TIMER0_OC0_Normal				(0<<COM01)|(0<<COM00)
#define TIMER0_OC0_Toggle				(0<<COM01)|(1<<COM00)
#define TIMER0_OC0_ClearSet				(1<<COM01)|(0<<COM00)
#define TIMER0_OC0_SetClear				(1<<COM01)|(1<<COM00)

#define TIMER0_PRESC_1					1	//(0<<CS02)|(0<<CS01)|(1<<CS00)	
#define TIMER0_PRESC_8					2	//(0<<CS02)|(1<<CS01)|(0<<CS00)	
#define TIMER0_PRESC_64					3	//(0<<CS02)|(1<<CS01)|(1<<CS00)	
#define TIMER0_PRESC_256				4	//(1<<CS02)|(0<<CS01)|(1<<CS00)	
#define TIMER0_PRESC_1024				5
//Interrupt Moods BITS
#define OCIE0							1
#define TOIE0							0

#define TIMER0_OVFSInterrEN				(1<<TOIE0)
#define TIMER0_CompMatchInterrEN		(1<<OCIE0)
//Flags BITS
#define OCF0							1
#define	TOV0							0
#define TIMER0_PWMTOP					0XFF

#endif /* TIMER0_PRIV_H_ */