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
#include "display_helpers.h"
#include "frame.h"
#include "frame_command_data.h"
#include "object_helpers.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_inventory.h"
#include "state0_inventory_numbers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct Setup17734 {
    u8 pad00;
    u8 id01;
    u8 pad02[0xBF];
    u8 valueC1;
    u8 padC2[0x3E];
};

extern struct Setup17734 gSetup17734[] asm("gSetupBuffer_03000590");
extern u8 sub_0807CEC8(u32 value, u32 divisor);
extern void sub_08015BF4(u32 value);

void sub_0800B174(void);
void sub_08017734(u32 mode);

void sub_0800B174(void) {

    u32 i;

    for (i = 0; i < 8; i++) {
        if (gInventoryRecords[gState0TypedWork.bytes[0x3D]].unknown06[0x22] > i)
            sub_08042698(1, 1, i + 0x2, 0x9, *(volatile u16 *)0x0400000A, 0xd3d0);
        else
            sub_0803EF8C(1, 1, i + 0x2, 0x9, *(volatile u16 *)0x0400000A, 0);
    }

    for (i = 0; i < 8; i++) {
        if (gInventoryRecords[gState0TypedWork.bytes[0x3D]].unknown06[0x23] > i)
            sub_08042698(1, 1, i + 0x2, 0xc, *(volatile u16 *)0x0400000A, 0xd3d0);
        else
            sub_0803EF8C(1, 1, i + 0x2, 0xc, *(volatile u16 *)0x0400000A, 0);
    }

    for (i = 0; i < 8; i++) {
        if (gInventoryRecords[gState0TypedWork.bytes[0x3D]].unknown06[0x24] > i)
            sub_08042698(1, 1, i + 0x10, 0x9, *(volatile u16 *)0x0400000A, 0xd3d3);
        else
            sub_0803EF8C(1, 1, i + 0x10, 0x9, *(volatile u16 *)0x0400000A, 0);
    }

    for (i = 0; i < 8; i++) {
        if (gInventoryRecords[gState0TypedWork.bytes[0x3D]].unknown06[0x25] > i)
            sub_08042698(1, 1, i + 0x10, 0xc, *(volatile u16 *)0x0400000A, 0xd3d3);
        else
            sub_0803EF8C(1, 1, i + 0x10, 0xc, *(volatile u16 *)0x0400000A, 0);
    }

    for (i = 0; i < 8; i++) {
        if (gInventoryRecords[gState0TypedWork.bytes[0x3D]].unknown06[0x26] > i)
            sub_08042698(1, 1, i + 0x2, 0xf, *(volatile u16 *)0x0400000A, 0xd3d1);
        else
            sub_0803EF8C(1, 1, i + 0x2, 0xf, *(volatile u16 *)0x0400000A, 0);
    }

    for (i = 0; i < 8; i++) {
        if (gInventoryRecords[gState0TypedWork.bytes[0x3D]].unknown06[0x27] > i)
            sub_08042698(1, 1, i + 0x2, 0x12, *(volatile u16 *)0x0400000A, 0xd3d2);
        else
            sub_0803EF8C(1, 1, i + 0x2, 0x12, *(volatile u16 *)0x0400000A, 0);
    }

    for (i = 0; i < 8; i++) {
        if (gInventoryRecords[gState0TypedWork.bytes[0x3D]].unknown06[0x28] > i)
            sub_08042698(1, 1, i + 0x10, 0xf, *(volatile u16 *)0x0400000A, 0xd3d4);
        else
            sub_0803EF8C(1, 1, i + 0x10, 0xf, *(volatile u16 *)0x0400000A, 0);
    }

    for (i = 0; i < 8; i++) {
        if (gInventoryRecords[gState0TypedWork.bytes[0x3D]].unknown06[0x29] > i)
            sub_08042698(1, 1, i + 0x10, 0x12, *(volatile u16 *)0x0400000A, 0xd3d0);
        else
            sub_0803EF8C(1, 1, i + 0x10, 0x12, *(volatile u16 *)0x0400000A, 0);
    }
}

void sub_08017734(u32 mode) {

    u32 x;
    u32 i;
    u8 digits;

    x = 0;
    if (mode == 0) {
        sub_08041D04(gUnknownBytes_083B7F8C + gSetup17734[gCounter6ED08_03001800.buffer64[0x1C]].id01 * 3, gUnknown_0300052E, 3);
        sub_08041D04(gUnknownBytes_083B7E54 + gUnknown_0300052E[gCounter6ED08_03001800.buffer64[0x1E] - 1] * 6, gUnknown_0300052E + 0x20, 6);
        digits = sub_0807CEC8(gUnknown_0300052E[0x22], 10);
        for (i = 0; i < 8 - digits; i++) {
            sub_0803EF8C(1, 1, x + 1, 0x11, *(volatile u16 *)0x04000008, 0);
            x++;
        }
        for (i = x; i <= 7; i++) {
            if (!(4 & gState0TypedWork.bytes[0x84])) {
                sub_08042698(1, 1, x + 1, 0x11, *(volatile u16 *)0x04000008, 0xB208);
            } else {
                sub_08042698(1, 1, x + 1, 0x11, *(volatile u16 *)0x04000008, 0xC208);
            }
            x++;
        }
        sub_0803EF8C(5, 1, 4, 0x12, *(volatile u16 *)0x0400000A, 0);
        sub_08042838(gState0TypedWork.bytes[0x110], 4, 0x12, 2, *(volatile u16 *)0x0400000A, 0xD220);
        sub_08015BF4(gCounter6ED08_03001800.buffer64[0x1C]);
    } else {
        sub_0803EF8C(8, 1, 1, 0x11, *(volatile u16 *)0x04000008, x);
        sub_08015E68(gCounter6ED08_03001800.buffer64[0x1C]);
        if (gSetup17734[gCounter6ED08_03001800.buffer64[0x1C]].valueC1 != 0x50) {
            sub_08015BA8(gCounter6ED08_03001800.buffer64[0x1C]);
        }
    }
}
