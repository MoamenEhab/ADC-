/*
 * DIO.h
 *
 *  Created on: Oct 8, 2021
 *      Author: Ahmed
 */
#include "std_Types.h"
#ifndef DIO_H_
#define DIO_H_
#define  PIN_0 0
#define  PIN_1 1
#define  PIN_2 2
#define  PIN_3 3
#define  PIN_4 4
#define  PIN_5 5
#define  PIN_6 6
#define  PIN_7 7
#define	 OUTPUT 1
#define	 INPUT 0
#define  PortA_Num 0
#define  PortB_Num 1
#define  PortC_Num 2
#define  PortD_Num 3
#define  AllOutput 255
#define  AllInput 0
#define  AllHigh 255
#define  AllLow 0
#define  HIGH 1
#define  LOW 0
#define  OK 1
#define  Not_OK 0
#define  PORT_OUTPUT OxFF
#define  num_1 0b00000110
#define  num_0 0b00111111
#define  num_2 0b01011011
#define  num_3 0b01001111
#define  num_4 0b01100111
#define  num_5 0b01101101
#define  num_6 0b01111101
#define  num_7 0b00000111
#define  num_8 0b01111111
#define  num_9 0b01101111
u8 DIO_Set_PORT_Direction(u8 portNum , u8 Direction);
u8 DIO_Set_PIN_Direction(u8 portNum ,u8 pinNum ,u8 Direction);
u8 DIO_Set_PORT_Value(u8 portNum , u8 Value);
u8 DIO_Set_PIN_Value(u8 portNum ,u8 pinNum ,u8 Value);
u8 DIO_get_PORT_Vlaue(u8 portNum ,u8*Register_Reading);
u8 DIO_get_PIN_Vlaue(u8 portNum ,u8 pinNum,u8*PIN_value);

#endif /* DIO_H_ */
