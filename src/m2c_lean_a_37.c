/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "graphics.h"
#include "input.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_inventory.h"
#include "state0_inventory_rows.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

extern void sub_0800F300(void);
extern void sub_0800F6E4(void);
extern void sub_0800F77C(void);
extern void sub_0800F7D0(void);
extern void sub_0800F844(void);
extern void sub_0800F8A0(void);
extern void sub_0800FA7C(void);

u32 sub_0800AD58(void);
s32 sub_0800FDD8(void);

u32 sub_0800AD58(void) {

    u8 up;
    u8 *value;

    up = 0x40 & (u8)gRepeatedKeys;
    if (up) {
        u32 root;
        sub_08074DE0(2);
        root = (u32)gInventoryRecords;
        value = (u8 *)((gState0TypedWork.bytes[0x46] + (gState0TypedWork.bytes[0x3D] << 6)) + 0x18 + root);
        if (*value == 0) {
            *value = 7;
        } else {
            *value -= 1;
        }
        return 1;
    }
    if (0x80 & (u8)gRepeatedKeys) {
        u32 root;
        sub_08074DE0(2);
        root = (u32)gInventoryRecords;
        value = (u8 *)((gState0TypedWork.bytes[0x46] + (gState0TypedWork.bytes[0x3D] << 6)) + 0x18 + root);
        if (*value == 7) {
            *value = 0;
        } else {
            *value += 1;
        }
        return 1;
    }
    return 0;
}

s32 sub_0800FDD8(void) {

    u16 value;
    s32 low;

    if (gState0TypedWork.bytes[0x41] <= 1)
        goto end;
    if (0x20 & (u8)gRepeatedKeys) {
        while (1) {
            if (gState0TypedWork.bytes[0x3D] == 0)
                gState0TypedWork.bytes[0x3D] = 0x77;
            else
                gState0TypedWork.bytes[0x3D]--;
            value = sub_08042114(gState0TypedWork.bytes[0x3D], gState0TypedWork.bytes[0x3E]);
            if (value == 0)
                continue;
            if (gState0TypedWork.bytes[0x3C] != 1)
                break;
            if ((value >> 8) == (low = value & 0xFF))
                continue;
            sub_08042B58(gState0TypedWork.bytes[0x3D], gState0TypedWork.bytes[0x3E], &gState0TypedWork.bytes[0x10E]);
            if (gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].unknown00[1] == gState0TypedWork.bytes[0x111])
                break;
        }
    }
    if (0x10 & (u8)gRepeatedKeys) {
        while (1) {
            if (gState0TypedWork.bytes[0x3D] == 0x77)
                gState0TypedWork.bytes[0x3D] = 0;
            else
                gState0TypedWork.bytes[0x3D]++;
            value = sub_08042114(gState0TypedWork.bytes[0x3D], gState0TypedWork.bytes[0x3E]);
            if (value == 0)
                continue;
            if (gState0TypedWork.bytes[0x3C] != 1)
                break;
            if ((value >> 8) == (low = value & 0xFF))
                continue;
            sub_08042B58(gState0TypedWork.bytes[0x3D], gState0TypedWork.bytes[0x3E], &gState0TypedWork.bytes[0x10E]);
            if (gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].unknown00[1] == gState0TypedWork.bytes[0x111])
                break;
        }
    }
    if (0x30 & (u8)gRepeatedKeys) {
        sub_08074DE0(2);
        sub_08042B58(gState0TypedWork.bytes[0x3D], gState0TypedWork.bytes[0x3E], &gState0TypedWork.bytes[0xEE]);
        sub_0800F6E4();
        sub_0800F77C();
        sub_0800F7D0();
        sub_0800F844();
        sub_0800F8A0();
        sub_0800FA7C();
        sub_0800F300();
        return 1;
    }
end:
    return 0;
}
