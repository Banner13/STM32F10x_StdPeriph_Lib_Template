
/* *****************************************************************************
 *
 *  PS4 handle driver
 *  author: huke
 *  date:   2023-3-31
 *  description: 
 * 
 * ***************************************************************************/

/* ****************************************************************************
 *  include
 * ***************************************************************************/
#include "ps4_handle.h"
#include "kalman.h"

float meaE = 5.0;

float estV_h = 2100.0;
float estE_h = 10.0;
float gain_h = 0.0;

float estV_v = 2065.0;
float estE_v = 10.0;
float gain_v = 0.0;
/* ****************************************************************************
 *  code
 * ***************************************************************************/
unsigned short GetADC_PS4(unsigned char channel)
{
    PS4_Get_ADC(channel);
}

inline unsigned short GetAverage(unsigned char channel, unsigned char times)
{
    unsigned int temp_val = 0;
    unsigned char count = 0;
/*
    float *estV , *estE, *gain;
    

    if (PS4_HOR_CHANNEL == channel)
    {
        estV = &estV_h;
        estE = &estE_h;
        gain = &gain_h;
    }
    else
    {
        estV = &estV_v;
        estE = &estE_v;
        gain = &gain_v;
    }

    while (times--)
    {
        temp_val = GetADC_PS4(channel);
        KalmanProcess(temp_val, meaE, estV , estE, gain);
    }
*/
    while (count++ < times)
    {
        temp_val += GetADC_PS4(channel);
    }
    
    return (temp_val/times);
}

PS4_t PS4_Test(void)
{
	PS4_t psAverage;

    psAverage.horizontalValue = GetAverage(PS4_HOR_CHANNEL, 1);
    psAverage.verticalValue = GetAverage(PS4_VER_CHANNEL, 1);
	return psAverage;
}