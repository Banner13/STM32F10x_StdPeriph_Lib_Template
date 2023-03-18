#include <stdio.h>
#include "board.h"
#include "htime.h"

int main(void)
{
    BoardInit();

    while(1)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_0);
        Delay(5);
        GPIO_ResetBits(GPIOA, GPIO_Pin_0);
        Delay(5);
        // LcdDisplayTest();
    }

    return 0;
}
