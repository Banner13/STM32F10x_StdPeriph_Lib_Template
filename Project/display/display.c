/* huke help time */

/* *****************************************************************************
 *  include
 * ****************************************************************************/
#include "u8g2.h"
#include "st7789_api.h"

/* *****************************************************************************
 *  golbal variables
 * ****************************************************************************/
static u8g2_t u8g2;

/* *****************************************************************************
 *  code
 * ****************************************************************************/
static uint8_t u8g2_gpio_and_delay_stm32(U8X8_UNUSED u8x8_t *u8x8, U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int, U8X8_UNUSED void *arg_ptr)
{
    switch(msg){
        //Initialize SPI peripheral
        case U8X8_MSG_GPIO_AND_DELAY_INIT:
            /* HAL initialization contains all what we need so we can skip this part. */
            break;

        //Function which implements a delay, arg_int contains the amount of ms
        case U8X8_MSG_DELAY_MILLI:
            ST7789_MS_DELAY(arg_int);
            break;

        //Function which delays 10us
        case U8X8_MSG_DELAY_10MICRO:
            for (uint16_t n = 0; n < 320; n++)
            {
                __NOP();
            }
            break;

        //Function which delays 100ns
        case U8X8_MSG_DELAY_100NANO:
            __NOP();
            break;

#if (!ST7789_USING_SPI)
        //Function to define the logic level of the clockline
        case U8X8_MSG_GPIO_SPI_CLOCK:
            if (arg_int) {ST7789_SCK_H;}
            else {ST7789_SCK_L;}
            break;

        //Function to define the logic level of the data line to the display
        case U8X8_MSG_GPIO_SPI_DATA:
            if (arg_int) {ST7789_SDA_H;}
            else {ST7789_SDA_L;}
            break;
#endif

        // Function to define the logic level of the CS line
        case U8X8_MSG_GPIO_CS:
            if (arg_int) {ST7789_CS_SET;}
            else {ST7789_CS_RESET;}
            break;

        //Function to define the logic level of the Data/ Command line
        case U8X8_MSG_GPIO_DC:
            if (arg_int) {ST7789_DC_SET;}
            else {ST7789_DC_RESET;}
            break;

        //Function to define the logic level of the RESET line
        case U8X8_MSG_GPIO_RESET:
            if (arg_int) {ST7789_RES_SET;}
            else {ST7789_RES_RESET;}
            break;

        default:
            return 0; //A message was received which is not implemented, return 0 to indicate an error
    }

    return 1; // command processed successfully.
}

uint8_t u8x8_byte_3wire_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{

    switch(msg)
    {
    case U8X8_MSG_BYTE_SEND:
        ST7789_SPI_Write(arg_ptr, arg_int);
        break;

    case U8X8_MSG_BYTE_SET_DC:
        break;

    case U8X8_MSG_BYTE_START_TRANSFER:
        u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_enable_level);  
        u8x8->gpio_and_delay_cb(u8x8, U8X8_MSG_DELAY_NANO, u8x8->display_info->post_chip_enable_wait_ns, NULL);
        break;

    case U8X8_MSG_BYTE_END_TRANSFER:
        u8x8->gpio_and_delay_cb(u8x8, U8X8_MSG_DELAY_NANO, u8x8->display_info->pre_chip_disable_wait_ns, NULL);
        u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_disable_level);
        break;

    default:
        return -1;
    }

    return 0;
}


void DisplayInit(void)
{
    u8g2_Setup_st7789_320x172_1(&u8g2, U8G2_R0, u8x8_byte_3wire_hw_spi, u8g2_gpio_and_delay_stm32);
    u8g2_InitDisplay(&u8g2); // send init sequence to the display, display is in sleep mode after this,
}

void DisplayTest(void)
{
    LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
    LCD_Fill(0,0,LCD_W,LCD_H,BLACK);
    u8g2_DrawLine(&u8g2, 0, 0, 160, 160);
    u8g2_SendBuffer(&u8g2);
}



