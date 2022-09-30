/*
 * ADC_Configrations.h
 * this file contains ADC configrations and all options u can select
 * Created on: september 4,2022
 * Author: Moamen ehab
 */

#ifndef ADC_CONFIGRATIONS_H_
#define ADC_CONFIGRATIONS_H_

/*********************  ADC REF VOLTAGE CONFIG *****************************/
#define ADC_REF_VOLTAGE_5V             (0U)
#define ADC_REF_VOLTAGE_2_56V          (1U)

#define ADC_REF_VOLTAGE                (ADC_REF_VOLTAGE_5V)


/**************************************************************************/

/*********************  ADC PRESCALER CONFIG ******************************/
#define ADC_CLOCK_FREQUENCY_4000KHZ     (0U)
#define ADC_CLOCK_FREQUENCY_2000KHZ     (1U)
#define ADC_CLOCK_FREQUENCY_1000KHZ     (2U)
#define ADC_CLOCK_FREQUENCY_500KHZ      (3U)
#define ADC_CLOCK_FREQUENCY_250KHZ      (4U)
#define ADC_CLOCK_FREQUENCY_125KHZ      (5U)
#define ADC_CLOCK_FREQUENCY_62_5KHZ     (6U)

#define ADC_CLOCK_FREQUENCY             (ADC_CLOCK_FREQUENCY_1000KHZ)

/**************************************************************************/


/*********************  ADC RESOLUTION CONFIG ******************************/
#define ADC_RESOLUTION_8_BIT           (0U)
#define ADC_RESOLUTION_10_BIT          (1U)

#define ADC_RESOLUTION                 (ADC_RESOLUTION_8_BIT)



/**************************************************************************/
/***********  ADC channels for  ADC_customizefreeRunConversion ************/

#define  NUM_OF_CHANNELS                      (4U)

static u8 freeRunChannels[NUM_OF_CHANNELS]={ADC_CHANNEL_0,ADC_CHANNEL_1,ADC_CHANNEL_2,ADC_CHANNEL_3};

#endif /* ADC_CONFIGRATIONS_H_ */
