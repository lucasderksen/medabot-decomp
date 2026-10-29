#include "global.h"
#include "frame.h"
#include "continued_commands.h"
#include "post_dispatch.h"

extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_03006D20[];
extern u8 gLaterBuffer_030055A0[];
extern u32 sub_080532D4(u32 value);

void sub_0804C364(void)
{
    u32 value = sub_0804D83C();
    u8 *work = gUnknown_030057E0;
    work[0xC94] = value;
    if ((u8)value == 1)
        work[0xC5D] = (work[0xC5D] & 0xEF) | 0x10;
    else
        work[0xC5D] = work[0xC5D] & 0xEF;
}

void sub_0804C478(void)
{
    u8 *work = gUnknown_030057E0;
    u16 *position = (u16 *)(work + 0xC8A);
    u32 previous = *position;
    u32 high, value;
    sub_0804D8CC(2);
    high = work[0xC94] << 8;
    value = work[0xC95];
    value |= high;
    *position = previous + value;
}

void sub_0804C53C(void)
{
    u8 *work;
    { u32 value = sub_0804D83C(); work = gUnknown_030057E0; work[0xC2A] = value; }
    { u32 value = sub_0804D83C(); work[0xC2F] = value; }
    { u32 value = sub_0804D83C(); work[0xC2E] = value; }
    if (sub_0804B738() == 0)
        work[0xC89] = 1;
}
