#include "global.h"
#include "gba.h"
#include "frame.h"
#include "continued_commands.h"
#include "continued_numeric.h"
#include "continued_map_data.h"

struct NumericView
{
    s32 word00;
    s32 word04;
    s32 word08;
    s32 word0C;
    float float10;
    float float14;
    float float18;
    float float1C;
    float float20;
    float float24;
    float float28;
    float float2C;
    float float30;
    float float34;
    float float38;
    float float3C;
    float float40;
    float float44;
    float float48;
    float float4C;
    float float50;
    float float54;
    float float58;
    float float5C;
    u8 unknown60[0x40];
    s32 wordA0;
    u8 unknownA4[0x10];
    s32 wordB4;
    s32 wordB8;
};

void sub_08053BE0(float first, float second, float third)
{
    float firstResult, secondResult, thirdResult;
    sub_08053C7C(first, second, third, &firstResult, &secondResult, &thirdResult);
    sub_08053C00(firstResult, secondResult);
}


void sub_08053C00(float first, float second)
{
    s32 *firstResult = (s32 *)(gLaterBuffer_03005350 + 0xB4);
    sub_08053D78(first, second, firstResult, firstResult + 1);
}


void sub_08053D78(float first, float second, s32 *firstResult, s32 *secondResult)
{
    struct NumericView *work = (struct NumericView *)gLaterBuffer_03005350;
    *firstResult = (s32)work->float30 * (s32)first + (s32)work->float38 + work->word08;
    *secondResult = work->word0C - ((s32)work->float34 * (s32)second + (s32)work->float3C);
}


void sub_08053FBC(s32 first, s32 second)
{
    struct NumericView *work = (struct NumericView *)gLaterBuffer_03005350;
    work->word00 = 240;
    work->word04 = 160;
    work->word08 = first + 120;
    work->word0C = second + 80;
    sub_08053858(-120.5f, 120.5f, -80.5f, 80.5f);
    sub_0805390C(-120.5f, 120.5f, -80.5f, 80.5f);
}
