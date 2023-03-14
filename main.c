#include <stdio.h>
#include "stm32f10x.h"

void RccInit(void)
{
    RCC_DeInit();
    RCC_HSICmd(ENABLE);
    while(RESET == RCC_GetFlagStatus(RCC_FLAG_HSIRDY));

    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    FLASH_SetLatency(FLASH_Latency_1);

    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
    RCC_PCLK2Config(RCC_HCLK_Div1); 
    RCC_PCLK1Config(RCC_HCLK_Div2);
    RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_12);

    RCC_PLLCmd(ENABLE);
    while (RESET == RCC_GetFlagStatus(RCC_FLAG_PLLRDY));

    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    while (0x08 != RCC_GetSYSCLKSource());
}

int main(void)
{
    RccInit();
    // printf("hello huke\n");
    return 0;
}