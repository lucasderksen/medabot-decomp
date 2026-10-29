/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sprite_layouts.h"
#include "state0_debug_menu.h"
#include "state0_work.h"
#include "tile_text.h"

struct RankEntry { u16 id; u8 difference; u8 rank; u32 score; };


void sub_0805B0D8(void);

void sub_0805B0D8(void) {

    u8 slot = ((u8 *)gMainContextPointer_03006F74)[0x19];
    s32 i;
    u8 count;
    s32 offset;
    u32 scores;
    u8 *info;

    for (i = 0; i <= 0x77; i++)
        ((struct RankEntry *)0x02040000)[i].difference = 0;
    offset = slot * 0xF0;
    for (i = 0, count = 0, info = gUnknown_0300052E, scores = 0x02040004; i <= 0x77; i++) {
        if (gObjectHalfwordBytes[offset + i * 2] > gObjectHalfwordBytes[offset + i * 2 + 1]) {
            struct RankEntry *entry = (struct RankEntry *)(count * 8 + 0x02040000);
            entry->id = i;
            entry->difference = gObjectHalfwordBytes[offset + i * 2] - gObjectHalfwordBytes[offset + i * 2 + 1];
            sub_08042B58(i, slot, info);
            entry->rank = info[3];
            *(u32 *)(count * 8 + scores) = info[0xB] * 100;
            count++;
        }
    }
    ((u8 *)gMainContextPointer_03006F74)[0x20] = count;
}
