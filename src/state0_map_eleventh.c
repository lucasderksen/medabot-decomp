#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "equipment_helpers.h"
#include "interrupts.h"
#include "input.h"
#include "render_work.h"

extern u8 gUnknown_030057E0[];

void sub_08011BB8(void)
{
    u8 *work;
    sub_08040CD0(0, 128);
    sub_08043CA8();
    sub_0803EF8C(32, 32, 0, 0, *(volatile u16 *)0x04000008, 0);
    sub_0803EF8C(32, 32, 0, 0, *(volatile u16 *)0x0400000A, 0);
    sub_0803EF8C(32, 32, 0, 0, *(volatile u16 *)0x0400000C, 0);
    sub_0803EF8C(32, 32, 0, 0, *(volatile u16 *)0x0400000E, 0);
    work = gUnknown_030057E0;
    work[0xC2D] = 0;
    work[0xC2E] = 0;
    work[0xC2F] = 0;
    gUnknownCallback_030017F0 = DummyInterruptHandler;
    sub_0804253C(3, 0x3F, 32);
    gMainState = 2;
    gMainSubstate = 8;
    gUnknown_0300137C = 0;
}

void sub_08011C88(void)
{
    u8 *cell;
    sub_08012098();
    sub_08043CD4();
    {
        u8 *work = gUnknown_030057E0;
        cell = work + 0xC2E;
    }
    if (*cell & 15)
    {
        *cell = 0;
        gUnknown_0300137C = 64;
    }
    else
    {
        u8 *records;
        u8 *work;
        u32 index;
        u32 scaled;
        u32 identifier;
        sub_080122F4(0);
        records = gSetupBuffer_03000590;
        work = gState0TransferWork.bytes;
        index = work[0x187];
        scaled = index * 256;
        identifier = records[scaled + 0x47];
        sub_080421B4(identifier, work[0x168]);
        sub_0803FB0C();
        gUnknown_0300137C++;
    }
}

void sub_08011CFC(void)
{
    sub_08012098();
    sub_08043CD4();
    sub_080123A0();
    if (sub_0803FB3C(gState0FixedMessages_083C6744[108]))
    {
        if ((u8)gNewKeys & 3)
        {
            gRenderMode = 0;
            sub_08074DE0(13);
            gUnknown_0300137C++;
        }
    }
}

void sub_08011D50(void)
{
    sub_08012098();
    sub_08043CD4();
    if (sub_080440B4())
        gUnknown_0300137C = 64;
    else
    {
        sub_0803FB0C();
        gUnknown_0300137C++;
    }
}

void sub_08011D80(void)
{
    sub_08012098();
    sub_08043CD4();
    if (sub_0803FB3C(gState0FixedMessages_083C6744[111]))
        gUnknown_0300137C = 114;
}
