/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "composite_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "gba.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"


void sub_0801A33C(const u8 *source, u32 row, u32 index);
void sub_0801A418(const u8 *source, u32 row, u32 index);

void sub_0801A33C(const u8 *source, u32 row, u32 index) {

    s32 flags;
    u32 i;
    u32 group;
    u32 root;
    struct FrameObject *object;
    struct FrameObject *anchor;

    i = 0;
    root = (u32)gFrameObjects;
    group = row * 4;
    flags = 0xC224;
    do {
        if (source[i] == 0xFE) {
            return;
        }
        object = (struct FrameObject *)(((group + index + i) << 6) + root);
        object->flags = flags;
        object->tableSelector = 0;
        anchor = (struct FrameObject *)(((group + 0x5D) << 6) + root);
        object->screenY = anchor->screenY + 4;
        object->priority = 0x90;
        object->frameAndGroup = source[i] + 0x800;
        object->commandDelay = i * 4;
        object->commandOffset = 0;
        object->scaleY = 0x40;
        object->scaleX = 0x40;
        object->palette = source[0] + 1;
        switch (source[6]) {
        case 1:
            object->screenX = anchor->screenX + i * 8;
            break;
        case 2:
            object->screenX = 0xFFFC + anchor->screenX + i * 8;
            break;
        case 3:
            object->screenX = 0xFFF8 + anchor->screenX + i * 8;
            break;
        case 4:
            object->screenX = 0xFFF4 + anchor->screenX + i * 8;
            break;
        }
    } while (++i <= 4);
}

void sub_0801A418(const u8 *source, u32 row, u32 index) {

    s32 flags;
    u32 i;
    u32 group;
    u32 root;
    struct FrameObject *object;
    struct FrameObject *anchor;

    i = 0;
    root = (u32)gFrameObjects;
    group = row * 4;
    flags = 0xC224;
    do {
        if (source[i] == 0xFE) {
            return;
        }
        object = (struct FrameObject *)(((group + index + i) << 6) + root);
        object->flags = flags;
        object->tableSelector = 0;
        anchor = (struct FrameObject *)(((group + 0x5D) << 6) + root);
        object->screenY = anchor->screenY + 4;
        object->priority = 0x90;
        object->frameAndGroup = source[i] + 0x5100;
        object->commandDelay = i * 4;
        object->commandOffset = 0;
        object->scaleY = 0x40;
        object->scaleX = 0x40;
        object->palette = 0xC;
        switch (source[6]) {
        case 1:
            object->screenX = anchor->screenX + i * 8;
            break;
        case 2:
            object->screenX = 0xFFFC + anchor->screenX + i * 8;
            break;
        case 3:
            object->screenX = 0xFFF8 + anchor->screenX + i * 8;
            break;
        case 4:
            object->screenX = 0xFFF4 + anchor->screenX + i * 8;
            break;
        }
    } while (++i <= 4);
}
