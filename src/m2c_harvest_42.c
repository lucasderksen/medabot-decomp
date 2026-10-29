/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "compression.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "gba.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "render_work.h"
#include "state0_debug_menu.h"
#include "state0_inventory_rows.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern const u8 *const gUnknownPointers_083B803C[];
extern s32 sub_08035960(s32, s32);

void sub_0800AAC0(void);
void sub_080205A4(void);
void sub_0802480C(void);
s32 sub_0803598C(s32 slot, s32 index, s32 value);
s32 sub_080359D8(s32 slot, s32 index, s32 value);
s32 sub_08035A24(s32 slot, s32 index, s32 value);

void sub_0800AAC0(void) {
    const u8 *const *tables = gUnknownPointers_083B803C;
    u8 *work = gState0TypedWork.bytes;
    const u8 *table = tables[work[0x43]];
    /* Observed screenX/screenY halfwords of object 6; preserve base lifetime. */
    u8 *objects = (u8 *)gFrameObjects;
    u8 *selection = work + 0x44;
    { u32 index = *selection + 1; const u8 *entry = table + index * 2; u32 coordinate = entry[0] * 8; *(u16 *)(objects + 0x182) = coordinate; }
    { u32 index = *selection + 1; u32 coordinate = table[index * 2 + 1] * 8; *(u16 *)(objects + 0x184) = coordinate; }
}

void sub_080205A4(void) {
    struct FrameObject *objects;
    u8 *work;
    u8 *row;
    u32 index;
    u32 selected;
    struct FrameObject *object;
    LeDecompress(gActionMotionAsset_084CF178, (void *)0x06014800);
    CpuFastSet(gActionMotionPalette_0850F918, (void *)0x050002E0, 8);
    objects = gFrameObjects;
    work = gState0TransferWork.bytes;
    row = &work[0x87];
    index = *row * 4;
    row += 0x20;
    selected = *row;
    selected += 90;
    index += selected;
    object = &objects[index];
    sub_08036FF8(33, object->screenX, object->screenY, 4);
    work[0xAA]++;
}

void sub_0802480C(void) {
    struct FrameObject *objects;
    u8 *work;
    u8 *row;
    u32 index;
    u32 selected;
    struct FrameObject *object;
    LeDecompress(gActionMotionAsset_084CF178, (void *)0x06014800);
    CpuFastSet(gActionMotionPalette_0850F918, (void *)0x050002E0, 8);
    objects = gFrameObjects;
    work = gState0TransferWork.bytes;
    row = &work[0x88];
    index = *row * 4;
    row += 0x48;
    selected = *row;
    selected += 90;
    index += selected;
    object = &objects[index];
    sub_08036FF8(33, object->screenX, object->screenY, 4);
    work[0xAA]++;
}

s32 sub_0803598C(s32 slot, s32 index, s32 value) {
    u8 *base = gSetupBuffer_03000590;
    s32 row = index * 24;
    s32 offset = slot << 8;
    if (((u8) (base[row + offset + 0x49] - 4) <= 1 || (base[offset + 0xD6] & 1)) && sub_08035960(value, 0x18) != 0)
        return 1;
    return 0;
}

s32 sub_080359D8(s32 slot, s32 index, s32 value) {
    u8 *base = gSetupBuffer_03000590;
    s32 row = index * 24;
    s32 offset = slot << 8;
    if (((u8) (base[row + offset + 0x49] - 6) <= 1 || (base[offset + 0xD6] & 2)) && sub_08035960(value, 0x19) != 0)
        return 1;
    return 0;
}

s32 sub_08035A24(s32 slot, s32 index, s32 value) {
    u8 *base = gSetupBuffer_03000590;
    s32 row = index * 24;
    s32 offset = slot << 8;
    if (((u8) (base[row + offset + 0x49] - 8) <= 1 || (base[offset + 0xD6] & 4)) && sub_08035960(value, 0x1A) != 0)
        return 1;
    return 0;
}
