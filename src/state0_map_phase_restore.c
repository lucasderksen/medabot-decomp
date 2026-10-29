#include "render_work.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "object_helpers.h"
#include "equipment_helpers.h"
#include "utility_helpers.h"
#include "interrupts.h"
#include "display_helpers.h"
#include "gba.h"


void sub_08013824(void)
{
    u8 *work = (u8 *)0x0300047C;
    sub_0803F624(work, 20, 0);
    work[0] = 2;
    {
        u8 *buffer = gSetupBuffer_03000590;
        u8 *selection = gState0TransferWork.bytes;
        u8 *record;
        selection += 0x80;
        record = buffer + *selection * 256;
        work[1] = sub_08041D3C(record[1]) - 1;
    }
    work[5] = 1;
    work[6] = 2;
    sub_08043CA8();
    gMainSubstate = 4;
    gUnknown_0300137C = 40;
}

void sub_0801387C(void)
{
    u8 state = gUnknown_03000440[0x139];
    u8 *work = gUnknown_03000440;
    switch (state)
    {
    case 0:
    {
        u8 *cleared = work + 0x96;
        u32 zero = 0;
        *cleared = zero;
        gRenderMode = zero;
        sub_08043CA8();
        sub_08043E54();
        *(volatile u16 *)0x04000000 &= 0xF0FF;
        *(volatile u16 *)0x04000008 = 0x500;
        *(volatile u16 *)0x0400000A = 0x1901;
        *(volatile u16 *)0x0400000C = 0x1A0A;
        *(volatile u16 *)0x0400000E = 0x1B0B;
        if (sub_0801A788(0))
        {
            work[0x84] = zero;
            work[0x139]++;
        }
        break;
    }
    case 1:
    {
        u32 zero = 0;
        CpuFastSet(&zero, (void *)0x03002C30, 0x01000800);
        gUnknown_03000440[0x139]++;
        break;
    }
    case 2:
        *(volatile u16 *)0x04000000 |= 0x1F40;
        sub_080158F8();
        sub_08043F9C();
        sub_080441A8(gEquipmentAssets_083B2628[gState0TransferWork.bytes[0x38] * 5 + 1]);
        gUnknown_03000440[0x139]++;
        break;
    case 3:
        CpuFastSet((void *)0x02020800, (void *)0x06002800, 0x200);
        CpuFastSet((void *)0x02021000, (void *)0x0600C800, 0x200);
        gUnknown_03000440[0x139]++;
        break;
    case 4:
        CpuFastSet((void *)0x02021800, (void *)0x0600D000, 0x200);
        CpuFastSet((void *)0x02022000, (void *)0x0600D800, 0x200);
        gUnknown_03000440[0x139]++;
        break;
    case 5:
        CpuFastSet((void *)0x02028000, (void *)0x03002C30, 0x800);
        gUnknownCallback_030017F0 = sub_08044100;
        gUnknown_0300137C++;
        gUnknown_03000440[0x139] = 0;
        break;
    }
}
