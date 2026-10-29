#include "continued_commands.h"
#include "continued_scene_records.h"
#include "frame.h"

extern u8 gUnknown_030057E0[];

u32 sub_08052624(void)
{
    s32 result = -1;
    const struct CellDirectionRecord *const *tables = gCellDirectionTables_0840F880;
    u8 *work = gUnknown_030057E0;
    const struct CellDirectionRecord *source = tables[work[0x7FE]];
    s32 invalid = 0;
    u32 x = work[0xC56];
    u32 y = work[0xC57];
    switch (gFrameObjects[47].commandDelay)
    {
    case 0:
        if ((u8)y == 0) invalid = -1;
        else y--;
        break;
    case 1:
        if (y == *(u16 *)(work + 0x802) / 2 - 1) invalid = -1;
        else y++;
        break;
    case 2:
        if ((u8)x == 0) invalid = -1;
        else x--;
        break;
    case 3:
        if (x == *(u16 *)(work + 0x800) / 2 - 1) invalid = -1;
        else x++;
        break;
    }
    if (invalid == -1)
        return invalid;
    if (source->directions)
    {
        const u8 *buffer = gLaterBuffer_03003810;
        const struct CellDirectionRecord *record = source;
        while (record->directions)
        {
            if (record->x == x && record->y == y)
            {
                result = record->value;
                if (result)
                {
                    u32 allowed = record->directions;
                    switch (buffer[0])
                    {
                    case 0: if (!(allowed & 2)) result = -1; break;
                    case 1: if (!(allowed & 1)) result = -1; break;
                    case 2: if (!(allowed & 8)) result = -1; break;
                    case 3: if (!(allowed & 4)) result = -1; break;
                    }
                }
            }
            if (result != -1)
                break;
            record++;
        }
    }
    return result;
}
