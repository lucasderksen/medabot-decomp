#include "global.h"
#include "frame.h"
#include "continued_commands.h"
#include "packed_fields.h"
#include "later_graphics.h"

extern u8 gLaterBuffer_03006D20[];
extern u8 gUnknown_030057E0[];

u32 sub_080508B4(void)
{
    u32 result = 0;
    u8 *work = gLaterBuffer_03006D20;
    switch (work[0])
    {
    case 0:
        {
            u8 index = work[10];
            struct FrameObject *base = gFrameObjects;
            u8 frame = sub_08050300(index, base[index].commandDelay);
            sub_08049420(index, frame);
            work[0]++;
        }
        break;
    case 1:
        if (work[2])
        {
            sub_08049440(work[10]);
            work[2]--;
        }
        else
            result = 1;
        break;
    }
    return result;
}

struct QueryCommandContext
{
    u8 unknown00[0x1D4];
    u32 command;
};
#define gQueryCommandContext_03005350 (*(struct QueryCommandContext *)gLaterBuffer_03005350)

u32 sub_08050BC8(void)
{
    u32 command = gQueryCommandContext_03005350.command & 63;
    if (command == 13 || command == 22)
    {
        gUnknown_030057E0[0xC5B] = 0;
        sub_08052BEC(0);
        sub_08052B70();
    }
    if (sub_0805424C() == 4)
    {
        switch (gQueryCommandContext_03005350.command & 63)
        {
        case 0:
        case 13:
        case 15:
        case 16:
        case 19:
        case 22:
            break;
        default:
            sub_08050C94();
            break;
        }
        return 1;
    }
    return 0;
}
