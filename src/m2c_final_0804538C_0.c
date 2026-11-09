/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "action_aux_data.h"
#include "action_scene_data.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "gba.h"
#include "graphics.h"
#include "map_object_spawns.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "render_work.h"
#include "scene_view.h"
#include "sound_work.h"
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


void sub_0804538C(struct RecordObjectWork *work, s32 yArg, s32 xArg, s32 keyArg);

void sub_0804538C(struct RecordObjectWork *work, s32 yArg, s32 xArg, s32 keyArg) {

    u16 y = yArg;
    u16 x = xArg;
    u16 key = keyArg;
    struct OamBits538C *object;
    u32 dims;
    u32 mask;
    u32 height;
    u32 width;
    u16 row;
    u32 column; /* u32 with an explicit u16 truncation keeps the inner loop small enough for loop.c to hoist 0x1FF */

    object = (struct OamBits538C *)work->objects;
    height = object->shape;
    width = object->size;
    dims = sub_08044E64(height << 14, width << 30);
    height = dims >> 16;
    mask = 0xFFFF;
    /* FAKE MATCH: nine nested do/while(0) wraps raise width's global-alloc priority above object's (r6 before r7); the separate mask keeps the and's constant out of regmove's reach */
    do { do { do { do { do { do { do { do { do {
        width = dims & mask;
    } while (0); } while (0); } while (0); } while (0); } while (0); } while (0); } while (0); } while (0); } while (0);
    work->key = key;
    for (row = 0; row < work->rows; row++) {
        /* FAKE MATCH: no-op truncation (height < 0x10000) in two wraps raises height's priority above width and object (r5) */
        do { do { height = (u16)height; } while (0); } while (0);
        /* FAKE MATCH: three wraps raise column's priority so it takes r3 before height and width are allocated */
        do { do { do { column = 0; } while (0); } while (0); } while (0);
        for (; column < work->columns; column = (u16)(column + 1)) {
            s32 sx;
            u16 w; /* hoisted by loop.c into the inner preheader: the reference's "adds r4, r6, #0" */
            object->y = y;
            sx = (s16)x;
            object->x = sx;
            w = width;
            x = w + x;
            object++;
            height = (u16)height; /* FAKE MATCH: no-op (height < 0x10000); stops gcse PRE hoisting y + height to the outer loop top */
        }
        x -= width * work->columns;
        {
            u16 h = height;
            y = h + y;
        }
    }
}
