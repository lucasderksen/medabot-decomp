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
#include "gba.h"
#include "graphics.h"
#include "later_helpers.h"
#include "link_menu.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "serial.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "sprite_layouts.h"
#include "state0_display.h"
#include "state0_work.h"
#include "tile_text.h"

struct LaterBytes { u8 b0, b1, b2, b3; };
struct LaterCmd { u8 count:6; u8 b6:2; u8 b8:7; u8 flag:1; u8 b2; u8 b3; };
struct RecordExtraA60 { u8 unknown00[0x28]; u32 slot; u32 flags; };

extern const struct LaterCmd gLaterCmdF610[][4] asm("gLaterCommands_0807F610");
extern const struct LaterCmd gLaterCmdFDB0[][4] asm("gLaterCommands_0807FDB0");
extern void sub_080465B8(struct RecordDisplayWork *work, const u32 *commands, u32 selector, s32 y, s32 x, s32 priority, u32 visible, u32 slot);

void sub_08046A60(void *unused, struct RecordDisplayWork *work, s32 index, s32 category, s32 y, s32 x, u32 priority, u32 palette, u32 flags);

void sub_08046A60(void *unused, struct RecordDisplayWork *work, s32 index, s32 category, s32 y, s32 x, u32 priority, u32 palette, u32 flags) {

    const u32 *commands;
    /* Set for categories 0-3 only; the original also reads it unset for other
       categories (its default path skips the store), so this is kept as is. */
    u16 tileBase;
    u32 slot;
    u32 bits;
    u32 visible;
    s32 k;

    commands = 0;
    slot = (u32)(0 - (flags & 2)) >> 31;
    switch (category) {
    case 0:
        commands = gLaterCommands_0807EE70[index];
        tileBase = 0x140;
        break;
    case 1:
        commands = ((const u32 (*)[4])gLaterCmdF610)[index];
        tileBase = 0x1A0;
        break;
    case 2:
        commands = ((const u32 (*)[4])gLaterCmdFDB0)[index];
        tileBase = 0x1E0;
        break;
    case 3:
        commands = gLaterCommands_08080550[index];
        tileBase = 0x220;
        break;
    }
    if (!(flags & 4)) {
        ((struct RecordExtraA60 *)gRecordDisplayExtraPointer)[slot].flags = (((struct RecordExtraA60 *)gRecordDisplayExtraPointer)[slot].flags | 1) & ~8;
        ((struct RecordExtraA60 *)gRecordDisplayExtraPointer)[slot].slot = slot;
        return;
    }
    bits = ((struct RecordExtraA60 *)gRecordDisplayExtraPointer)[slot].flags;
    visible = bits & 2;
    if (visible) {
        if (flags & 2)
            tileBase += 0x160;
        sub_08045E6C(work->source, commands, commands[0] << 26 >> 26, palette, work->data, &tileBase, slot);
        if (slot) {
            switch (category) {
            case 1:
                for (k = 0; gLaterCmdF610[index][k].count; k++) {
                    if (!gLaterCmdF610[index][k].flag)
                        sub_08046034(work->source, work->data, (const u32 *)gLaterCmdFDB0[index], gLaterCmdFDB0[index][k].count, gLaterCmdF610[index][k].count);
                }
                break;
            case 2:
                for (k = 0; gLaterCmdFDB0[index][k].count; k++) {
                    if (!gLaterCmdFDB0[index][k].flag)
                        sub_08046034(work->source, work->data, (const u32 *)gLaterCmdF610[index], gLaterCmdF610[index][k].count, gLaterCmdFDB0[index][k].count);
                }
                break;
            }
        }
        {
            u32 f = ((struct RecordExtraA60 *)gRecordDisplayExtraPointer)[slot].flags;
            f &= ~2;
            f |= 4;
            f |= 8;
            ((struct RecordExtraA60 *)gRecordDisplayExtraPointer)[slot].flags = f;
        }
    } else if (bits & 8) {
        u32 c = commands[0] << 26;
        const struct RecordAssetSet *const *sets = work->source;
        y -= (s8)sets[(s32)c >> 26 & 0x3F]->unknown04[8];
        x -= (s8)sets[(s32)(c >> 1) >> 25]->unknown04[9];
        sub_080465B8(work, commands, (u8)(c >> 26), y << 8, x << 8,
            (s16)priority, visible, slot);
    }
}
