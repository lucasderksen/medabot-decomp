#include "continued_commands.h"
#include "continued_map_data.h"




u32 sub_080529AC(u32 indexWord, u32 selectorWord)
{
    u8 index = indexWord;
    u8 selector = selectorWord;
    u32 result = 0;
    switch (selector)
    {
    case 0:
    {
        u32 address = (u32)gContinuedMapDimensions_083F8900;
        u32 offset = index * 2;
        result = *(u8 *)(address + offset);
        break;
    }
    case 1:
    {
        u32 address = (u32)gContinuedMapDimensions_083F8900;
        u32 offset = index * 2;
        offset++;
        result = *(u8 *)(address + offset);
        break;
    }
    }
    return result;
}

u32 sub_080529DC(u32 unused, u32 selectorWord)
{
    u8 selector = selectorWord;
    u32 result = 0;
    switch (selector)
    {
    case 0:
    {
        const struct MapHalfwordPairs *data = gSetupPointer_03006D14;
        result = data->low0 | ((u32)data->high0 << 16);
        break;
    }
    case 1:
    {
        const struct MapHalfwordPairs *data = gSetupPointer_03006D14;
        result = data->low1 | ((u32)data->high1 << 16);
        break;
    }
    }
    return result;
}
