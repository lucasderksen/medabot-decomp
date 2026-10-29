#include "continued_commands.h"
#include "continued_callbacks.h"
#include "continued_graphics.h"

extern u8 gUnknown_030057E0[];

void sub_0804AB60(void)
{
    u8 *work = gUnknown_030057E0;
    u32 offset = 0xC5C;
    u8 *selected = work + offset;
    u32 previous = *selected;
    u32 value;
    if (previous != 1)
    {
        work[0xC69] = previous;
        value = 1;
    }
    else
        value = work[0xC69];
    *selected = value;
    sub_08051E38(0);
    sub_0804842C(7, 0);
    sub_0804A210();
}

void sub_0804ABCC(void)
{
    u8 *work = gUnknown_030057E0;
    u32 offset = 0xC5C;
    u8 *selected = work + offset;
    u32 previous = *selected;
    u32 value;
    if (previous != 2)
    {
        work[0xC69] = previous;
        value = 2;
    }
    else
        value = work[0xC69];
    *selected = value;
    sub_08051E38(0);
    sub_0804842C(8, 0);
    sub_0804A210();
}

void sub_0804AD68(void)
{
    if (sub_08049E08(0))
    {
        u8 *work = gUnknown_030057E0;
        u32 offset;
        u16 x, y;
        work[0xC5C] = 11;
        sub_08051E38(0);
        offset = 0xC52;
        x = *(u16 *)(work + offset);
        offset = 0xC54;
        y = *(u16 *)(work + offset);
        sub_080533E4(18, x, y, 0);
        sub_0804A210();
    }
}

void sub_0804AE80(void)
{
    u8 *work = gUnknown_030057E0;
    u32 offset;
    u16 x, y;
    work[0xC5C] = 12;
    sub_08051E38(0);
    sub_0804842C(9, 0);
    offset = 0xC52;
    x = *(u16 *)(work + offset);
    offset = 0xC54;
    y = *(u16 *)(work + offset);
    sub_080533E4(14, x, y, 0);
    sub_0804A210();
}
