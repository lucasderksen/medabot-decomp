/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "battle_work.h"
#include "composite_graphics.h"
#include "continued_scene_records.h"
#include "encounter_choices.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "frame_command_data.h"
#include "frame_objects.h"
#include "graphics.h"
#include "main.h"
#include "main_callbacks.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "serial.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "state0_work.h"

extern const s16 gUnknown_083AF500[];
extern const s16 gUnknown_083AF540[];
extern const s16 gUnknown_083AF580[];
extern const s16 gUnknown_083AF5C0[];
extern const u16 gUnknown_083AF850[];
extern const u8 gUnknown_083B29EC[];

s32 sub_080366DC(s32 index, u32 path);
void sub_08038428(void);
u32 sub_080424B8(void);

s32 sub_080366DC(s32 index, u32 path) {

    s16 dx, dy;

    if (!(0x8000 & gFrameObjects[index].flags) || gFrameObjects[index].unknown23[0] == 0x10)
        return 1;
    /* No default: as in the reference, dx/dy stay unset for path > 3, which the only caller (path = gState0TransferWork.bytes[0x8B], 0..3) never passes. */
    switch (path) {
    case 0:
        {
            u32 j;
            dx = gUnknown_083AF500[j = gFrameObjects[index].unknown23[0] * 2];
            dy = gUnknown_083AF500[j + 1];
        }
        break;
    case 1:
        {
            u32 j;
            dx = gUnknown_083AF540[j = gFrameObjects[index].unknown23[0] * 2];
            dy = gUnknown_083AF540[j + 1];
        }
        break;
    case 2:
        {
            u32 j;
            dx = gUnknown_083AF580[j = gFrameObjects[index].unknown23[0] * 2];
            dy = gUnknown_083AF580[j + 1];
        }
        break;
    case 3:
        {
            u32 j;
            dx = gUnknown_083AF5C0[j = gFrameObjects[index].unknown23[0] * 2];
            dy = gUnknown_083AF5C0[j + 1];
        }
        break;
    }
    gFrameObjects[index].screenX = (gFrameObjects[index].screenX + dx) & 0x1FF;
    gFrameObjects[index].screenY = (gFrameObjects[index].screenY + dy) & 0xFF;
    gFrameObjects[index].unknown23[0]++;
    return 0;
}

void sub_08038428(void) {

    u32 phase;
    u32 index;
    struct FrameObject *f;
    u32 r;

    phase = 7 & gState0TypedWork.widths.word86;
    if (phase != 0)
        return;
    index = sub_08040D78(gState0TypedWork.bytes[0x12F] + 1, 0xA);
    sub_08040CD0(index, 1);
    { struct FrameObject *root = gFrameObjects; f = &root[index]; }
    f->flags = 0xC604;
    f->tableSelector = 0;
    f->screenX = 0x78;
    f->screenY = 0x78;
    f->scaleX = 0x40;
    f->scaleY = 0x40;
    f->angle = phase;
    f->palette = 6;
    f->priority = 0xF0;
    f->frameAndGroup = 0x7706;
    f->unknown23[6] = 2;
    f->unknown23[1] = 3;
    f->unknown23[0] = 0;
    r = sub_080424B8() & 3;
    if (!(1 & gCounter6ED08_03001800.flagsF8)) {
        u32 k;
        f->screenX = (gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX + gUnknown_083AF850[k = r * 2]) & 0x1FF;
        f->screenY = (gFrameObjects[gState0TypedWork.bytes[0x12F]].screenY + gUnknown_083AF850[k + 1]) & 0xFF;
        f->value30 = gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX + 0x10;
        f->value32 = gFrameObjects[gState0TypedWork.bytes[0x12F]].screenY + 4;
    } else {
        u32 k;
        f->screenX = (0xF0 - (gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX + gUnknown_083AF850[k = r * 2])) & 0x1FF;
        f->screenY = (gFrameObjects[gState0TypedWork.bytes[0x12F]].screenY + gUnknown_083AF850[k + 1]) & 0xFF;
        f->value30 = gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX - 0x10;
        f->value32 = gFrameObjects[gState0TypedWork.bytes[0x12F]].screenY + 6;
    }
}

u32 sub_080424B8(void) {

    u16 seed;
    u8 high;
    s32 full;
    u32 mask;

    if (gState0TypedWork.random.scripted == 0) {
        seed = gState0TypedWork.random.seed + gState0TypedWork.random.value;
        seed += 0x87 + ((((gFrameCounter << 4) + (gFrameCounter >> 4)) + 1) >> 1);
        full = seed;
        mask = 0xFF;
        gState0TypedWork.random.seed = ((full & mask) << 8) | ((high = full >> 8) ^ (full & mask));
        gState0TypedWork.random.value = high ^ full;
        return gState0TypedWork.random.value;
    }
    gState0TypedWork.random.index++;
    gState0TypedWork.random.value = gUnknown_083B29EC[gState0TypedWork.random.index];
    return gState0TypedWork.random.value;
}
