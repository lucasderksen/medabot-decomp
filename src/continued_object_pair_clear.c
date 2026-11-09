#include "global.h"
#include "frame.h"
#include "continued_commands.h"
#include "post_dispatch.h"
#include "object_numeric_helpers.h"

extern u8 gLaterBuffer_03006D38[];

void sub_08050554(u32 valueWord)
{
    u8 value = valueWord;
    u32 index = value & 15;
    if (value & 0xF0)
    {
        struct FrameObject *objects = gFrameObjects;
        u8 currentIndex = index;
        s32 mapped = GetScriptObjectSlot(currentIndex);
        u8 x;
        u8 y;
        mapped += 79;
        x = ConvertXToCellColumn((u16)(objects[mapped].positionX.value >> 8));
        mapped = GetScriptObjectSlot(currentIndex);
        mapped += 79;
        y = ConvertYToCellRow((u16)(objects[mapped].positionY >> 8));
        if (sub_08052C68(x, y))
            if (gLaterBuffer_03006D38[3])
                sub_08047BA8(gSetupByteLookup_083D2B66[gLaterBuffer_03006D38[3]]);
    }
    {
        u8 currentIndex = index;
        ResetFrameObjectSlot((u8)(GetScriptObjectSlot(currentIndex) + 79));
        ResetFrameObjectSlot((u8)(GetScriptObjectSlot(currentIndex) + 121));
        ClearScriptObjectSlot(currentIndex);
    }
}
