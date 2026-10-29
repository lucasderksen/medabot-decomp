#include "continued_commands.h"
#include "frame.h"

extern u8 gUnknown_030057E0[];

void sub_0805309C(void)
{
    u8 *work = gUnknown_030057E0;
    if (work[0xC76])
    {
        u16 value = *(u16 *)(work + 0xC52);
        u16 *x = (u16 *)(work + 0xC6E);
        u16 *y;
        *x = value;
        value = *(u16 *)(work + 0xC54);
        y = (u16 *)(work + 0xC70);
        *y = value;
        work[0xC72] = sub_0805273C(*x);
        work[0xC73] = sub_08052760(*y);
        { u32 address = (u32)gFrameObjects;
          u32 offset = 0xBE0;
          sub_08052E34(*(u8 *)(address + offset)); }
    }
}
