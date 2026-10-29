#include "continued_commands.h"
#include "frame.h"
#include "map_object_spawns.h"

extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_03006D38[];

s32 sub_08051940(u32 inputIndex)
{
    u8 index = inputIndex;
    u32 first = gObjectFactorBytes_083D2A40[gFrameObjects[index].unknown23[7]];
    return first * gObjectFactorBytes_083D2A40[gLaterBuffer_03006D38[2]];
}

void sub_0805196C(void)
{
    gUnknown_030057E0[0xC59] = 255;
    sub_08051ED8();
}

u32 sub_08051C64(u32 input)
{
    u8 result = input;
    const u8 *cells = gObjectCellBytes_0847E40C;
    u8 *work = gUnknown_030057E0;
    u32 type = cells[work[0xC57] * (*(u16 *)(work + 0x800) / 2) + work[0xC56]] - 1;
    if (type < 4)
        result = gObjectRowBytes_083D2A43[result + type * 16];
    return result;
}

void sub_08051ED8(void)
{
    u8 *work = gUnknown_030057E0;
    if (work[0xC76])
        work[0xC75] = 255;
}
