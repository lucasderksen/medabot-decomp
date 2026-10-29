#include "selector_helpers.h"
#include "global.h"
#include "fresh_helpers.h"
#include "post_dispatch.h"

extern u8 gUnknown_030057E0[];
extern const u8 gSelectorLookup_083D2B6B[];

u32 sub_08048960(u32 mode)
{
    u32 result;
    switch (mode)
    {
    case 0:
    {
        const u8 *table = gSelectorLookup_083D2B6B;
        u8 *work = gUnknown_030057E0;
        u32 offset = 0x7FE;
        u32 value = table[work[offset]];
        result = 2;
        if (value != 10)
        {
            result = 1;
            offset = 0xC5D;
            if (work[offset] & 0x20)
                result = 3;
        }
        break;
    }
    case 1: case 5: case 12: case 13: case 19: case 39: case 40:
    {
        u8 *work;
        u32 offset;
        result = 1;
        work = gUnknown_030057E0;
        offset = 0xC5D;
        if (work[offset] & 1)
            result = 3;
        else
        {
            u8 value;
            offset = 0xC5C;
            value = work[offset];
            if (value == 1 || value == 2)
                result = 4;
        }
        break;
    }
    default:
        result = 0;
    }
    return result;
}
