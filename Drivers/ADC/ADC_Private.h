/*
 * ADC_Private.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: ORIGINAL
 */

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#define FULL_COUNT                              (255U)



#define FEATURE_ASYNC_CONVERSION                 (0U)
#define FEATURE_FREERUN_CONVERSION               (1U)
#define FEATURE_IDLE                             (2U)
#define INVALID_CH                               (8U)
#define INVALID_VALUE                          (0xFFFF)
#define LAST_CHANNEL                        (NUM_OF_CHANNELS-1)

static u16 ADC_getDigitalValue(void);
static void ADC_setResolution(void);
static void ADC_setFrequency(void);
static void ADC_setRefVoltage(void);

#endif /* ADC_PRIVATE_H_ */
