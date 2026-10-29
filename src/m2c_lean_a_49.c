/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "composite_graphics.h"
#include "continued_scene_records.h"
#include "encounter_choices.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "sprite_layouts.h"
#include "state0_work.h"
#include "tile_text.h"

extern const u16 gUnknown_083AF600[];
extern const u8 *const gState0NextCommands_083B6100[];

void sub_08036C20(u32 index, s32 path, u16 x, u16 y, s32 command);

void sub_08036C20(u32 index, s32 path, u16 x, u16 y, s32 command) {

    struct FrameObject *f;
    u32 k;

    sub_08040CD0(index, 1);
    { struct FrameObject *root = gFrameObjects; f = &root[index]; }
    f->flags = 0xC404;
    f->tableSelector = 0;
    f->palette = 0xE;
    f->priority = 0x80;
    { s32 t = gUnknown_083AF600[k = path * 2] + (s16)x; f->screenX = t & 0x1FF; }
    { s32 t = gUnknown_083AF600[k + 1] + (s16)y; f->screenY = t & 0xFF; }
    sub_08040B90(gState0NextCommands_083B6100[command], index);
}
