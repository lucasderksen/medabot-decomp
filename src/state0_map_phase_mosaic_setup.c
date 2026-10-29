#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "frame_objects.h"
#include "main.h"
#include "graphics.h"
#include "gba.h"


void sub_08014050(void)
{
    u8 *selection;
    u8 *state;
    u32 zero;
    sub_080189EC();
    selection = gState0TransferWork.bytes;
    selection += 0x84;
    zero = 0;
    *selection = 1;
    LeDecompress((const void *)0x084C9A84, (void *)0x06014800);
    CpuFastSet((const void *)0x084E4578, (void *)0x050003E0, 8);
    sub_080750F0(8);
    sub_08074DE0(110);
    state = gUnknown_03000440;
    state += 0x84;
    *state = zero;
    gUnknown_0300137C++;
}

void sub_0801425C(void)
{
    sub_08018A54();
    sub_08018AB4(0);
    sub_08018BD4();
    gUnknown_0300137C = 68;
}
