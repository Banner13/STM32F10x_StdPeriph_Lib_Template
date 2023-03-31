/* huke board api */

/* *****************************************************************************
 *  include
 * ****************************************************************************/
#include "board.h"
#include "htime.h"
/* *****************************************************************************
 *  code
 * ****************************************************************************/
static inline void HUKE_RCC_Init()
{
    RCC_DeInit();

    RCC_HSEConfig(RCC_HSE_ON);

    if (RCC_WaitForHSEStartUp() == SUCCESS)
    {
        /* Enable Prefetch Buffer */
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

        /* Flash 2 wait state */
        FLASH_SetLatency(FLASH_Latency_2);

        /* HCLK = SYSCLK */
        RCC_HCLKConfig(RCC_SYSCLK_Div1); 

        /* PCLK2 = HCLK */
        RCC_PCLK2Config(RCC_HCLK_Div1); 

        /* PCLK1 = HCLK/2 */
        RCC_PCLK1Config(RCC_HCLK_Div2);

        /* PLLCLK = 8MHz * 9 = 72 MHz */
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

        /* ADCCLK = 72MHz / 6 = 12 MHz */
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);

        /* Enable PLL */ 
        RCC_PLLCmd(ENABLE);

        /* Wait till PLL is ready */
        while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
        {
        }

        /* Select PLL as system clock source */
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

        /* Wait till PLL is used as system clock source */
        while(RCC_GetSYSCLKSource() != 0x08)
        {
        }
    }
    else
    {
        while (1);
    }

    RCC_ClocksTypeDef clocksTypeDef;
    RCC_GetClocksFreq(&clocksTypeDef);
    RCC_GetClocksFreq(&clocksTypeDef);
}

static inline void HUKE_GPIO_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 
                                | GPIO_Pin_2 | GPIO_Pin_3 
                                | GPIO_Pin_4 | GPIO_Pin_5 
                                | GPIO_Pin_6 | GPIO_Pin_7 ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOA, GPIO_InitStructure.GPIO_Pin);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOC, GPIO_InitStructure.GPIO_Pin);
}

static inline void HUKE_SPI_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef SPI_InitStruct;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);


    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    SPI_I2S_DeInit(SPI1);
    SPI_InitStruct.SPI_Direction            = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStruct.SPI_Mode                 = SPI_Mode_Master;
    SPI_InitStruct.SPI_DataSize             = SPI_DataSize_8b;
    SPI_InitStruct.SPI_CPOL                 = SPI_CPOL_Low;
    SPI_InitStruct.SPI_CPHA                 = SPI_CPHA_1Edge;
    SPI_InitStruct.SPI_NSS                  = SPI_NSS_Soft;
    SPI_InitStruct.SPI_BaudRatePrescaler    = SPI_BaudRatePrescaler_32;
    SPI_InitStruct.SPI_FirstBit             = SPI_FirstBit_MSB;
    SPI_InitStruct.SPI_CRCPolynomial        = 10;
    SPI_Init(SPI1, &SPI_InitStruct);
    SPI_Cmd(SPI1, ENABLE);
}

static inline void HUKE_SysTick_Init()
{
    if (SysTick_Config(SystemCoreClock / 1000))
    { 
        /* Capture error */ 
        while (1);
    }
}

static inline void HUKE_CRC_Init()
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);
}

static inline void HUKE_ADC_Init()
{
    ADC_InitTypeDef ADC_InitStruct;
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    ADC_DeInit(ADC1);
    ADC_InitStruct.ADC_Mode                 = ADC_Mode_Independent;
    ADC_InitStruct.ADC_ScanConvMode         = DISABLE;
    ADC_InitStruct.ADC_ContinuousConvMode   = DISABLE;
    ADC_InitStruct.ADC_ExternalTrigConv     = ADC_ExternalTrigConv_None;
    ADC_InitStruct.ADC_DataAlign            = ADC_DataAlign_Right;
    ADC_InitStruct.ADC_NbrOfChannel         = 0x01;
    ADC_Init(ADC1, &ADC_InitStruct);

    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);
     
    while(ADC_GetResetCalibrationStatus(ADC1));

    ADC_StartCalibration(ADC1);

    while(ADC_GetCalibrationStatus(ADC1));
}

void BoardInit(void)
{
    HUKE_RCC_Init();
    HUKE_GPIO_Init();
    HUKE_SPI_Init();
    HUKE_CRC_Init();
    HUKE_ADC_Init();

    HUKE_SysTick_Init();
}



