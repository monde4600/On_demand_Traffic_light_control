/*
* DIO_prog.c
*
* Created: 9/22/2022 10:32:55 PM
*  Author: abano
*/
#include "../../LIBRARY/errorState.h"
#include "../../LIBRARY/stdTypes.h"
#include "DIO_priv.h"
#include "../Atmega32_Registers.h"

ES_t DIO_enuSetGroupDirection(u8 Copy_u8Group,u8 Copy_u8GroupDirection)
{
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_u8Group>=DIO_GroupA && Copy_u8Group <= DIO_GroupD && Copy_u8GroupDirection <= DIO_MaxREGISValue)
	{
		Local_enuErrorState = ES_OK;
		switch(Copy_u8Group)
		{
			case DIO_GroupA :
			DDRA = Copy_u8GroupDirection;
			break;
			case DIO_GroupB :
			DDRB = Copy_u8GroupDirection;
			break;
			case DIO_GroupC :
			DDRC = Copy_u8GroupDirection;
			break;
			case DIO_GroupD :
			DDRD = Copy_u8GroupDirection;
			break;
		}
	}
	return Local_enuErrorState;
}

ES_t DIO_enuSetGroupValue(u8 Copy_u8Group,u8 Copy_u8GroupValue)
{
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_u8Group>=DIO_GroupA && Copy_u8Group <= DIO_GroupD && Copy_u8GroupValue <= DIO_MaxREGISValue)
	{
		Local_enuErrorState = ES_OK;
		switch(Copy_u8Group)
		{
			case DIO_GroupA :
			PORTA = Copy_u8GroupValue;
			break;
			case DIO_GroupB :
			PORTB = Copy_u8GroupValue;
			break;
			case DIO_GroupC :
			PORTC = Copy_u8GroupValue;
			break;
			case DIO_GroupD :
			PORTD = Copy_u8GroupValue;
			break;
		}
	}
	return Local_enuErrorState;
}

ES_t DIO_enuGetGroupValue(u8 Copy_u8Group,u8* Copy_pu8GroupValue)
{
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_u8Group>=DIO_GroupA && Copy_u8Group <= DIO_GroupD )
	{
		if(NULL!=Copy_pu8GroupValue)
		{
			Local_enuErrorState = ES_OK;
			switch(Copy_u8Group)
			{
				case DIO_GroupA :
				*Copy_pu8GroupValue = PINA;
				break;
				case DIO_GroupB :
				*Copy_pu8GroupValue = PINB;
				break;
				case DIO_GroupC :
				*Copy_pu8GroupValue = PINC;
				break;
				case DIO_GroupD :
				*Copy_pu8GroupValue = PIND;
				break;
			}
			
		}
		else  Local_enuErrorState = ES_NULL_POINTER;
	}
	return Local_enuErrorState;
}

ES_t DIO_enuSetPinDirection(u8 Copy_u8Group,u8 Copy_u8Pin,u8 Copy_u8Direction)
{
	ES_t Local_enuErrorState = ES_NOK;
	if (Copy_u8Group>=DIO_GroupA && Copy_u8Group <= DIO_GroupD && Copy_u8Pin>=DIO_PIN_0 && Copy_u8Pin <= DIO_PIN_7)
	{
		if(DIO_OUTPUT == Copy_u8Direction)
		{
			Local_enuErrorState= ES_OK;
			switch(Copy_u8Group)
			{
				case DIO_GroupA :
				DDRA |= (1<<Copy_u8Pin);
				break;
				case DIO_GroupB :
				DDRB |= (1<<Copy_u8Pin);
				break;
				case DIO_GroupC :
				DDRC |= (1<<Copy_u8Pin);
				break;
				case DIO_GroupD :
				DDRD |= (1<<Copy_u8Pin);
				break;
			}
		}
		else if(DIO_INPUT == Copy_u8Direction)
		{
			Local_enuErrorState= ES_OK;
			switch(Copy_u8Group)
			{
				case DIO_GroupA :
				DDRA &= ~(1<<Copy_u8Pin);
				break;
				case DIO_GroupB :
				DDRB &= ~(1<<Copy_u8Pin);
				break;
				case DIO_GroupC :
				DDRC &= ~(1<<Copy_u8Pin);
				break;
				case DIO_GroupD :
				DDRD &= ~(1<<Copy_u8Pin);
				break;
			}
		}
		
	}
	return Local_enuErrorState;
}

ES_t DIO_enuSetPinValue(u8 Copy_u8Group,u8 Copy_u8Pin,u8 Copy_u8Value)
{
	ES_t Local_enuErrorState = ES_NOK;
	if (Copy_u8Group>=DIO_GroupA && Copy_u8Group <= DIO_GroupD && Copy_u8Pin>=DIO_PIN_0 && Copy_u8Pin <= DIO_PIN_7)
	{
		if(DIO_HIGH == Copy_u8Value)
		{
			Local_enuErrorState= ES_OK;
			switch(Copy_u8Group)
			{
				case DIO_GroupA :
				PORTA |= (1<<Copy_u8Pin);
				break;
				case DIO_GroupB :
				PORTB |= (1<<Copy_u8Pin);
				break;
				case DIO_GroupC :
				PORTC |= (1<<Copy_u8Pin);
				break;
				case DIO_GroupD :
				PORTD |= (1<<Copy_u8Pin);
				break;
			}
		}
		else if(DIO_LOW == Copy_u8Value)
		{
			Local_enuErrorState= ES_OK;
			switch(Copy_u8Group)
			{
				case DIO_GroupA :
				PORTA &= ~(1<<Copy_u8Pin);
				break;
				case DIO_GroupB :
				PORTB &= ~(1<<Copy_u8Pin);
				break;
				case DIO_GroupC :
				PORTC &= ~(1<<Copy_u8Pin);
				break;
				case DIO_GroupD :
				PORTD &= ~(1<<Copy_u8Pin);
				break;
			}
		}
		
	}
	return Local_enuErrorState;
}

ES_t DIO_enuGetPinValue(u8 Copy_u8Group,u8 Copy_u8Pin,u8* Copy_pu8Value)
{
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_u8Group>=DIO_GroupA && Copy_u8Group <= DIO_GroupD && Copy_u8Pin>=DIO_PIN_0 && Copy_u8Pin <= DIO_PIN_7)
	{
		if (NULL!=Copy_pu8Value)
		{
			Local_enuErrorState = ES_OK;
			switch(Copy_u8Group)
			{
				case DIO_GroupA :
				*Copy_pu8Value = 1 & (PINA>>Copy_u8Pin);
				break;
				case DIO_GroupB :
				*Copy_pu8Value = 1 & (PINB>>Copy_u8Pin);
				break;
				case DIO_GroupC :
				*Copy_pu8Value = 1 & (PINC>>Copy_u8Pin);
				break;
				case DIO_GroupD :
				*Copy_pu8Value = 1 & (PIND>>Copy_u8Pin);
				break;
			}
		}
		else Local_enuErrorState = ES_NULL_POINTER;
	}
	return Local_enuErrorState;
}

ES_t DIO_enuTogglePin(u8 Copy_u8Group,u8 Copy_u8Pin)
{
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_u8Group>=DIO_GroupA && Copy_u8Group <= DIO_GroupD && Copy_u8Pin>=DIO_PIN_0
	&& Copy_u8Pin <= DIO_PIN_7)
	{
		switch(Copy_u8Group)
		{
			case DIO_GroupA :
			PORTA ^= (1<<Copy_u8Pin);
			break;
			case DIO_GroupB :
			PORTB ^= (1<<Copy_u8Pin);
			break;
			case DIO_GroupC :
			PORTC ^= (1<<Copy_u8Pin);
			break;
			case DIO_GroupD :
			PORTD ^= (1<<Copy_u8Pin);
			break;
		}
	}
	return Local_enuErrorState;
}
