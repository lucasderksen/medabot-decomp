/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "action_scene_data.h"
#include "composite_graphics.h"
#include "continued_map_data.h"
#include "continued_scene_records.h"
#include "encoded_label_catalog.h"
#include "encoded_labels.h"
#include "encounter_choices.h"
#include "frame.h"
#include "graphics.h"
#include "later_helpers.h"
#include "object_helpers.h"
#include "part_label_banks.h"
#include "pose_channels.h"
#include "pose_durations.h"
#include "record_helpers.h"
#include "scene_view.h"
#include "sound_samples.h"
#include "sound_voice.h"
#include "sound_work.h"
#include "sprite_layouts.h"
#include "state0_display.h"
#include "state0_work.h"
#include "utility_helpers.h"

extern const u32 gUnknown_0807E8EC[];
extern u32 sub_08047428(void *data, const void *first, const void *second, const u8 *text, u32 group, u32 counter, u32 position, u32 width, u32 length);

u32 sub_08044A3C(u32 bank, u32 group, u32 index);

u32 sub_08044A3C(u32 bank, u32 group, u32 index) {

    u32 length;
    const u8 *const *text;
    u8 *counter;
    u8 *position;
    u32 zero;
    struct RecordDisplayWork *work;
    u8 *base;
    u32 done;

    group = gUnknown_0807E8EC[gActionPoseVariants_083CAD78[index] + group * 7];
    length = 0;
    {
        const u8 *const *root = gPoseDurationPointers_083D2018;
        text = &root[group];
    }
    if ((*text)[0] != 0)
    {
        const u8 *const *t = text;
        do
        {
            length++;
            if (length > 0xFE)
                break;
        } while ((*t)[length] != 0);
    }
    counter = (u8 *)0x020260CC + bank;
    {
        u32 count = *counter + 1;
        zero = 0;
        *counter = count;
    }
    work = (struct RecordDisplayWork *)0x02026000;
    base = (u8 *)0x020260CE;
    position = base + bank;
    if (*position < length)
    {
        /* Wrap: keeps the work pointer's constant set before the compare (local-alloc does not move it into a loop). */
        do { work->data = base + 2 + bank * 0x410; } while (0);
        done = sub_08047428(base + 2 + bank * 0x410, gPoseAnglePointers_083D1E40[group], gPosePositionPointers_083D1F2C[group], gPoseDurationPointers_083D2018[group], (u8)group, *counter, *position, 0x40, length);
    }
    /* done is unset when *position >= length: the reference reads a stale ip there (shipped behaviour), so the
       return value and the position/counter updates on that path depend on the caller's ip. */
    if (done)
    {
        if (++*position >= length)
        {
            *position = zero;
            *counter = zero;
            return 1;
        }
        *counter = zero;
    }
    return 0;
}
