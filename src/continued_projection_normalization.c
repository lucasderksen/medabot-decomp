#include "global.h"
#include "gba.h"
#include "continued_commands.h"
#include "continued_numeric.h"

void sub_080539C0(float first, float second, float scale, float fourth)
{
    float *work = (float *)gLaterBuffer_03005350;
    u32 index;
    float firstA, firstB, secondA, secondB;
    float x, y, z, length;
    s32 divisor, firstInteger;
    const float *firstTable, *secondTable;
    work[0x4C / 4] = scale;
    *(s32 *)(gLaterBuffer_03005350 + 0xA0) = fourth;
    firstTable = gSecondaryFloatTable_083D6F2C;
    index = (s32)first & 0xFF;
    firstA = firstTable[index];
    work[0x50 / 4] = firstA;
    secondTable = gSecondaryFloatTable_083D732C;
    firstB = secondTable[index];
    work[0x54 / 4] = firstB;
    index = (s32)second & 0xFF;
    secondA = firstTable[index];
    work[0x58 / 4] = secondA;
    secondB = secondTable[index];
    work[0x5C / 4] = secondB;
    x = secondA * firstA;
    y = secondA * firstB;
    z = secondB;
    length = sub_080533CC(x * x + y * y + z * z);
    if (length == 0.0f)
        length = 1.0f;
    firstInteger = (s32)x;
    divisor = (s32)length;
    x = Div(firstInteger, divisor);
    y = Div((s32)y, divisor);
    z = Div((s32)z, divisor);
    work[0x40 / 4] = scale * x;
    work[0x44 / 4] = scale * y;
    work[0x48 / 4] = scale * z;
}
