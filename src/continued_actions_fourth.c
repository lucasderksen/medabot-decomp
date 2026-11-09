#include "global.h"
#include "frame.h"
#include "continued_commands.h"
#include "post_dispatch.h"

extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_03006D20[];
extern u8 gLaterBuffer_030055A0[];
extern u32 sub_080532D4(u32 value);

void sub_0804C5E4(void)
{
    struct ObjectEntry { u16 value; u16 unknown; };
    u32 value = ReadBankedScriptByte();
    u8 *work = gUnknown_030057E0;
    u8 *initial = work + 0xC94;
    u8 *argument;
    s32 index;
    const struct ObjectEntry *objects;
    *initial = value;
    index = 0;
    objects = (const struct ObjectEntry *)gLaterBuffer_030055A0;
    argument = initial;
    do
    {
        u8 selected = index;
        if (GetScriptObjectSlot(selected) != -1)
        {
            s32 entry = GetScriptObjectSlot(selected);
            entry += 79;
            if (objects[entry].value != 0)
                sub_08052D90((u8)(GetScriptObjectSlot(selected) + 79), *argument);
        }
        index++;
    } while (index <= 3);
}
