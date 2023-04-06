#include <stdio.h>
#include "board.h"
#include "aht10.h"
#include "htime.h"

#include <string.h>

int main(void)
{
    AHT10_t aht10;
    AHT10_Measure_Result result;
    static volatile int res = 0;

    BoardInit();

    InitDevice_AHT10(&aht10);

    while(1)
    {
        res = AHT10_IOCTL(&aht10, AHT10_MEASURE, NULL, 0);

        res = AHT10_IOCTL(&aht10, AHT10_GET_RESULT, (void*)&result, sizeof(result));

        DelayS(2);
    }

    return res;
}
