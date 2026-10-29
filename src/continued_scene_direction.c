#include "global.h"
#include "frame.h"
#include "continued_commands.h"
#include "later_graphics.h"
#include "packed_fields.h"

extern u8 gUnknown_030057E0[];

struct DirectionFrameBytes
{
    u8 unknown00[47 * 64 + 0x2A];
    u8 primary;
    u8 unknownBEB[63];
    u8 secondary;
};

void sub_08051EFC(u32 modeWord)
{
    u8 mode = modeWord;
    u8 *work = gUnknown_030057E0;
    u8 *direction = work + 0xC75;
    u8 previous = *direction;
    u8 *storedRow = work + 0xC73;
    u8 *row = work + 0xC57;
    if (*storedRow == *row)
    {
        u8 *storedColumn = work + 0xC72;
        u8 *column = work + 0xC56;
        if (*storedColumn == *column)
            work[0xC74] = 0;
        else
        {
            u8 *current;
            if (mode & 2)
            {
                s32 divisor = sub_08051940(48);
                s32 duration = 16 / divisor;
                work[0xC74] = duration;
            }
            if (*storedColumn < *column)
                *direction = 3;
            else
                *direction = 2;
            {
                u32 nextAddress = (u32)gUnknown_030057E0;
                u32 offset = 0xC75;
                current = (u8 *)(nextAddress + offset);
            }
            if (*current != previous)
            {
                sub_08052E34(*current);
                sub_08049420(48, (u8)sub_08050300(48, *current));
            }
        }
    }
    else
    {
        u8 *current;
        if (mode & 2)
        {
            s32 divisor = sub_08051940(48);
            s32 duration = 16 / divisor;
            work[0xC74] = duration;
        }
        if (*storedRow < *row)
            *direction = 1;
        else
            *direction = 0;
        {
            u32 nextAddress = (u32)gUnknown_030057E0;
            u32 offset = 0xC75;
            current = (u8 *)(nextAddress + offset);
        }
        if (*current != previous)
        {
            sub_08052E34(*current);
            sub_08049420(48, (u8)sub_08050300(48, *current));
        }
    }
    {
        struct DirectionFrameBytes *objects = (struct DirectionFrameBytes *)gFrameObjects;
        objects->secondary = objects->primary;
    }
}
