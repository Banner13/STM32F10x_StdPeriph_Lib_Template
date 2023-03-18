/* huke help time */

/* *****************************************************************************
 *  include
 * ****************************************************************************/
#include "htime.h"

/* *****************************************************************************
 *  code
 * ****************************************************************************/
volatile uint32_t g_huke_sysTick;
static inline void SetSysTick(uint32_t t) {g_huke_sysTick = t;}
static inline uint32_t GetSysTick(void) {return g_huke_sysTick;}

void DelayMs(uint32_t t)
{
	SetSysTick(t);
	while (0 != GetSysTick()) {};
}

void Delay(uint32_t t)
{
	SetSysTick(t * 1000);
	while (0 != GetSysTick()) {};
}


