#include "state0_work.h"
#include "object_helpers.h"
#include "tile_text.h"

void sub_0800FC60(void)
{
    u8 *initialWork = gState0TypedWork.bytes;
    u8 *initialCounter = &initialWork[0x41];
    *initialCounter = 0;
    if ((u8)(initialWork[0x3C] - 2) > 1)
    {
        u32 index = 0;
        u8 *work = initialWork;
        u8 *group = &work[0x3E];
        u8 *counter = initialCounter;
        for (; index < 120; index++)
        {
            u32 value = (u16)sub_08042114((u8)index, *group);
            if (value != 0)
            {
                if (work[0x3C] != 1)
                    (*counter)++;
                else if ((u8)(value >> 8) != (value & 0xFF))
                {
                    sub_08042B58(index, *group, work + 0x10E);
                    if (gUnknownRecords_030017A0[work[0x51]].unknown00[1] == work[0x111])
                        (*counter)++;
                }
            }
        }
    }
}
