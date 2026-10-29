/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "coordinate_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "render_work.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

extern const u8 gUnknown_083AE060[];
extern u32 sub_08015924(u32);
extern u8 gCounter6ED08_03001800[];
extern u8 gUnknown_0300059A[];
extern u8 gUnknown_0300183C[];

void sub_08015960(u32 index, u32 x, u32 y);
void sub_08015A00(u32 index, u32 x, u32 y);
void sub_08016FB4(void);
void sub_08017BD0(void);
u32 sub_08018F6C(u32 side);
void sub_0801BC04(u32 selected);
void sub_08023274(void);
void sub_08023384(void);
void sub_08024488(void);
void sub_08024FC4(void);

void sub_08015960(u32 index, u32 x, u32 y) {

    u8 *parts = gUnknown_0300183C + 0x28;

    sub_08015838(index, parts);
    sub_08042E58(parts[0], parts[1], parts[2], parts[3], index, index * 4 + 0x5A, x, y,
                 sub_08015924(index), gUnknown_0300183C[0] + 2, index * 4 + 0x5A);
}

void sub_08015A00(u32 index, u32 x, u32 y) {

    u8 *parts = gUnknown_0300183C + 0x28;

    sub_08015838(index, parts);
    sub_0804305C(parts[0], parts[1], parts[2], parts[3], index, index * 4 + 0x5A, x, y,
                 sub_08015924(index), gUnknown_0300183C[0] + 2, index * 4 + 0x5A);
    gFrameObjects[index * 4 + 0x5B].flags &= 0xFDFF;
    gFrameObjects[index * 4 + 0x5C].flags &= 0xFDFF;
    gFrameObjects[index * 4 + 0x5B].angle = 0;
    gFrameObjects[index * 4 + 0x5C].angle = 0;
}

void sub_08016FB4(void) {

    u32 i;

    for (i = 0; i <= 5; i++) {
        gFrameObjects[i].scaleY += 8;
        gFrameObjects[i].scaleX += 8;
        if (gFrameObjects[i].scaleY > 0x40 - (0x90 - gFrameObjects[i].screenY) / 2) {
            gFrameObjects[i].scaleY = 0x40 - (0x90 - gFrameObjects[i].screenY) / 2;
            gFrameObjects[i].scaleX = 0x40 - (0x90 - gFrameObjects[i].screenY) / 2;
        }
    }
}

void sub_08017BD0(void) {

    sub_08040D0C(9, 13);
    if (gState0TypedWork.bytes[0x3C] == 0)
        sub_08040DB8(gUnknown_0300059A + ((gState0TypedWork.bytes[0x3D] + gState0TypedWork.bytes[0x3C] * 3) << 8), 9, 0x11, 0xE, 10, 15, 0, 0);
    else
        sub_08040DB8(gUnknown_0300059A + ((gState0TypedWork.bytes[0x3D] + gState0TypedWork.bytes[0x3C] * 3) << 8), 9, 3, 0xE, 10, 15, 0, 0);
}

u32 sub_08018F6C(u32 side) {

    u32 slot;
    u32 tries;
    u8 *buf = gSetupBuffer_03000590;
    u32 base = side << 8;
    u8 *last = &buf[base] + 0xCA;

    slot = *last ? *last : 4;
    for (tries = 0; tries <= 3; tries++) {
        u32 prev = slot - 1;
        if (buf[prev * 0x18 + base + 0x59] > 1)
            return slot;
        slot = prev;
        if (slot == 0)
            slot = 4;
    }
    return 0;
}

void sub_0801BC04(u32 selected) {

    struct FrameObject *objects = gFrameObjects;
    struct FrameObject *object;
    struct FrameObject *source;

    object = (struct FrameObject *)(((selected + 0x72) << 6) + (u8 *)objects);
    object->flags = ((gCounter6ED08_03001800[0x3C] + 2) << 10) | 0xC004;
    object->tableSelector = 0;
    source = &objects[selected * 4 + 0x5D];
    object->screenX = source->screenX;
    object->screenY = source->screenY + 8;
    object->palette = 5;
    object->priority = 1;
    object->frameAndGroup = 0xF00;
}

void sub_08023274(void) {

    u32 i;
    u32 first = sub_08032FC4(gCounter6ED08_03001800[0x87]);

    for (i = 0; i <= 2; i++) {
        if (gSetupBuffer_03000590[((first + i) << 8) + 0x40]) {
            gFrameObjects[i + 0x21].flags = 0xC624;
            gFrameObjects[i + 0x21].tableSelector = 0;
            gFrameObjects[i + 0x21].screenX = gFrameObjects[(first + i) * 4 + 0x5D].screenX;
            gFrameObjects[i + 0x21].screenY = gFrameObjects[(first + i) * 4 + 0x5D].screenY;
            gFrameObjects[i + 0x21].palette = 7;
            gFrameObjects[i + 0x21].priority = 0xF0;
            gFrameObjects[i + 0x21].scaleX = 0x40;
            gFrameObjects[i + 0x21].scaleY = 0x40;
            gFrameObjects[i + 0x21].frameAndGroup = 0x4801;
        }
    }
    gState0TypedWork.widths.word86 = 0;
    sub_08074DE0(0x2E);
    gCounter6ED08_03001800[0xAA]++;
}

void sub_08023384(void) {

    u32 i;

    for (i = 0; i <= 2; i++) {
        if (gFrameObjects[i + 0x21].flags & 0x8000) {
            gFrameObjects[i + 0x21].scaleX -= 8;
            gFrameObjects[i + 0x21].scaleY += 8;
        }
    }
    if (gFrameObjects[0x21].scaleX == 8) {
        sub_08040CD0(0x21, 3);
        gCounter6ED08_03001800[0xAA]++;
    }
}

void sub_08024488(void) {

    u32 i;

    for (i = 0; i <= 3; i++) {
        gFrameObjects[i + 0x26].flags = 0xC404;
        gFrameObjects[i + 0x26].tableSelector = 0;
        gFrameObjects[i + 0x26].screenX = gFrameObjects[gCounter6ED08_03001800[0x88] * 4 + 0x5A].screenX;
        gFrameObjects[i + 0x26].screenY = gFrameObjects[gCounter6ED08_03001800[0x88] * 4 + 0x5A].screenY + 4;
        gFrameObjects[i + 0x26].palette = 7;
        gFrameObjects[i + 0x26].priority = 0xF0;
        gFrameObjects[i + 0x26].unknown23[1] = 6;
        gFrameObjects[i + 0x26].unknown23[2] = gUnknown_083AE060[i];
        gFrameObjects[i + 0x26].frameAndGroup = 0x4D01;
    }
    gState0TypedWork.bytes[0x84] = 0;
    gCounter6ED08_03001800[0xAA]++;
}

void sub_08024FC4(void) {

    if (!(gCounter6ED08_03001800[0xF8] & 1))
        gFrameObjects[0x21].angle = (gFrameObjects[0x21].angle - 0x80) & 0x3FF;
    else
        gFrameObjects[0x21].angle = (gFrameObjects[0x21].angle + 0x80) & 0x3FF;
    if (gFrameObjects[0x21].scaleX == 0x80) {
        gCounter6ED08_03001800[0xAA]++;
    } else {
        gFrameObjects[0x21].scaleX++;
        gFrameObjects[0x21].scaleY++;
    }
}
