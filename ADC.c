/*
 * ADC.c
 * this file contains the impelemntation of ADC functions and how it works
 * Created on: september 4,2022
 * Author: Moamen ehab
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include"Std_Types.h"
#include "DIO.h"
#include "macros.h"
#include "register.h"
#include "ADC_interface.h"
#include "ADC_Private.h"
#include "ADC_Configrations.h"

/*************************global variable used to check the ADC feature selected *************************/
static u8 Feature ;

/***************global struct that will carry digital values of the ADC channels selected*****************/
static ADCvalues ADCvals;

/*************************pointer to callbackFunc that user will create***********************************/
void (*ptrTocallbkfn)(ADCvalues);

/*************************global var that will carry the ADC digital value********************************/
static u16 digitalVal ;

/*************************global var that will carry the ADC channel number*******************************/
static u8 ADC_channel ;

/*************************pointer to callbackFunc that user will create***********************************/
void (*ptrToCallBackFun) (u8 channel , u16 val);

/*************************pointer to callbackFunc that user will create***********************************/
void (*ptrTofunction)(u16 *pointer)  ;

/*****************global var that will carry the current state of the ADC channels selected***************/
static u8 Current_CH ;

/* Description: Initialization of ADC includes  defining the configurations found in the                 */
/*				"ADC_Configrations.h" file       							                             */
/*																				            	         */
/* Inputs : void														 			                     */
/* 																								         */
/* Outputs: void																	                     */

void ADC_init(void)
{
	digitalVal=0 ;

	ADCvals.value0=INVALID_VALUE;
	ADCvals.value1=INVALID_VALUE;
	ADCvals.value2=INVALID_VALUE;
	ADCvals.value3=INVALID_VALUE;

/*********************************** Set ADC REF VOLTAGE**************************************************/
	ADC_setRefVoltage();
/**************************************** Set ADC CLOCK FREQ**********************************************/
	ADC_setFrequency();
/***************************************** Set ADC Resolution*********************************************/
	ADC_setResolution();
/**************************************  ADC Enable  *****************************************************/
bitset(ADCSRA,ADEN);

}
/*********************************************************************************************************/
/* Description: starting ADC conversion by selecting the channel found in "ADC_interface.h" file         */
/*				and return digital value to use in ur application                                        */
/*																				            	         */
/* Inputs : Channel , *ptr_TodigitalVal                                                                  */
/*          u should pass the channel u selected in "ADC_interface.h" as input argument to enable ADC    */
/*  	    on this channel . then create variable &pass the address of the var to the pointer input     */
/*          argument to make the variable represents the ADC digital value                               */
/*            									 			                                             */
/* 																								         */
/* Outputs: return of this function will be the error state if there is any error occur during the       */
/* conversion process the error state will be StatusNotOk , if not the error state will be StatusOk      */
/* so please check the error states first , digital value will be passed to the function  by address     */

error ADC_syncronousStartConversion(u8 channel , u16 * ptr_TodigitalVal)
{

/**********************************initialize of error Counter********************************************/
  u8 timeout = CountFull ;

/**********************************initialize of error status*********************************************/
  error ErrorStatus ;

/********************************* Set channel to be converted********************************************/
  ADMUX |= channel;

/************************************** Start Conversion *************************************************/
  bitset(ADCSRA,ADSC);

/******************************************* Wait on the conversion flag *********************************/

  /*	for(u8 timeout =0 ;timeout <= 255;timeout++)
	{
		if(Git_bit(ADCSRA,ADIF))
		{
			break ;
		}

	}*/

  while ( (Git_bit(ADCSRA,ADIF)==0) && (timeout>0) )
  {
	  timeout-- ;
  }

  /********************************** timeout=0 ->error **************************************************/
  if(timeout)
  {
	  /**************************** no error situation ***************************************************/
	  /**************************** Return "digital value" ***********************************************/
	  switch (ADC_RESOLUTION)
	  {

	  case ADC_RESOLUTION_8_BIT :
		  * ptr_TodigitalVal=ADCH;
		  break;

	  case ADC_RESOLUTION_10_BIT :
		  * ptr_TodigitalVal=ADCL | (ADCH<<8);
		  break;

	  default :
		  * ptr_TodigitalVal=ADCH;
		  break;

	  }

	  ErrorStatus=StatusOk ;
  }


  else
  {
	  /****************************** error situation ***************************************************/
	  ErrorStatus=StatusNotOk ;
  }

  return ErrorStatus ;

}

/*********************************************************************************************************/
/*********************************************************************************************************/
/* Description: Initialization of ADC includes  defining the configurations found in the                 */
/*				"ADC_Configrations.h" file       							                             */
/*																				            	         */
/* Inputs : void (*ptrTofunction)(u16 *p)                                                                */
/*          u r responsible to create global pointer of u16 data type. then create call back function    */
/*          returns void and takes u16*pointer as input argument . in the body of the function assign    */
/*          the value of the input pointer to the global pointer u create                                */
/*          the global pointer now carry ur  digital values of the  ADC channels u selected              */
/*          this function will be passed to  ADC_customizeFreeRunConversion function as input argument   */
/*          Example :                                                                                    */
/*          u16* mypointer;                                                                              */
/*          void callbachfn(u16*pointer)                                                                 */
/*          {mypointer=pointer;}                                                                         */
/* 																								         */
/* Outputs: void	                                                                                     */
void ADC_customizeFreeRunConversion(void *ptrTofn(u16 *p))
{
	Current_CH=0;
	Feature=Feature_customizeFreeRunConversion;
	ptrTofunction = ptrTofn;
/********************************* Set channel to be converted********************************************/
	ADMUX |= Digitalvals[Current_CH];
/******************************* enable of ADC interrupt (PIE)********************************************/
	bitset(ADCSRA,ADIE);
/************************************** Start Conversion *************************************************/
	bitset(ADCSRA,ADSC);

}

/*********************************************************************************************************/
/* Description: Initialization of ADC includes  defining the configurations found in the                 */
/*				"ADC_Configrations.h" file       							                             */
/*																				            	         */
/* Inputs : void *ptrTofn(ADCvalues)                                                                     */
/*          u r responsible to create global object of'ADCvalues' struct data type. then create function */
/*          returns void and takes object of 'ADCvalues' struct data type as input argument in the       */
/*          body of the function assign the value of the input object to the global object u created     */
/*          the global object now carry ur 4 digital values of the four ADC channels u select            */
/*          this function will be passed to  ADC_FreeR function as input argument	                     */
/*          Example :                                                                                    */
/*          ADCvalues myadcvalues;                                                                       */
/*          void callbachfn(ADCvalues adcvalues)                                                         */
/*          {myadcvalues=adcvalues;}                                                                     */
/* 																								         */
/* Outputs: void	                                                                                     */
void ADC_freeRunConversion(void *ptrTofn(ADCvalues))
{
	Feature=Feature_freeRunConversion;
	ptrTocallbkfn = ptrTofn;
	ADC_channel=CONVERSION_CHANNEL_0;
/********************************* Set channel to be converted********************************************/
	ADMUX |= CONVERSION_CHANNEL_0;
/******************************* enable of ADC interrupt (PIE)********************************************/
    bitset(ADCSRA,ADIE);
/************************************** Start Conversion *************************************************/
	bitset(ADCSRA,ADSC);

}
/*********************************************************************************************************/

/*********************************************************************************************************/
/* Description: starting ADC conversion by selecting the channel found in "ADC_interface.h" file         */
/*				and return digital value to use in ur application                                        */
/*																				            	         */
/* Inputs : Channel , void *ptrToFun(u8,u16) :                                                           */
/*  	    u should pass the channel u selected in "ADC_interface.h" as input argument to enable ADC    */
/*  	    on this channel	. then u r responsible to create u16 & u8 global vars . after that create ur */
/*  	    CallBackFunc returns void and takes u16&u8 var as input args. in the implementation of this  */
/*  	    function assign the value of this u16 var  to the global var u created before ( this global  */
/*  	    var now represents the ADC digital value ). and assign the value of the u8 var to the u8     */
/*          global var (this u8 global var now represents the ADC channel that generates the current     */
/*          digital value )  .                                                                           */
/*  	    pass the func u created as argument to asyncronousADC_startConversion function .             */
/*                                                                                                       */
/*          Example :                                                                                    */
/*          u16 myADCval;                                                                                */
/*          u16 myADCchannel;                                                                            */
/*          void CallBackFunc(u8 ADCchannel,u16 ADCval)                                                  */
/*               {                                                                                       */
/*                myADCchannel = ADCchannel;                                                             */
/*	              myADCval = ADCval ;                                                                    */
/*               }                                                                                       */
/*  	    						 			                                                         */
/* 																								         */
/* Outputs: void                                                                                         */

void asyncronousADC_startConversion(u8 channel , void * ptrToFun(u8, u16))
{Feature=Feature_asyncronousConversion;
	ptrToCallBackFun = ptrToFun ;
	ADC_channel=channel;
/********************************* Set channel to be converted********************************************/
 ADMUX |= channel;
/******************************* enable of ADC interrupt (PIE)********************************************/
 bitset(ADCSRA,ADIE);
/************************************** Start Conversion *************************************************/
 bitset(ADCSRA,ADSC);  // this bit is set to zero after conversion finished
}
/*********************************************************************************************************/

/*********************************************************************************************************/
/* Description: this function responsible to set the resolution of ADC Based on the ADC resolution       */
/*              option selected in ADC_configrations.h file                                              */
/*                                                                                                       */
/*                                                                                                       */
/*				      							                                                         */
/*																				            	         */
/* Inputs : void                                                                                         */
/*                                                                                                       */
/*                                                                                                       */
/*                                                                                                       */
/* Outputs: u16 																	                     */
/*          this function  returns u16 var that represents the current ADC digital output value          */
static u16 ADC_getDigitalValue(void);
static u16 ADC_getDigitalValue(void)
{
	u16 digitalvalue;

	switch (ADC_RESOLUTION)
	{

	case ADC_RESOLUTION_8_BIT :
		digitalvalue=ADCH;
		break;

	case ADC_RESOLUTION_10_BIT :
		digitalvalue=ADCL | (ADCH<<8);

		break;

	default :
		digitalvalue=ADCH;

		break;

	}
    return digitalvalue;
}
/*********************************************************************************************************/


ISR(ADC_vect)
{
	switch(Feature)
	{


	case Feature_asyncronousConversion :

						digitalVal= ADC_getDigitalValue();
						if (ptrToCallBackFun != NULL)
						{
						ptrToCallBackFun(ADC_channel , digitalVal);
						}
						break;


		/*************************** Return "digital value" ************************************************/

	 case Feature_freeRunConversion   :

						switch(ADC_channel)
						{
						case CONVERSION_CHANNEL_0 :
							ADCvals.value0=ADC_getDigitalValue();
							ADC_channel=CONVERSION_CHANNEL_1;
							ADMUX |= CONVERSION_CHANNEL_1;
							bitset(ADCSRA,ADIE);
							bitset(ADCSRA,ADSC);
							break;

						case CONVERSION_CHANNEL_1 :
							ADCvals.value1=ADC_getDigitalValue();
							ADC_channel=CONVERSION_CHANNEL_2;
							ADMUX |= CONVERSION_CHANNEL_2;
							bitset(ADCSRA,ADIE);
							bitset(ADCSRA,ADSC);
							break;

						case CONVERSION_CHANNEL_2 :
							ADCvals.value2=ADC_getDigitalValue();
							ADC_channel=CONVERSION_CHANNEL_3;
							ADMUX |= CONVERSION_CHANNEL_3;
							bitset(ADCSRA,ADIE);
							bitset(ADCSRA,ADSC);
							break;

						case CONVERSION_CHANNEL_3 :
							ADCvals.value3=ADC_getDigitalValue();
							if (ptrTocallbkfn != NULL)
							{
							ptrTocallbkfn(ADCvals);
							}
							bitclear(ADCSRA,ADIE);
							break;
						}
						break;

	   case Feature_customizeFreeRunConversion :

					   Digitalvals[Current_CH]=ADC_getDigitalValue();

					   if(Current_CH < LAST_CHANNEL  && Digitalvals[Current_CH+1]!=0)
					   {

						   Current_CH ++ ;

						   ADMUX |= Digitalvals[Current_CH];

						   bitset(ADCSRA,ADIE);
						   bitset(ADCSRA,ADSC);

					   }
					   else
					   {
						   if(ptrTofunction != NULL)
						   {
							   ptrTofunction(Digitalvals);
						   }
						   bitclear(ADCSRA,ADIE);
						   bitclear(ADCSRA,ADSC);
					   }


						break;
			}
}
/* Description: this function responsible to set ADC reference voltage found in the                      */
/*				"ADC_Configrations.h" file       							                             */
/*																				            	         */
/* Inputs : void														 			                     */
/* 																								         */
/* Outputs: void																	                     */
static void ADC_setRefVoltage(void)
{
	switch(ADC_REF_VOLTAGE)
		{

		case ADC_REF_VOLTAGE_5V :
			bitclear(ADMUX,REFS1);
			bitset(ADMUX,REFS0);
			break;

		case ADC_REF_VOLTAGE_2_56V:
			bitset(ADMUX,REFS0);
			bitset(ADMUX,REFS1);
			break;

		default:
			bitclear(ADMUX,REFS1);
			bitset(ADMUX,REFS0);

		}


}

/* Description: this function responsible to set ADC frequency  found in the                             */
/*				"ADC_Configrations.h" file       							                             */
/*																				            	         */
/* Inputs : void														 			                     */
/* 																								         */
/* Outputs: void																	                     */
static void ADC_setFrequency(void)
{
	switch(ADC_CLOCK_FREQUENCY)
	{

	case  ADC_CLOCK_FREQUENCY_4000KHZ :
		bitset(ADCSRA,ADPS0);
		bitclear(ADCSRA,ADPS1);
		bitclear(ADCSRA,ADPS2);
		break;

	case  ADC_CLOCK_FREQUENCY_2000KHZ :
		bitclear(ADCSRA,ADPS0);
		bitset(ADCSRA,ADPS1);
		bitclear(ADCSRA,ADPS2);
		break;

	case  ADC_CLOCK_FREQUENCY_1000KHZ :
		bitset(ADCSRA,ADPS0);
		bitset(ADCSRA,ADPS1);
		bitclear(ADCSRA,ADPS2);
		break;

	case  ADC_CLOCK_FREQUENCY_500KHZ  :
		bitclear(ADCSRA,ADPS0);
		bitclear(ADCSRA,ADPS1);
		bitset(ADCSRA,ADPS2);
		break;

	case  ADC_CLOCK_FREQUENCY_250KHZ  :
		bitset(ADCSRA,ADPS0);
		bitclear(ADCSRA,ADPS1);
		bitset(ADCSRA,ADPS2);
		break;

	case  ADC_CLOCK_FREQUENCY_125KHZ  :
		bitclear(ADCSRA,ADPS0);
		bitset(ADCSRA,ADPS1);
		bitset(ADCSRA,ADPS2);
		break;

	case  ADC_CLOCK_FREQUENCY_62_5KHZ :
		bitset(ADCSRA,ADPS0);
		bitset(ADCSRA,ADPS1);
		bitset(ADCSRA,ADPS2);
		break;

	default :
		bitclear(ADCSRA,ADPS0);
		bitset(ADCSRA,ADPS1);
		bitset(ADCSRA,ADPS2);
		break;

	}
}



/* Description: this function responsible to set ADC resolution found in the                             */
/*				"ADC_Configrations.h" file       							                             */
/*																				            	         */
/* Inputs : void														 			                     */
/* 																								         */
/* Outputs: void																	                     */
static void ADC_setResolution(void)
{
	switch(ADC_RESOLUTION)
		{

		case ADC_RESOLUTION_8_BIT :
			bitset(ADMUX,ADLAR);
			break;

		case ADC_RESOLUTION_10_BIT :
			bitclear(ADMUX,ADLAR);
			break;

		default :
			bitset(ADMUX,ADLAR);
			break;

		}

}
