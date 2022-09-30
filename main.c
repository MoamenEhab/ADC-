/* main.c
 * this file contains simple ADC application
 * Created on: september 4,2022
 * Author: Moamen ehab
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Common/Std_Types.h"
#include "Drivers/DIO/DIO.h"
#include "Common/macros.h"
#include <avr/delay.h>
#include "Common/register.h"
#include "Drivers/ADC/ADC_interface.h"
#include "Common/private.h"


u8 flag;
u16*ptr;
void callbachfn(u16*p)
{
	ptr = p ;
	flag=1;
}



void main ()
{
	ADC_init();

	flag = 0 ;
	DIO_Set_PIN_Direction(PortA_Num,PIN_0,INPUT);
	DIO_Set_PIN_Direction(PortD_Num,PIN_5,OUTPUT);
	DIO_Set_PIN_Direction(PortD_Num,PIN_6,OUTPUT);
	DIO_Set_PIN_Direction(PortD_Num,PIN_7,OUTPUT);
	GIE_enable();



	while(1)
	{

		DIO_Set_PIN_Value(PortD_Num,PIN_5,HIGH);
		DIO_Set_PIN_Value(PortD_Num,PIN_6,HIGH);
		DIO_Set_PIN_Value(PortD_Num,PIN_7,HIGH);
		_delay_ms(1000);


		ADC_freeRunConversion(callbachfn);

		while (flag == 0);

		while (ptr[0]==0xFFFF);
		DIO_Set_PIN_Value(PortD_Num,PIN_5,HIGH);
		DIO_Set_PIN_Value(PortD_Num,PIN_6,LOW);
		DIO_Set_PIN_Value(PortD_Num,PIN_7,LOW);
		_delay_ms(1000);
		while (ptr[1]==0xFFFF);
		DIO_Set_PIN_Value(PortD_Num,PIN_5,LOW);
		DIO_Set_PIN_Value(PortD_Num,PIN_6,HIGH);
		DIO_Set_PIN_Value(PortD_Num,PIN_7,LOW);
		_delay_ms(1000);

		while (ptr[2]==0xFFFF);
		DIO_Set_PIN_Value(PortD_Num,PIN_5,LOW);
		DIO_Set_PIN_Value(PortD_Num,PIN_6,LOW);
		DIO_Set_PIN_Value(PortD_Num,PIN_7,HIGH);
		_delay_ms(1000);

		while (ptr[3]==0xFFFF);
		DIO_Set_PIN_Value(PortD_Num,PIN_5,LOW);
		DIO_Set_PIN_Value(PortD_Num,PIN_6,HIGH);
		DIO_Set_PIN_Value(PortD_Num,PIN_7,LOW);
		_delay_ms(1000);
		flag=0;
	}
}


