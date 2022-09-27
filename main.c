/* main.c
 * this file contains simple ADC application
 * Created on: september 4,2022
 * Author: Moamen ehab
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include"Std_Types.h"
#include "DIO.h"
#include "macros.h"
#include <avr/delay.h>
#include "register.h"
#include "ADC_Configrations.h"
#include "ADC_interface.h"
#include "private.h"
/* u16 myADCval;                                                                   //----------> (.bss) volatile memory
u16 myADCchannel;                                                                  //----------> (.bss) volatile memory
u8 flag ;                                                                          //----------> (.bss) volatile memory
void CallBackFunc( u8 ADCchannel , u16 ADCval )                                    //-----------> (.text) non volatile memory
{
	myADCval = ADCval ;
	myADCchannel=ADCchannel;
	flag = 1 ;
}
void main (void)
{
	ADC_init();
	myADCval = 0 ;
	myADCchannel = 0 ;
	flag = 0 ;
	while(1)
	{
	    asyncronousADC_startConversion(ADC_CHANNEL_0 ,CallBackFunc);

	    GIE_enable();

		DIO_Set_PIN_Direction(PortA_Num,PIN_0,INPUT);

		DIO_Set_PIN_Direction(PortD_Num,PIN_5,OUTPUT);
		DIO_Set_PIN_Direction(PortD_Num,PIN_6,OUTPUT);
		DIO_Set_PIN_Direction(PortD_Num,PIN_7,OUTPUT);




			if(myADCval<=50)
			{
				DIO_Set_PIN_Value(PortD_Num,PIN_5,HIGH);
				DIO_Set_PIN_Value(PortD_Num,PIN_6,LOW);
				DIO_Set_PIN_Value(PortD_Num,PIN_7,LOW);


			}
			else if (myADCval>50 && myADCval<=100)
			{

				DIO_Set_PIN_Value(PortD_Num,PIN_5,LOW);
				DIO_Set_PIN_Value(PortD_Num,PIN_6,HIGH);
				DIO_Set_PIN_Value(PortD_Num,PIN_7,LOW);
			}
			else
			{
				DIO_Set_PIN_Value(PortD_Num,PIN_5,LOW);
				DIO_Set_PIN_Value(PortD_Num,PIN_6,LOW);
				DIO_Set_PIN_Value(PortD_Num,PIN_7,HIGH);
			}
	}

}*/
/*ADCvalues myadcvalues;
flag;
void callbachfn(ADCvalues adcvalues)
{myadcvalues=adcvalues;
flag=1;
	}
void main (void)
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

		while (myadcvalues.value0==0xFFFF);
		DIO_Set_PIN_Value(PortD_Num,PIN_5,HIGH);
		DIO_Set_PIN_Value(PortD_Num,PIN_6,LOW);
		DIO_Set_PIN_Value(PortD_Num,PIN_7,LOW);
		_delay_ms(1000);
		while (myadcvalues.value1==0xFFFF);
		DIO_Set_PIN_Value(PortD_Num,PIN_5,LOW);
		DIO_Set_PIN_Value(PortD_Num,PIN_6,HIGH);
		DIO_Set_PIN_Value(PortD_Num,PIN_7,LOW);
		_delay_ms(1000);

		while (myadcvalues.value2==0xFFFF);
		DIO_Set_PIN_Value(PortD_Num,PIN_5,LOW);
		DIO_Set_PIN_Value(PortD_Num,PIN_6,LOW);
		DIO_Set_PIN_Value(PortD_Num,PIN_7,HIGH);
		_delay_ms(1000);

		while (myadcvalues.value3==0xFFFF);
		DIO_Set_PIN_Value(PortD_Num,PIN_5,LOW);
		DIO_Set_PIN_Value(PortD_Num,PIN_6,HIGH);
		DIO_Set_PIN_Value(PortD_Num,PIN_7,LOW);
		_delay_ms(1000);
		flag=0;
	}
}*/

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


			ADC_customizeFreeRunConversion(callbachfn);

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


