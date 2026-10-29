/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "bg_scroll.h"
#include "continued_commands.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "graphics.h"
#include "record_helpers.h"
#include "tile_text.h"


void sub_08052204(void);

void sub_08052204(void) {

    s32 i;
    struct SelectionRecord *rec;
    u8 *base;
    u8 *p;
    u32 t;
    u32 v;
    s32 x;
    rec = gSelectionRecords_03005DBC;
    i = 0;
    base = (u8 *)rec - 0x5DC;
    do {
        p = base + 0xC92;
        if (base[0xC88] != 0) {
            x = base[0xCB4] ^ i;
            v = (u32)((0 - x) | x) >> 0x1F;
            if (*p == 0x87) {
            } else {
                goto block_5;
            }
        } else {
            v = 1;
block_5:
            if (v != 0 && ((u16)rec->attributes >> 0xC) == 6) {
                t = ((u32)(rec->flags.value << 0x1B) >> 0x1B) + 0x31;
                if (gFrameObjects[t].unknown23[1] != 0xFF) {
                    sub_08049440(t);
                }
            }
        }
        rec += 1;
        i += 1;
    } while (i <= 0x3F);
}
