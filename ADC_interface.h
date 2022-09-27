/*
 * ADC_interface.h
 * this file contains the ADC interface u must follow the steps below to run ur ADC
 * Created on: september 4,2022
 * Author: Moamen ehab
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_


/**************************************  ADC CHANNELS ****************************************************/
#define ADC_CHANNEL_0     (0U)
#define ADC_CHANNEL_1     (1U)
#define ADC_CHANNEL_2     (2U)
#define ADC_CHANNEL_3     (3U)
#define ADC_CHANNEL_4     (4U)
#define ADC_CHANNEL_5     (5U)
#define ADC_CHANNEL_6     (6U)
#define ADC_CHANNEL_7     (7U)

/*********************************************************************************************************/
typedef struct
{
	u16 value0;
	u16 value1;
	u16 value2;
	u16 value3;
}ADCvalues ;

/*********************************************************************************************************/
/* Description: Initialization of ADC includes  defining the configurations found in the                 */
/*				"ADC_Configrations.h" file       							                             */
/*																				            	         */
/* Inputs : void														 			                     */
/* 																								         */
/* Outputs: void																	                     */

void ADC_init(void);
/*********************************************************************************************************/
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

void ADC_freeRunConversion(void *ptrTofn(ADCvalues));
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

void ADC_asyncronousConversion(u8 channel , void * ptrToFun(u8, u16)) ;
/*********************************************************************************************************/
/* Description: Initialization of ADC includes  defining the configurations found in the                 */
/*				"ADC_Configrations.h" file       							                             */
/*																				            	         */
/* Inputs : void *ptrTofn(u16*pointer)                                                                   */
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
void ADC_customizeFreeRunConversion(void *ptrTofn(u16*));

#endif /* ADC_INTERFACE_H_ */
