#include <stdio.h>
#include "board.h"
#include "display.h"
#include "ps4_handle_api.h"



int main(void)
{
    BoardInit();
    DisplayInit();
    DisplayTest();

    PS4_t ps4;
    while(1)
    {
        ps4 = PS4_Test();

        GUI_DispDecAt (ps4.horizontalValue, 180, 50, 8);
        GUI_DispDecAt (ps4.verticalValue, 180, 90, 8);
    }

    return 0;
}
