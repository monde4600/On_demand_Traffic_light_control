/*
 * DIO_int.h
 *
 * Created: 9/22/2022 10:32:19 PM
 *  Author: abano
 */ 


#ifndef DIO_INT_H_
#define DIO_INT_H_

ES_t DIO_enuSetGroupDirection(u8 Copy_u8Group,u8 Copy_u8GroupDirection);
ES_t DIO_enuSetGroupValue(u8 Copy_u8Group,u8 Copy_u8GroupValue);
ES_t DIO_enuGetGroupValue(u8 Copy_u8Group,u8* Copy_pu8GroupValue);
ES_t DIO_enuSetPinDirection(u8 Copy_u8Group,u8 Copy_u8Pin,u8 Copy_u8Direction);
ES_t DIO_enuSetPinValue(u8 Copy_u8Group,u8 Copy_u8Pin,u8 Copy_u8Value);
ES_t DIO_enuGetPinValue(u8 Copy_u8Group,u8 Copy_u8Pin,u8* Copy_pu8Value);
ES_t DIO_enuTogglePin(u8 Copy_u8Group,u8 Copy_u8Pin);

#define DIO_GroupA				11
#define DIO_GroupB				12
#define DIO_GroupC				13
#define DIO_GroupD				14

#define DIO_PIN_0					0
#define DIO_PIN_1					1
#define DIO_PIN_2					2
#define DIO_PIN_3					3
#define DIO_PIN_4					4
#define DIO_PIN_5					5
#define DIO_PIN_6					6
#define DIO_PIN_7					7

#define DIO_OUTPUT					1
#define DIO_INPUT					0

#define DIO_HIGH					1
#define DIO_LOW						0

#endif /* DIO_INT_H_ */