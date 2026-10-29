#include "global.h"
#include "continued_map_data.h"
#include "compression.h"
#include "continued_commands.h"

extern u8 gUnknown_030057E0[];

void sub_080528F8(u32 indexWord)
{
    u8 index = indexWord;
    u8 *work;
    LZ77UnCompVram(gContinuedMapData_083F9080[index][0], gSetupPointer_03006D14);
    work = gUnknown_030057E0;
    if ((sub_080529AC(work[0x7FE], 0) >> 1) <= 14)
    {
        s32 value = (15 - (sub_080529AC(index, 0) >> 1)) * 8;
        *(u16 *)(work + 0xC48) = value;
    }
    else
        *(u16 *)(work + 0xC48) = 0;
    {
        u8 *next = gUnknown_030057E0;
        if ((sub_080529AC(next[0x7FE], 1) >> 1) <= 9)
        {
            s32 value = (10 - (sub_080529AC(index, 1) >> 1)) * 8;
            *(u16 *)(next + 0xC4A) = value;
        }
        else
            *(u16 *)(next + 0xC4A) = 0;
    }
}
