#include "global.h"
#include "continued_commands.h"
extern u8 gUnknown_030057E0[];

void sub_0804F110(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *state = work + 0xC93;
    switch (*state)
    {
    case 0:
        {
            s32 divisor = sub_08051940(47);
            s32 quotient = 16 / divisor;
            *(u16 *)(work + 0xC8A) = quotient;
            sub_08050124(47, (u8)((work[0xC94] << 4) | work[0xC95]), 0);
            (*state)++;
            break;
        }
    case 1:
        if (sub_0804F188(work[0xC94]))
            sub_08050290();
        break;
    }
}
