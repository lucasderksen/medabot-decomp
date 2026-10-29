/*
 * sub_0804538C: not matching yet. The build assembles asm/non_matching/sub_0804538C.inc
 * in its place; the C below is the closest attempt (docs/drafts/README.md).
 */

#include "global.h"
#include "action_aux_data.h"
#include "action_scene_data.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "gba.h"
#include "graphics.h"
#include "map_object_spawns.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "render_work.h"
#include "scene_view.h"
#include "sprite_layouts.h"
#include "tile_text.h"

struct OamBits538C {
    u16 y:8;
    u16 attr0Middle:6;
    u16 shape:2;
    u16 x:9;
    u16 attr1Middle:5;
    u16 size:2;
    u16 attr2;
    u16 affine;
};

NONMATCH("asm/non_matching/sub_0804538C.inc", void sub_0804538C(struct RecordObjectWork *work, s32 yArg, s32 xArg, s32 keyArg))
{
    /* include/record_helpers.h declares full-width parameters; the draft works on halfwords. */
    u16 y = yArg;
    u16 x = xArg;
    u16 key = keyArg;
    struct OamBits538C *object;
    u32 dims;
    u32 height;
    u32 width;
    u16 row;
    u16 column;

    object = (struct OamBits538C *)work->objects;
    height = object->shape;
    width = object->size;
    dims = sub_08044E64(height << 14, width << 30);
    height = dims >> 16;
    width = dims & 0xFFFF;
    work->key = key;
    for (row = 0; row < work->rows; row++) {
        for (column = 0; column < work->columns; column++) {
            s32 sx;
            object->y = y;
            sx = (s16)x;
            object->x = sx;
            x += width;
            object++;
        }
        x -= width * work->columns;
        y += height;
    }
}
END_NONMATCH
