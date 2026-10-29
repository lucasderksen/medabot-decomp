#include "continued_numeric.h"
#include "global.h"
#include "continued_commands.h"

void sub_080537D8(void)
{
    sub_080537E4();
}

void sub_080537E4(void)
{
    u32 *work = (u32 *)gLaterBuffer_03005350;
    work[0] = 240;
    work[1] = 160;
    {
        u32 zero = 0;
        work[2] = 120;
        work[3] = 80;
        sub_08053858(-120.5f, 120.5f, -80.5f, 80.5f);
        sub_0805390C(-120.5f, 120.5f, -80.5f, 80.5f);
        work[0xB4 / 4] = zero;
        work[0xB8 / 4] = zero;
    }
}

void sub_08053858(float first, float second, float third, float fourth)
{
    float *work = (float *)gLaterBuffer_03005350;
    float numerator, width, height;
    work[4] = first;
    work[5] = second;
    work[6] = third;
    work[7] = fourth;
    numerator = work[9] - work[8];
    width = second - first;
    work[12] = numerator / width;
    numerator = work[11] - work[10];
    height = fourth - third;
    work[13] = numerator / height;
    work[14] = (second * work[8] - first * work[9]) / width;
    work[15] = (fourth * work[10] - third * work[11]) / height;
}

void sub_0805390C(float first, float second, float third, float fourth)
{
    float *work = (float *)gLaterBuffer_03005350;
    float numerator, width, height;
    work[8] = first;
    work[9] = second;
    work[10] = third;
    work[11] = fourth;
    numerator = second - first;
    width = work[5] - work[4];
    work[12] = numerator / width;
    numerator = fourth - third;
    height = work[7] - work[6];
    work[13] = numerator / height;
    work[14] = (work[5] * first - work[4] * second) / width;
    work[15] = (work[7] * third - work[6] * fourth) / height;
}

