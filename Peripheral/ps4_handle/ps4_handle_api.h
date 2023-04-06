
/* *****************************************************************************
 *
 *  PS4 handle driver API
 *  author: huke
 *  date:   2023-3-31
 *  description: 
 * 
 * ***************************************************************************/
#ifndef PS4_HANDLE_API_H
#define PS4_HANDLE_API_H

/* ***************************************************************************
 *  include
 * **************************************************************************/
#include "htime.h"
#include "board.h"

/* *****************************************************************************
 *  User definition
 * ****************************************************************************/
#define PS4_MS_DELAY(t)             DelayMs(t)

#define PS4_HOR_CHANNEL             ADC_Channel_8
#define PS4_VER_CHANNEL             ADC_Channel_9
#define PS4_SWITCH_PIN              GPIO_Pin_9

#define PS4_Get_ADC(channel)        do { \
                                            ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_239Cycles5); \
                                            ADC_SoftwareStartConvCmd(ADC1, ENABLE);  \
                                            while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC )); \
                                            return ADC_GetConversionValue(ADC1);  \
                                    } while(0);

#define PS4_IS_PULL()                 GPIO_ReadInputDataBit(GPIOA, PS4_SWITCH_PIN)

/* *****************************************************************************
 *  public definition
 * ****************************************************************************/
typedef struct {
    unsigned short horizontalValue;
    unsigned short verticalValue;
}PS4_t;

/* *****************************************************************************
 *  public prototye
 * ****************************************************************************/
PS4_t PS4_Test(void);
#endif  // PS4_HANDLE_API_H



