#include <stdio.h>
#include "board.h"
#include "display.h"

int main(void)
{
    BoardInit();
    DisplayInit();

    while(1)
    {
        DisplayTest();
    }

    return 0;
}
