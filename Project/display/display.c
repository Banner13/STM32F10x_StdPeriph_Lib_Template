/* huke help time */

/* *****************************************************************************
 *  include
 * ****************************************************************************/
#include "st7789_api.h"
#include "GUI.h"
/* *****************************************************************************
 *  golbal variables
 * ****************************************************************************/


/* *****************************************************************************
 *  code
 * ****************************************************************************/
void DisplayInit(void)
{
    ST7789Init();
    GUI_Init();
}

void DisplayTest(void)
{
    LCD_Fill(0,0,LCD_ST7789_W,LCD_ST7789_H,WHITE);
    LCD_Fill(0,0,LCD_ST7789_W,LCD_ST7789_H,BLACK);
    GUI_SetBkColor(GUI_BLUE);
    GUI_SetColor(GUI_YELLOW);
    GUI_Clear();
    GUI_SetFont(&GUI_Font24_ASCII);
    GUI_DispStringAt("Hello Word!",0,0);
    GUI_FillRoundedRect(5,5,100,100,25);//在指定位置绘制填充的圆角矩形
    GUI_DispStringAt("huke 2023",5, 200);
}



