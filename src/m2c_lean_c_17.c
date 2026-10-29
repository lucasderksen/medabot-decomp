/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_scene_records.h"
#include "encounter_choices.h"
#include "encounter_parts.h"
#include "frame.h"
#include "frame_objects.h"
#include "graphics.h"
#include "link_menu.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_inventory.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct ContextB22C { u8 unknown00[0x19]; u8 part; u8 unknown1A[2]; u32 total; u8 count; };
struct RecordB22C { u16 part; u8 amount; u8 frame; u32 value; };

extern u8 gUnknown_02023078;
extern void sub_0805A0CC(u16 value, s8 width, u8 x, u8 y, u8 palette, u8 block);
extern void sub_0805B188(s32 index, s32 part, s32 slot);
extern void sub_0805B530(s32 arg0, s32 arg1, s32 arg2);

void sub_0805B22C(u32 halve);

void sub_0805B22C(u32 halve) {

    s32 count = 4;
    u8 parts[count];
    u8 amounts[count];
    u8 frames[count];
    u32 values[count];
    u8 part;
    s32 i;
    u32 index;
    u32 *out;
    struct RecordB22C *record;
    u32 value;

    part = ((struct ContextB22C *)gMainContextPointer_03006F74)->part;
    index = gUnknown_02023078;
    for (i = 0, out = values, record = (struct RecordB22C *)0x02040000 + index; i < count; record++, out++, i++)
    {
        parts[i] = record->part;
        amounts[i] = record->amount;
        frames[i] = record->frame;
        value = record->value;
        *out = value;
        if (halve != 0)
            *out = value >> 1;
    }
    for (i = 0; i < count; i++)
    {
        sub_08040D0C(i * 14 + 13, 14);
        sub_0805B530(12, i * 2 + 10, 3);
        sub_0805B530(12, i * 2 + 11, 3);
        sub_08040D0C(i * 7 + 0x45, 7);
    }
    for (i = 0; i < count; i++)
    {
        if (halve == 0)
        {
            if (((struct ContextB22C *)gMainContextPointer_03006F74)->count <= i)
                goto done;
            sub_08040DB8(gPartTextPointers_083BBB4C[parts[i] * 4 + part], (u8)(i * 14 + 13), 2, i * 2 + 10, 14, 13, 1, 1);
            sub_0805A0CC(amounts[i], 2, 13, i * 2 + 10, 5, (*(volatile u16 *)0x0400000A >> 8) & 0x1F);
            gFrameObjects[0x6A + i].flags |= 0x4000;
            gFrameObjects[0x6A + i].frameAndGroup = frames[i] + 0x1B;
            gFrameObjects[0x6E + i].flags |= 0x4000;
            sub_0805B188(parts[i], part, i);
            sub_08041164(gDebugMenuTextBuffer, values[i]);
            sub_08040DB8(gDebugMenuTextBuffer, (u8)(i * 7 + 0x45), 18, i * 2 + 10, 7, 13, 2, 1);
        }
        else
        {
            if (amounts[i] == 0)
                goto done;
            sub_08040DB8(gPartTextPointers_083BBB4C[parts[i] * 4 + part], (u8)(i * 14 + 13), 2, i * 2 + 10, 14, 13, 1, 1);
            sub_0805A0CC(amounts[i], 2, 13, i * 2 + 10, 5, (*(volatile u16 *)0x0400000A >> 8) & 0x1F);
            gFrameObjects[0x6A + i].flags |= 0x4000;
            gFrameObjects[0x6A + i].frameAndGroup = frames[i] + 0x1B;
            gFrameObjects[0x6E + i].flags |= 0x4000;
            sub_0805B188(parts[i], part, i);
            sub_08041164(gDebugMenuTextBuffer, values[i]);
            sub_08040DB8(gDebugMenuTextBuffer, (u8)(i * 7 + 0x45), 18, i * 2 + 10, 7, 13, 2, 1);
        }
    }
done:
    sub_08041164(gDebugMenuTextBuffer, ((struct ContextB22C *)gMainContextPointer_03006F74)->total);
    sub_08040DB8(gDebugMenuTextBuffer, 0x61, 19, 5, 7, 12, 2, 0);
}
