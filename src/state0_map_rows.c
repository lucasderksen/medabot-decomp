#include "state0_next_helpers.h"
#include "state0_work.h"
#include "state0_callbacks.h"

void sub_08010478(void)
{
    s32 first;
    s32 i;
    if (gState0TypedWork.selection.word48 <= 4)
        first = 0;
    else
        first = gState0TypedWork.selection.word48 - 4;
    for (i = first; i <= gState0TypedWork.selection.word48; i++)
    {
        if (i <= 14)
            sub_0803EF8C(1, 20, i, 0, *(volatile u16 *)0x04000008,
                         (u16)(gState0TypedWork.selection.word48 - i + 0xD130));
    }
    for (i = first; i <= gState0TypedWork.selection.word48; i++)
    {
        if (i <= 14)
            sub_0803EF8C(1, 20, 29 - i, 0, *(volatile u16 *)0x04000008,
                         (u16)(gState0TypedWork.selection.word48 - i + 0xD130));
    }
    if (++gState0TypedWork.selection.word48 > 19)
        gUnknown_0300137C++;
}
