/*
 * sub_08045E6C: not matching yet. The build assembles asm/non_matching/sub_08045E6C.inc
 * in its place; the C below is the closest attempt (docs/drafts/README.md).
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "battle_work.h"
#include "composite_graphics.h"
#include "fallback_map_assets.h"
#include "frame.h"
#include "frame_command_data.h"
#include "gba.h"
#include "initialization.h"
#include "link_menu.h"
#include "main_callbacks.h"
#include "pose_channels.h"
#include "record_asset_data.h"
#include "record_helpers.h"
#include "render_work.h"
#include "state0_work.h"

extern u8 gUnknown_02030400[];
extern u8 gUnknown_02030800[];

NONMATCH("asm/non_matching/sub_08045E6C.inc", u32 sub_08045E6C(const struct RecordAssetSet *const *sets, const u32 *commands, u8 selector, u8 palette, struct RecordTileBlock *records, u16 *tileBase, u32 mode))
{
    const struct RecordAssetSet *set;
    struct RecordTileBlock *block;
    const u32 *p;
    u32 total;
    u8 visible;
    u32 size;
    s32 k;
    u8 index;

    total = 0;
    set = sets[selector];
    index = 0;
    visible = 0;
    size = 0;
    if (commands != NULL)
    {
        k = 0;
        if (*(const u8 *)commands & 0x3F)
        {
            u8 sel = selector;
            p = commands;
            while (1)
            {
                if (sel == (*p << 26 >> 26))
                {
                    {
                        u32 a = *p >> 6;
                        u8 alt = (*p & 0x8000) != 0;
                        index = (a + (mode & alt)) * 2;
                    }
                    visible = gState0TypedWork.bytes[0x96] ? 0 : *p << 17 >> 31;
                    size = 1;
                    if (k == 0 && ((const void *const *)set->entries)[index + 1] != NULL)
                    {
                        size = 0x20;
                        CpuSet(((const void *const *)set->entries)[index + 1], (void *)(((set->palette + palette) << 5) + 0x05000200), 0x10);
                        CpuSet(((const void *const *)set->entries)[index + 1], ((set->palette + palette) << 5) + gUnknown_02030400, 0x10);
                    }
                    break;
                }
                p++;
                k++;
                if (!(*(const u8 *)p & 0x3F))
                    break;
            }
        }
    }
    else
    {
        size = 1;
    }
    if (size != 0 && ((const void *const *)set->entries)[index] != NULL)
    {
        size = sub_08044D0C(((const void *const *)set->entries)[index], gUnknown_02030800);
        if (size != 0)
            CpuSet(gUnknown_02030800, (void *)((*tileBase << 5) + 0x06010000), size << 10 >> 11);
        block = &records[selector];
        { u32 sum = sub_08045D34((struct OamEntry *)block, set, palette, *tileBase) + *tileBase; *tileBase = sum; }
        if (gState0TypedWork.bytes[0x96])
            ((s8 *)block->unknown00)[1] = ((s8 *)block->unknown00)[1] & ~3;
        else
            ((s8 *)block->unknown00)[1] = (((s8 *)block->unknown00)[1] & ~3) | visible;
        total += size;
    }
    if (sets[selector]->child10)
        total += sub_08045E6C(sets, commands, sets[selector]->child10, palette, records, tileBase, mode);
    if (sets[selector]->child0F)
        total += sub_08045E6C(sets, commands, sets[selector]->child0F, palette, records, tileBase, mode);
    return total;
}
END_NONMATCH
