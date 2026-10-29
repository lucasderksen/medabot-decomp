#include "continued_map_data.h"
#include "continued_numeric.h"
#include "global.h"
#include "bg_scroll.h"
#include "later_graphics.h"
#include "continued_commands.h"
extern u32 Sqrt(u32 value);

float sub_08053360(float value)
{
    if (value == 0.0f)
        value = 1.0f;
    return value;
}

float sub_08053380(float value)
{
    if (value < 0.0f)
        return -1.0f;
    return 1.0f;
}

float sub_080533A4(float value)
{
    if (value < 0.0f)
        value *= -1.0f;
    return value;
}

double sub_080533CC(double value)
{
    s32 integer = value;
    u16 root = Sqrt((u32)integer << 3);
    return (double)(root >> 3);
}

void sub_08053464(void)
{
    u8 *base;
    double *destination;
    sub_080537D8();
    base = gLaterBuffer_03005350;
    destination = (double *)(base + 0xA4);
    *destination = (s32)*(u32 *)(base + 0x1D8) - (s16)gBgScroll1.x - 112;
    {
        double *next = destination + 1;
        *next = (s32)*(u32 *)(base + 0x1DC) - (s16)gBgScroll1.y - 80;
    }
    sub_08049714(gSetupPointer_03006D30, 0x3000);
}
