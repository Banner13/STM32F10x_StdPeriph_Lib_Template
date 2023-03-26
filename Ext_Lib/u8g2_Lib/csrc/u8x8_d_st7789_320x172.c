/*

  u8x8_d_st7789_320x172.c

  Copyright (c) 2023, hihuke@163.com
  All rights reserved.

  ST7789: 320x172 monochrome LCD
*/


#include "u8x8.h"
#include "st7789_api.h"

/*===================================================*/

static const u8x8_display_info_t u8x8_st7789_320x172_display_info =
{
  /* chip_enable_level = */ 0,
  /* chip_disable_level = */ 1,
  
  /* post_chip_enable_wait_ns = */ 20,
  /* pre_chip_disable_wait_ns = */ 20,
  /* reset_pulse_width_ms = */ 5, 	
  /* post_reset_wait_ms = */ 5, 		/**/
  /* sda_setup_time_ns = */ 20,		/* */
  /* sck_pulse_width_ns = */ 40,	/*  */
  /* sck_clock_hz = */ 4000000UL,	/* since Arduino 1.6.0, the SPI bus speed in Hz. Should be  1000000000/sck_pulse_width_ns */
  /* spi_mode = */ 0,		/* active high, rising edge */
  /* i2c_bus_clock_100kHz = */ 4,	/* 400KHz */
  /* data_setup_time_ns = */ 15,
  /* write_pulse_width_ns = */ 70,	
  /* tile_width = */ 40,
  /* tile_height = */ 20,
  /* default_x_offset = */ 0,
  /* flipmode_x_offset = */ 0,
  /* pixel_width = */ 320,
  /* pixel_height = */ 172
};

uint8_t u8x8_d_st7789_320x172(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    u8x8_tile_t* tile;
    switch(msg)
    {
    case U8X8_MSG_DISPLAY_INIT:
        ST7789Init();
        break;
    case U8X8_MSG_DISPLAY_SETUP_MEMORY:
        u8x8_d_helper_display_setup_memory(u8x8, &u8x8_st7789_320x172_display_info);
        break;
    case U8X8_MSG_DISPLAY_DRAW_TILE:
        tile = (u8x8_tile_t*)arg_ptr;
        LCD_Fill(tile->x_pos+50, tile->y_pos+50, tile->x_pos+1+50, tile->y_pos+1+50, WHITE);
        break;
    default:
      return -1;
    }
    return 0;
}
