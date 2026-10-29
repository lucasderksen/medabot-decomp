#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "equipment_helpers.h"
#include "graphics.h"


void sub_080108FC(void)
{
    sub_08012098();
    sub_08043CD4();
    if (sub_0803FB3C(gUnknownPointers_083B5578[20]))
    {
        sub_080415E8(1, 22, 7);
        gUnknown_0300137C++;
    }
}

void sub_08010930(void)
{
    u32 result;
    sub_08012098();
    sub_08043CD4();
    result = sub_08041674();
    if (result)
    {
        if ((result >> 4) == 0)
        {
            sub_0803FB0C();
            gUnknown_0300137C++;
        }
        else
            gUnknown_0300137C = 32;
    }
}

void sub_08010968(void)
{
    sub_08012098();
    sub_08043CD4();
    if (sub_0803FB3C(gUnknownPointers_083B5578[21]))
    {
        sub_080750F0(8);
        sub_08042318(50, 1);
        gUnknown_0300137C++;
    }
}

void sub_080109A0(void)
{
    sub_08012098();
    sub_08043CD4();
    SnapshotPalettes();
    gUnknown_03000440[0x84] = 0;
    gUnknown_0300137C++;
}

void sub_080109CC(void)
{
    sub_08012098();
    sub_08043CD4();
    if (gUnknown_03000440[0x84] <= 8)
    {
        sub_0803F684(0, gUnknown_03000440[0x84] * 4, 0xFFFF);
        sub_0803F998(0, gUnknown_03000440[0x84] * 4, 0xFFFF);
        gUnknown_03000440[0x84]++;
    }
    else
        gUnknown_0300137C++;
}

void sub_08010A20(void)
{
    sub_0804253C(0, 0, 0);
    sub_0803EF8C(32, 32, 0, 0, *(volatile u16 *)0x04000008, 0);
    sub_0803EF8C(32, 32, 0, 0, *(volatile u16 *)0x0400000A, 0);
    sub_08040CD0(0, 128);
    gUnknown_0300137C++;
}

void sub_08010A7C(void)
{
    sub_080480E4();
    sub_08048830();
    sub_080497E0(64, 0x2F00, 5, 16, 16, 16, 12, 10, 0);
    gUnknown_03000440[0x84] = 0;
    gUnknown_0300137C++;
}
