/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "render_work.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern s8 sub_08036E54(s16);
extern u8 *gUnknown_083B620C;
extern u8 *gUnknown_083B62A0;
extern u8 gUnknown_030018D2[];

void sub_080167BC(u32 value);
void sub_0802BAAC(void);
void sub_0802CA5C(void);

void sub_080167BC(u32 value) {
    struct FrameObject *objects = gFrameObjects;
    s16 *coordinate;
    u8 *parameter;
    objects[1].flags = 0xC404;
    objects[1].tableSelector = 0;
    coordinate = &objects[1].screenX;
    *coordinate = 0x78;
    coordinate++;
    *coordinate = 0x6C;
    parameter = (u8 *) coordinate + 6;
    *parameter = 0xA;
    parameter++;
    *parameter = 0xC0;
    objects[1].frameAndGroup = value * 4 + 0x604;
}

void sub_0802BAAC(void) {
    s32 found = 0;
    u32 i = 0;
    u8 *flags = gUnknown_030018D2;
    u8 **script = &gUnknown_083B62A0;
    u8 *objects = (u8 *) gFrameObjects;
    u8 *stopped = objects + 0x862;
    do {
        if (*(u8 *) (i + (u32) flags) != 0) {
            sub_08040BD8(*script, i + 0x21);
            if (*stopped == 0xFF)
                found = 1;
        }
        stopped += 0x40;
        i++;
    } while (i <= 2);
    if (found)
        gState0TransferWork.bytes[0xAA]++;
}

void sub_0802CA5C(void) {
    s32 found = 0;
    u32 i = 0;
    u8 *flags = gUnknown_030018D2;
    u8 **script = &gUnknown_083B620C;
    u8 *objects = (u8 *) gFrameObjects;
    u8 *stopped = objects + 0x862;
    do {
        if (*(u8 *) (i + (u32) flags) != 0) {
            sub_08040BD8(*script, i + 0x21);
            if (*stopped == 0xFF)
                found = 1;
        }
        stopped += 0x40;
        i++;
    } while (i <= 2);
    if (found)
        gState0TransferWork.bytes[0xAA]++;
}
