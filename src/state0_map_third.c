#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "equipment_helpers.h"
#include "interrupts.h"
#include "input.h"


void sub_08010AC8(void)
{
    if (gUnknown_03000440[0x84] <= 16)
    {
        sub_08049A6C();
        sub_0803F684(0, 32 - gUnknown_03000440[0x84] * 2, 0xFFFF);
        sub_0803F998(0, 32 - gUnknown_03000440[0x84] * 2, 0xFFFF);
        gUnknown_03000440[0x84]++;
    }
    else
    {
        gUnknownCallback_030017F0 = DummyInterruptHandler;
        sub_08044094();
    }
}

void sub_08010B24(void)
{
    sub_0803F624(gUnknown_03000490, 20, 0);
    gUnknown_03000490[0] = 2;
    gMainSubstate = 3;
    gUnknown_0300137C = 0;
}

void sub_08010B54(void)
{
    u16 *timers = gState0MapTimers_03002B84;
    u32 limit = 9999;
    sub_0801BF64(&timers[0], limit);
    if (gUnknown_03000440[0x9C] == 1)
    {
        sub_0801BF64(&timers[1], limit);
        sub_08074B88(14);
    }
    else
        sub_08074B88(15);
    gUnknown_0300137C++;
}

void sub_08010BA0(void)
{
    sub_08043CD4();
    if (gUnknown_03000440[0x9C] == 1)
        gUnknown_0300137C++;
    else
        gUnknown_0300137C = 112;
}

void sub_08010BD0(void)
{
    sub_08012098();
    sub_08043CD4();
    if (sub_0803FB3C(gState0MessagePointers_083C3B04[gState0TransferWork.bytes[0]]))
    {
        if (*(u8 *)&gNewKeys & 3)
        {
            gUnknown_03000440[0x1B] = 0;
            sub_08074DE0(13);
            gUnknown_0300137C++;
        }
    }
}

void sub_08010C28(void)
{
    sub_08012098();
    sub_08043CD4();
    if (sub_08041CD4())
    {
        sub_0803FB0C();
        gUnknown_0300137C++;
    }
}
