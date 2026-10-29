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
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "sprite_layouts.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

extern const s16 gUnknown_083AF640[];
extern const u8 *const gState0NextCommands_083B6100[];

void sub_08036FF8(u32 index, u32 xArg, u32 yArg, u32 count) {
    u16 x = xArg;
    u16 y = yArg;

    u32 i;
    const u16 *p;
    u16 flags;
    struct FrameObject *f;
    u32 root;

    sub_08040CD0(index, count);
    i = 0;
    if (i < count) {
        p = (const u16 *)gUnknown_083AF640;
        flags = 0x4004;
    loop:
        do {
        root = (u32)gFrameObjects;
        f = (struct FrameObject *)(root + ((index + i) << 6));
        *(u16*)f = flags;
        f->tableSelector = 0;
        f->palette = 7;
        f->priority = 0xF0;
        f->unknown2C[0] = i * 8;
        { s32 t = (s16)x + p[0]; f->screenX = t & 0x1FF; }
        { s32 t = (s16)y + p[1]; f->screenY = t & 0xFF; }
        sub_08040B90(gState0NextCommands_083B6100[36], index + i);
        } while (0);
        p += 2;
        i++;
        if (i < count) goto loop;
    }
}
