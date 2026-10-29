#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "input.h"
#include "render_work.h"


void sub_08010F08(void)
{
    sub_08012098();
    sub_08043CD4();
    sub_080123A0();
    sub_08012468();
    if ((u8)gNewKeys & 3)
    {
        sub_08040CD0(1, 2);
        gRenderMode = 0;
        sub_08074DE0(13);
        gUnknown_0300137C++;
    }
    else if ((u8)gNewKeys & 8)
    {
        sub_08074DE0(4);
        gUnknown_0300137C = 96;
    }
}

void sub_08010F6C(void)
{
    sub_08012098();
    sub_08043CD4();
    if (gState0TransferWork.bytes[1])
    {
        sub_0803FB0C();
        gUnknown_0300137C++;
    }
    else
        gUnknown_0300137C = 64;
}

void sub_08010FA4(void)
{
    sub_08012098();
    sub_08043CD4();
    if (sub_0803FB3C(gState0FixedMessages_083C6744[118]))
    {
        sub_080422B8(50, 1);
        gUnknown_0300137C++;
    }
}

void sub_08010FDC(void)
{
    sub_08012098();
    sub_08043CD4();
    sub_08012584();
    {
        u8 *buffer = gDebugMenuTextBuffer;
        u8 *work = gState0TransferWork.bytes;
        u32 offset = 0x16C;
        sub_08041490(buffer, *(u16 *)(work + offset), 53);
    }
    sub_0803FB0C();
    gUnknown_0300137C++;
}

void sub_08011018(void)
{
    sub_08012098();
    sub_08043CD4();
    if (sub_0803FB3C(gState0FixedMessages_083C6744[109]))
        gUnknown_0300137C++;
}

void sub_08011048(void)
{
    sub_08012098();
    sub_08043CD4();
    sub_080127DC();
    gState0TransferWork.bytes[0x186] = 0;
    gUnknown_0300137C++;
}
