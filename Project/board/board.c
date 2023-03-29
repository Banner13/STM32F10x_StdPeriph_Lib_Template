/* huke board api */

/* *****************************************************************************
 *  include
 * ****************************************************************************/
#include "board.h"

/* *****************************************************************************
 *  code
 * ****************************************************************************/
static inline void HUKE_RCC_Init()
{

    RCC_ClocksTypeDef clocksTypeDef;
    RCC_GetClocksFreq(&clocksTypeDef);
    RCC_GetClocksFreq(&clocksTypeDef);
    /* There is nothing to do, 
        as this is done in the bootloader's SystemInit function.
        72MHz
    */
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

void BoardInit(void)
{
    HUKE_RCC_Init();
    HUKE_GPIO_Init();
    HUKE_SPI_Init();
    HUKE_CRC_Init();

    HUKE_SysTick_Init();
}



