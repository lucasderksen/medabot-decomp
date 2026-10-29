/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "continued_commands.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "render_work.h"
#include "sprite_layouts.h"
#include "state0_work.h"
#include "tile_text.h"

struct ContinuedWork2400 {
    u8 unknown000[0x5DC];
    struct SelectionRecord records[64];
    u8 unknown7DC[0x47A];
    u8 cellX;
    u8 cellY;
    u8 unknownC58[0x30];
    u8 byteC88;
    u8 byteC89;
    u16 halfC8A;
    u8 unknownC8C[2];
    u16 halfC8E;
    u16 halfC90;
    u8 unknownC92[0x22];
    u8 byteCB4;
};

extern struct ContinuedWork2400 gContinuedWork_030057E0;

u32 sub_08052400(void);

u32 sub_08052400(void) {

    s32 found = 0;
    struct SelectionRecord *rec = gContinuedWork_030057E0.records;
    s32 i;

    for (i = 0; i < 64; i++) {
        if (rec->x == gContinuedWork_030057E0.cellX && (rec->y == gContinuedWork_030057E0.cellY && (rec->attributes & 0xF000) >> 12 == 8)) {
            u16 attr;
            gContinuedWork_030057E0.byteC88 = 1;
            attr = rec->attributes & 0xFFF;
            gContinuedWork_030057E0.halfC8E = attr;
            gContinuedWork_030057E0.halfC90 = attr;
            gContinuedWork_030057E0.byteC89 = 0;
            gContinuedWork_030057E0.halfC8A = 0;
            gContinuedWork_030057E0.byteCB4 = i;
            gFrameObjects[0x2F].unknown23[2] = 1;
            found = 1;
        }
        rec++;
        if (found)
            break;
    }
    return gContinuedWork_030057E0.byteC88;
}
