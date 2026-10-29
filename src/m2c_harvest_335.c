/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "record_helpers.h"


void sub_080723F8(void *record);

void sub_080723F8(void *record) {

    u8 *cursor = (u8 *)record + 0x61;
    u32 flags;
    u32 mask;

    *cursor = 0;
    cursor += 5;
    *cursor = 0;
    cursor -= 0x16;
    flags = *cursor;
    mask = 2;
    mask |= flags;
    *cursor = mask;
}
