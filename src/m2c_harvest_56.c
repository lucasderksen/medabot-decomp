/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "render_work.h"
#include "state0_next_helpers.h"


void sub_08017130(u32 value);
void sub_08017178(u32 value);

void sub_08017130(u32 value) {
    struct FrameObject *objects = gFrameObjects;
    s16 *coordinate;
    u8 *parameter;
    objects[1].flags = 0xC404;
    objects[1].tableSelector = 0;
    coordinate = &objects[1].screenX;
    *coordinate = 0x78;
    coordinate++;
    *coordinate = 0x84;
    parameter = (u8 *) coordinate + 6;
    *parameter = 0xA;
    parameter++;
    *parameter = 0xC0;
    objects[1].frameAndGroup = value * 4 + 0x61E;
}

void sub_08017178(u32 value) {
    struct FrameObject *objects = gFrameObjects;
    s16 *coordinate;
    u8 *parameter;
    objects[2].flags = 0xC404;
    objects[2].tableSelector = 0;
    coordinate = &objects[2].screenX;
    *coordinate = 0x78;
    coordinate++;
    *coordinate = 0x6C;
    parameter = (u8 *) coordinate + 6;
    *parameter = 0xA;
    parameter++;
    *parameter = 0xC0;
    objects[2].frameAndGroup = value * 4 + 0x61B;
}
