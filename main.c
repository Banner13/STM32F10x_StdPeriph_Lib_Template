#include <stdio.h>
#include "board.h"
#include "htime.h"
#include "st7789.h"
int main(void)
{
    BoardInit();
    ST7789Init();

    while(1)
    {
        LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
        LCD_Fill(0,0,LCD_W,LCD_H,BLACK);
        LCD_Fill(0,0,LCD_W,LCD_H,BLUE);
        LCD_Fill(0,0,LCD_W,LCD_H,BRED);
        LCD_Fill(0,0,LCD_W,LCD_H,GRED);
        LCD_Fill(0,0,LCD_W,LCD_H,GBLUE);
        LCD_Fill(0,0,LCD_W,LCD_H,RED);
        LCD_Fill(0,0,LCD_W,LCD_H,MAGENTA);
        LCD_Fill(0,0,LCD_W,LCD_H,CYAN);
        LCD_Fill(0,0,LCD_W,LCD_H,YELLOW);

        // LcdDisplayTest();
    }

    return 0;
}
