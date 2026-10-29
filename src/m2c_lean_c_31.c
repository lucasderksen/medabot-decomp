/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "action_aux_data.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "map_object_spawns.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "sprite_layouts.h"
#include "tile_text.h"

struct Ctx66B4C { u8 pad00[0x1F0]; s32 matrix[4][4]; };

extern struct Ctx66B4C *gCtx66B4C asm("gMainContextPointer_03006F74");
extern void sub_08066A48(s32 (*out)[4], s32 (*a)[4], s32 (*b)[4]);

void sub_08066B4C(u32 x, u32 y, u32 z);

void sub_08066B4C(u32 x, u32 y, u32 z) {

    s32 rx[4][4] = {
        { 0x100, 0, 0, 0 },
        { 0, gAffineSineTable_080AE8F4[x + 0x40], gAffineSineTable_080AE8F4[x], 0 },
        { 0, -gAffineSineTable_080AE8F4[x], gAffineSineTable_080AE8F4[x + 0x40], 0 },
        { 0, 0, 0, 0x100 },
    };
    s32 ry[4][4] = {
        { gAffineSineTable_080AE8F4[y + 0x40], 0, -gAffineSineTable_080AE8F4[y], 0 },
        { 0, 0x100, 0, 0 },
        { gAffineSineTable_080AE8F4[y], 0, gAffineSineTable_080AE8F4[y + 0x40], 0 },
        { 0, 0, 0, 0x100 },
    };
    s32 rz[4][4] = {
        { gAffineSineTable_080AE8F4[z + 0x40], gAffineSineTable_080AE8F4[z], 0, 0 },
        { -gAffineSineTable_080AE8F4[z], gAffineSineTable_080AE8F4[z + 0x40], 0, 0 },
        { 0, 0, 0x100, 0 },
        { 0, 0, 0, 0x100 },
    };
    s32 t1[4][4];
    s32 t2[4][4];

    sub_08066A48(t1, rx, gCtx66B4C->matrix);
    sub_08066A48(t2, ry, t1);
    sub_08066A48(gCtx66B4C->matrix, rz, t2);
}
