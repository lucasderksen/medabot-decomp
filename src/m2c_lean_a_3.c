/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "compression.h"
#include "continued_scene_records.h"
#include "gba.h"
#include "record_helpers.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct LeanCounter1800 { u8 unknown00[0x8B]; u8 group8B; u8 unknown8C[0x1E]; u8 stepAA; u8 unknownAB[0x1D]; u16 valueC8; u8 unknownCA[0x2E]; u8 flagsF8; u8 unknownF9[0x5B]; u16 positions[4]; };

extern const u8 gUnknown_084D2DC4[];
extern const u8 gUnknown_0850F5B8[];
extern struct LeanCounter1800 gCounter6ED08_03001800;
extern void sub_080368C4(u8 *text, u32 kind, u32 group, s32 x, s32 y);

extern void sub_0801E918(void);

void sub_0801E918(void) {

    u16 x, y;

    LeDecompress(gUnknown_084D2DC4, (void *)0x06010000);
    CpuFastSet(gUnknown_0850F5B8, (void *)0x050003C0, 8);
    if (!(gCounter6ED08_03001800.flagsF8 & 2)) {
        x = gCounter6ED08_03001800.positions[2];
        y = gCounter6ED08_03001800.positions[3];
    } else {
        x = gCounter6ED08_03001800.positions[0];
        y = gCounter6ED08_03001800.positions[1];
    }
    sub_0801A28C(gUnknown_0300052E, gCounter6ED08_03001800.valueC8, 1);
    sub_080368C4(gUnknown_0300052E, 10, gCounter6ED08_03001800.group8B, (s16)x, (s16)y);
    sub_08074DE0(0x5B);
    gCounter6ED08_03001800.stepAA++;
}
