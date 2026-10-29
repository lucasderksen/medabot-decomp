#include "continued_commands.h"
#include "frame.h"

extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_03006D38[];
extern const u8 *const gContinuedMapEntries_08412E60[];

u32 sub_08052C68(u32 x, u32 y)
{
    u32 found = 0;
    const u8 *const *table = gContinuedMapEntries_08412E60;
    const u8 *source = table[gUnknown_030057E0[0x7FE]];
    if (source[0] != 255)
    {
        u8 *buffer = gLaterBuffer_03006D38;
        s32 mask = 0xF0;
        const u8 *record = source;
    while (record[0] != 255)
    {
        u32 recordX = record[0];
        u32 recordY = record[1];
        if (recordX == x && recordY == y)
        {
            s32 value;
            found = 1;
            value = record[3];
            value &= mask;
            buffer[3] = value >> 4;
        }
        record += 8;
    }
    }
    return found;
}


u32 sub_08052CC0(u32 directionWord)
{
    u8 direction = directionWord;
    u32 found = 0;
    switch (direction)
    {
    case 0:
        {
            u8 *work = gUnknown_030057E0;
            u32 value = *(u16 *)(work + 0xC54);
            u16 *origin = (u16 *)(work + 0xC4A);
            if (value == *origin)
                found = 1;
        }
        break;
    case 1:
        {
            u8 *work = gUnknown_030057E0;
            u32 y = *(u16 *)(work + 0xC54) - *(u16 *)(work + 0xC4A);
            if (y + 16 == *(u16 *)(work + 0x802) * 8)
                found = 1;
        }
        break;
    case 2:
        {
            u8 *work = gUnknown_030057E0;
            u32 value = *(u16 *)(work + 0xC52);
            u16 *origin = (u16 *)(work + 0xC48);
            if (value == *origin)
                found = 1;
        }
        break;
    case 3:
        {
            u8 *work = gUnknown_030057E0;
            u32 x = *(u16 *)(work + 0xC52) - *(u16 *)(work + 0xC48);
            if (x + 16 == *(u16 *)(work + 0x800) * 8)
                found = 1;
        }
        break;
    }
    if (found)
        sub_08052E0C(direction);
    return found;
}


void sub_08052D90(u32 indexWord, u32 valueWord)
{
    u8 index = indexWord;
    u8 value = valueWord;
    struct FrameObject *base = gFrameObjects;
    struct FrameObject *object = &base[index];
    object->commandDelay = value;
    object->commandOffset = value;
    switch (value)
    {
    case 0:
        object->frameAndGroup = object->byte2B * 12;
        break;
    case 1:
        object->frameAndGroup = object->byte2B * 12 + 3;
        break;
    case 2:
        object->frameAndGroup = object->byte2B * 12 + 6;
        break;
    case 3:
        object->frameAndGroup = object->byte2B * 12 + 9;
        break;
    }
}


void sub_08052E0C(u32 valueWord)
{
    u8 value = valueWord;
    u8 *work = gUnknown_030057E0;
    work[0xC67] = value;
    sub_08052D90(47, value);
    sub_08051EFC(3);
}


void sub_08052E34(u32 valueWord)
{
    u8 value = valueWord;
    u8 *work = gUnknown_030057E0;
    work[0xC83] = value;
    sub_08052D90(48, value);
}


void sub_08052E58(u32 xWord, u32 yWord, u32 value)
{
    u8 x = xWord;
    u8 y = yWord;
    u8 *work = gUnknown_030057E0;
    u32 width = *(u16 *)(work + 0x800) / 2;
    u32 offset = y * width + x;
    u8 *data = work + 0x810;
    data[offset] = value;
}
