/*
 * DIO.c
 *
 *  Created on: Oct 8, 2021
 *      Author: Ahmed
 */
#include<stdio.h>
#include <avr/delay.h>
#include "Std_Types.h"
#include "macros.h"
#include "DIO.h"
#include "register.h"

u8 DIO_Set_PORT_Direction(u8 portNum , u8 Direction)
{
	s8 State;

	State = OK;
		switch(portNum)
		{
		case PortA_Num :

			DDRA = Direction;
			break;
		case PortB_Num:

			DDRB = Direction;
			break;

		case PortC_Num:
			DDRC = Direction;
			break;

		case PortD_Num:
			DDRD = Direction;
			break;
		default:
			State = Not_OK;
		}

		return(State);
}
u8 DIO_Set_PIN_Direction(u8 portNum ,u8 pinNum ,u8 Direction)
{
	s8 State;

		State = OK;
	switch(portNum)
		{
		case PortA_Num :
			switch(Direction)
			{
				case INPUT:
					bitclear(DDRA,pinNum);

					break;
				case OUTPUT:
					bitset(DDRA,pinNum);
					break;
				default:
					State = Not_OK;
					break;
				}
				break;
		case PortB_Num:
				switch(Direction)
				{
				case INPUT:
					bitclear(DDRB,pinNum);
					break;
				case OUTPUT:
					bitset(DDRB,pinNum);
					break;
				default:
					State = Not_OK;
					break;
				}
				break;
		case PortC_Num:
			switch(Direction)
			{
			case INPUT:
				bitclear(DDRC,pinNum);
				break;
			case OUTPUT:
				bitset(DDRC,pinNum);
				break;
			default:
				State = Not_OK;
				break;
			}
			break;
		case PortD_Num:
			switch(Direction)
			{
			case INPUT:
				bitclear(DDRD,pinNum);
				break;
			case OUTPUT:
				bitset(DDRD,pinNum);
				break;
			default:
				State = Not_OK;
				break;
			}
			break;
			default:
				State = Not_OK;

}

		return(State);
	}

u8 DIO_Set_PORT_Value(u8 portNum , u8 Value)
{
	s8 State;

	State = OK;
			switch(portNum)
			{
			case PortA_Num :

			PORTA = Value;
			break;
			case PortB_Num:

			PORTB = Value;
					break;

			case PortC_Num:
			PORTC = Value;
			break;

			case PortD_Num:
			PORTD = Value;
			break;
			default:
			State = Not_OK;
			}

			return(State);
	}

u8 DIO_Set_PIN_Value(u8 portNum ,u8 pinNum ,u8 Value)
{
	s8 State;

		State = OK;
		switch(portNum)
		{
		case PortA_Num :
		switch(Value)
		{
		case LOW:
		bitclear(PORTA,pinNum);

		break;
		case HIGH:
		bitset(PORTA,pinNum);
		break;
		default:
		State = Not_OK;
		break;
		}
					break;
			case PortB_Num:
					switch(Value)
					{
					case LOW:
						bitclear(PORTB,pinNum);
						break;
					case HIGH:
						bitset(PORTB,pinNum);
						break;
					default:
						State = Not_OK;
						break;
					}
					break;
			case PortC_Num:
				switch(Value)
				{
				case LOW:
					bitclear(PORTC,pinNum);
					break;
				case HIGH:
					bitset(PORTC,pinNum);
					break;
				default:
					State = Not_OK;
					break;
				}
				break;
			case PortD_Num:
				switch(Value)
				{
				case LOW:
					bitclear(PORTD,pinNum);
					break;
				case HIGH:
					bitset(PORTD,pinNum);
					break;
				default:
					State = Not_OK;
					break;
				}
				break;
				default:
					State = Not_OK;

	}

			return(State);
		}
u8 DIO_get_PORT_Vlaue(u8 portNum ,u8*Register_Reading)
{
	s8 State;


		switch(portNum)
		{
		case PortA_Num :

			*Register_Reading = PINA;
			break;
		case PortB_Num:

			*Register_Reading = PINB;
			break;

		case PortC_Num:
			*Register_Reading = PINC;
			break;

		case PortD_Num:
			*Register_Reading = PIND;
			break;
		default:
			State = Not_OK;
		}

		return(State);
}

u8 DIO_get_PIN_Vlaue(u8 portNum ,u8 pinNum,u8*PIN_value)
{
	s8 State;


		switch(portNum)
		{
		case PortA_Num :

			*PIN_value = 	Git_bit(PINA,pinNum);
			break;
		case PortB_Num:

			*PIN_value = 	Git_bit(PINB,pinNum);
			break;

		case PortC_Num:
			*PIN_value = 	Git_bit(PINC,pinNum);
			break;

		case PortD_Num:
			*PIN_value = 	Git_bit(PIND,pinNum);
			break;
		default:
			State = Not_OK;
		}

		return(State);
}
