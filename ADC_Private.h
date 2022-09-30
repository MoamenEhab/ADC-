/*
 * ADC_Private.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: ORIGINAL
 */

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#define CountFull  255



#define Feature_asyncronousConversion           (1U)
#define Feature_freeRunConversion               (2U)
#define Feature_customizeFreeRunConversion      (3U)

#define INVALID_VALUE                         (0xFFFF)
#define LAST_CHANNEL                        (NUM_OF_CHANNELS-1)


static void ADC_setResolution(void);
static void ADC_setFrequency(void);
static void ADC_setRefVoltage(void);

#endif /* ADC_PRIVATE_H_ */
