#include "global.h"
#include "continued_late_graphics.h"
#include "continued_commands.h"
#include "fresh_helpers.h"
#include "post_dispatch.h"
#include "object_numeric_helpers.h"
#include "input.h"


u32 sub_08057D80(u32 index)
{
    u32 result = 0;
    u32 available;
    s32 queried;
    switch ((s32)index)
    {
    case 0:
        {
            u32 query = sub_08047D8C(18);
            result = 1;
            if (!query) break;
        }
        queried = sub_08047F50(85);
        {
            s32 missing = -1;
            result = 2;
            if (queried == missing) break;
        }
        available = sub_08048088(0);
        result = 3;
        if (!available) break;
        {
            u32 flag = gUnknown_030057E0[0xC5D] & 2;
            result = 4;
            if (flag) break;
        }
        result = 0;
        if (gUnknown_030057E0[0xC5C] == 2) result = 5;
        break;
    case 1:
        {
            u32 query = sub_08047D8C(24);
            result = 1;
            if (!query) break;
        }
        {
            u32 flag = gUnknown_030057E0[0xC5D] & 16;
            result = 4;
            if (flag) break;
        }
        result = 0;
        if ((u8)(gUnknown_030057E0[0xC5C] - 1) <= 1) result = 5;
        break;
    case 2:
        {
            u32 query = sub_08047D8C(25);
            result = 1;
            if (!query) break;
        }
        queried = sub_08047F50(11);
        {
            s32 missing = -1;
            result = 2;
            if (queried == missing) break;
        }
        available = sub_08048088(1);
        if (gSelectorLookup_083D2B6B[gUnknown_030057E0[0x7FE]] == 10)
            available = 0;
        result = 3;
        if (!available) break;
        {
            u32 flag = gUnknown_030057E0[0xC5D] & 4;
            result = 4;
            if (flag) break;
        }
        result = 0;
        if ((u8)(gUnknown_030057E0[0xC5C] - 1) <= 1) result = 5;
        break;
    case 3:
        {
            u32 query = sub_08047D8C(38);
            result = 1;
            if (!query) break;
        }
        queried = sub_08047F50(107);
        {
            s32 missing = -1;
            result = 2;
            if (queried == missing) break;
        }
        {
            u32 flag = gUnknown_030057E0[0xC5D] & 8;
            result = 4;
            if (flag) break;
        }
        {
            u32 state = (u8)(gUnknown_030057E0[0xC5C] - 1);
            result = 5;
            if (state <= 1) break;
        }
        result = 0;
        if (sub_080524C8(gUnknown_030057E0[0xC67]) != 3) result = 6;
        break;
    }
    return result;
}
void sub_08057F1C(u32 count)
{
    gContinuedOtherWork_030057A0[0x15]++;
    if (*(u8 *)&gRepeatedKeys & KEY_UP)
    {
        u8 *work;
        u32 value;
        sub_08047BA8(2);
        work = gContinuedCommandWork_030064A0;
        work[0x65]--;
        if (work[0x65] == 255)
            work[0x65] = count - 1;
        value = gUnknownBytes_083D6118[work[0x65]];
        work[0x6D] = value;
        sub_08057FD4();
    }
    if (*(u8 *)&gRepeatedKeys & KEY_DOWN)
    {
        u8 *work;
        u32 value;
        sub_08047BA8(2);
        work = gContinuedCommandWork_030064A0;
        work[0x65]++;
        if ((s32)work[0x65] >= (s32)count)
            work[0x65] = 0;
        value = gUnknownBytes_083D6118[work[0x65]];
        work[0x6D] = value;
        sub_08057FD4();
    }
}

void sub_08057FB4(void)
{
    sub_08048888(32);
    sub_08048888(33);
    sub_08048888(34);
    sub_08048888(35);
}
