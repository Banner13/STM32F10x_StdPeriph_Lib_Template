
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


/* ****************************************************************************
 *  code
 * ***************************************************************************/
unsigned short GetADC_PS4(unsigned char channel)
{
    PS4_Get_ADC(channel);
}

inline unsigned short GetAverage(unsigned char channel, unsigned char times)
{
    unsigned char t;
	unsigned int temp_val = 0;

	for(t = 0; t < times; t++)
	{
		temp_val += GetADC_PS4(channel);
		//PS4_MS_DELAY(5);
	}
	return temp_val/times;
}

PS4_t PS4_Test(void)
{
	PS4_t psAverage;

    psAverage.horizontalValue = GetAverage(PS4_HOR_CHANNEL, 100);
    psAverage.verticalValue = GetAverage(PS4_VER_CHANNEL, 100);
	return psAverage;
}