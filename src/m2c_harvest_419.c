/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "encounter_choices.h"
#include "frame.h"
#include "frame_command_data.h"
#include "frame_objects.h"
#include "graphics.h"
#include "object_numeric_helpers.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "sound_work.h"
#include "sprite_layouts.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"
#include "utility_helpers.h"

struct Setup185E8 {
    u8 pad00[0x40];
    u8 active40;
    u8 pad41[0xBF];
};

extern const u8 gUnknown_083AD524[];
extern s32 sub_0807CD2C(s32, s32);
extern u16 gUnknown_02020000[];
extern u8 gSetupBytes185E8[] asm("gSetupBuffer_03000590");
extern void sub_08017994(u32, u32, u32);
extern void sub_080187A8(void);

u32 sub_080185E8(void);
s32 sub_080488E8(s32 value, u8 digits);

u32 sub_080185E8(void) {

    register u32 i;
    register u32 index;
    register u32 x;
    register u8 *root;

    sub_08040D0C(4, 1);
    sub_08040D0C(5, 1);
    sub_08040D0C(6, 1);
    sub_08040D0C(7, 1);
    if (gState0TypedWork.bytes[0x3C] == 0) {
        for (i = 0, root = gSetupBytes185E8; i <= 2; i++) {
            index = gState0TypedWork.bytes[0x3C] * 3 + i;
            if (*(const u8 *)((u32)root + (index << 8) + 0x40) != 0) {
                x = *(const u8 *)((u32)gUnknown_083AD524 + index * 2) - gState0TypedWork.bytes[0x40] * 8;
                { register u32 off = index * 2 + 1; sub_08017994(index, x, *(const u8 *)((u32)gUnknown_083AD524 + off)); }
            }
        }
        for (i = 0; i <= 12; i++) {
            gFrameObjects[9 + i].screenX -= 8;
        }
        sub_08044118(0xD, 6, 0x10 - gState0TypedWork.bytes[0x40], 0xD, *(volatile u16 *)0x04000008, (u16 *)0x02020000);
        sub_08044160(0xD, 6, 0xF - gState0TypedWork.bytes[0x40], 0xD, *(volatile u16 *)0x04000008, (u16 *)0x02020000);
    } else {
        for (i = 0, root = gSetupBytes185E8; i <= 2; i++) {
            index = gState0TypedWork.bytes[0x3C] * 3 + i;
            if (*(const u8 *)((u32)root + (index << 8) + 0x40) != 0) {
                register u32 twice asm("r0") = index * 2; /* FAKE MATCH: keeps index * 2 in r0 as the reference does; local-alloc priority otherwise swaps it with the counter byte in r1 */
                x = *(const u8 *)((u32)gUnknown_083AD524 + twice) + (gState0TypedWork.bytes[0x40] << 3);
                { register u32 off = twice + 1; sub_08017994(index, x, *(const u8 *)((u32)gUnknown_083AD524 + off)); }
            }
        }
        for (i = 0; i <= 12; i++) {
            gFrameObjects[9 + i].screenX += 8;
        }
        sub_08044118(0xD, 6, gState0TypedWork.bytes[0x40] + 1, 0xD, *(volatile u16 *)0x04000008, (u16 *)0x02020000);
        sub_08044160(0xD, 6, gState0TypedWork.bytes[0x40] + 2, 0xD, *(volatile u16 *)0x04000008, (u16 *)0x02020000);
    }
    if (++gState0TypedWork.bytes[0x40] == 0xE) {
        sub_080187A8();
        return 1;
    }
    return 0;
}

s32 sub_080488E8(s32 value, u8 digits) {

    register s32 i asm("r4"); /* FAKE MATCH: pins i to r4; global-alloc priority otherwise gives r4 to power */
    s32 j;
    s32 power;
    s32 rest;

    rest = value;
    i = 0;
    while (i < sub_080488AC(value) - digits && i != sub_080488AC(value) - 1) {
        power = 1;
        j = 0;
        i++;
        for (; j < sub_080488AC(value) - i; j++)
            power *= 10;
        j = sub_0807CD2C(rest, power);
        rest -= power * j;
    }
    /* With nonzero digits and no loop iterations, the reference returns the caller's incoming r8. */
    if (digits != 0)
        return j;
    return rest;
}
