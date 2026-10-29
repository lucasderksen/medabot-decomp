#include "state0_next_helpers.h"
#include "state0_callbacks.h"
#include "state0_work.h"
#include "display_helpers.h"
#include "render_work.h"
#include "gba.h"

void sub_08012970(void)
{
    if (sub_0803EED8() == 0)
    {
        if (gRenderMode == 2)
        {
            u32 fill = 0x200;
            CpuFastSet(&fill, gRenderWork->objects, CPU_SET_FILL | 256);
        }
        gState0MapPhaseCallbacks_083AD080[gUnknown_0300137C]();
    }
}

void sub_080129C8(void)
{
    u8 *work = gUnknown_03000440;
    work[0x139] = 0;
    work[0x13A] = 0;
    if (work[0x89] != 1)
    {
        sub_08014E7C();
        sub_08014E94();
        sub_08014EC8();
        sub_080150C0();
    }
    sub_0801528C();
    if (work[0x89] != 1)
        sub_08018A18();
    gUnknown_0300137C++;
}
