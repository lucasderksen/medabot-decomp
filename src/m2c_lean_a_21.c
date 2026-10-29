/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "frame.h"
#include "record_helpers.h"
#include "state0_work.h"

struct Work255F8
{
    u8 unknown00[0x51];
    u8 value51;
    u8 value52;
    u8 unknown53[0x34];
    u8 setup87;
    u8 setup88;
    u8 unknown89[0x21];
    u8 counterAA;
    u8 unknownAB[0x1D];
    u16 valueC8;
    u8 unknownCA[0x22];
    s16 valueEC;
};
struct Part255F8 { u8 unknown00[8]; u8 byte08; u8 unknown09[7]; u8 block10[8]; };
struct Setup255F8 { u8 unknown00[0x48]; struct Part255F8 parts[7]; u8 unknownF0[0x10]; };

extern struct Setup255F8 gSetup255F8[] asm("gSetupBuffer_03000590");
extern struct Work255F8 gWork255F8 asm("gCounter6ED08_03001800");
extern void sub_0803572C(u8 *, s32);
extern void sub_08035740(u8 *, s32, u32);
extern void sub_08037458(u32, s32);
extern void sub_08037498(s32, s32);

void sub_080255F8(void);

void sub_080255F8(void) {

    sub_08037458(gWork255F8.setup88, gWork255F8.valueEC);
    gWork255F8.value51 = gWork255F8.valueC8;
    sub_0803572C(gSetup255F8[gWork255F8.setup88].parts[0].block10, gWork255F8.value51);
    sub_08037498(gWork255F8.setup87, gWork255F8.value51);
    gWork255F8.value52 = gWork255F8.valueC8;
    sub_08035740(gSetup255F8[gWork255F8.setup87].parts[0].block10, gWork255F8.value52, gSetup255F8[gWork255F8.setup87].parts[0].byte08);
    gWork255F8.counterAA++;
}
