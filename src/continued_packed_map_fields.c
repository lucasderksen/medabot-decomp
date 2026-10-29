#include "continued_map_data.h"
#include "continued_commands.h"


void sub_08053168(u32 indexWord)
{
    u16 index = indexWord;
    if ((index & 1) == 0)
    {
        u8 *data = gSetupPointer_030057D8;
        data += index / 2;
        *data &= 0x7F;
    }
    else
    {
        u8 *data = gSetupPointer_030057D8;
        data += index / 2;
        *data &= 0xF7;
    }
}


void sub_080531A0(u32 indexWord)
{
    u16 index = indexWord;
    if ((index & 1) == 0)
    {
        u8 *data = gSetupPointer_030057D8;
        data += index / 2;
        *data = (*data & 0x7F) | 0x80;
    }
    else
    {
        u8 *data = gSetupPointer_030057D8;
        data += index / 2;
        *data = (*data & 0xF7) | 8;
    }
}


u32 sub_080531E0(u32 indexWord)
{
    u16 index = indexWord;
    u32 result;
    u8 value;
    if (index & 1)
    {
        u8 *data = gSetupPointer_030057D8;
        data += index / 2;
        value = *data & 8;
        result = value >> 3;
    }
    else
    {
        u8 *data = gSetupPointer_030057D8;
        data += index / 2;
        value = *data & 0x80;
        result = value >> 7;
    }
    return result;
}


void sub_0805321C(u32 indexWord, u32 valueWord)
{
    u16 index = indexWord;
    u8 value = valueWord;
    if (value == 0)
        sub_08053168(index);
    else
        sub_080531A0(index);
}


void sub_08053238(u32 indexWord, u32 valueWord)
{
    u16 index = indexWord;
    u8 value = valueWord;
    if ((index & 1) == 0)
    {
        u8 *data = gSetupPointer_030057D8;
        data += index / 2;
        *data = (*data & 0x8F) | (value << 4);
    }
    else
    {
        u8 *data = gSetupPointer_030057D8;
        data += index / 2;
        *data = (*data & 0xF8) | value;
    }
}


u32 sub_080532D4(u32 indexWord)
{
    u16 index = indexWord;
    if ((index & 1) == 0)
    {
        u8 *data = gSetupPointer_030057D8;
        data += index / 2;
        return (*data & 0x70) >> 4;
    }
    else
    {
        u8 *data = gSetupPointer_030057D8;
        data += index / 2;
        return *data & 7;
    }
}
