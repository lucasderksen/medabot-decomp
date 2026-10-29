/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "compression.h"
#include "continued_commands.h"
#include "continued_late_graphics.h"
#include "coordinate_helpers.h"
#include "display_helpers.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "gba.h"
#include "graphics.h"
#include "main.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct ContinuedDispatchWork { u8 pad[0xC2D]; u8 mode; };

extern const u8 gUnknown_0850F2B8[160];
extern s8 gUnknown_03000584;
extern s8 gUnknown_03002420;
extern struct ContinuedDispatchWork gContinuedWork_030057E0;
extern u32 sub_0801827C(void);
extern u8 gUnknown_03001864[4];
extern void sub_08015838(u32 index, u8 *destination);
extern void sub_08017A14(u32 first, u32 second);
extern void sub_08017B24(void);
extern void sub_08017BD0(void);
extern void sub_08017CE8(void);
extern void sub_08017D14(void);
extern void sub_08017D50(void);
extern void sub_08017D90(void);
extern void sub_08017E00(void);
extern void sub_08017EA8(void);
extern void sub_08017F9C(void);
extern void sub_08018074(u32 first, u32 second, u32 third, u32 fourth);
extern void sub_08018098(void);
extern void sub_08018218(void);
extern void sub_080182AC(void);
extern void sub_080182D0(void);
extern void sub_0801830C(void);

void sub_08013B8C(void);
void sub_08017994(u32 arg0, u32 arg1, u32 arg2);
void sub_08047878(u32 first, u32 second);

void sub_08013B8C(void) {
    volatile u16 *display;
    volatile u16 *bg0;
    volatile u16 *bg1;
    volatile u16 *bg2;
    volatile u16 *bg3;
    const u8 *palette;
    u8 *record;
    u8 *part;
    u32 fill;
    u32 index;
    sub_08043CA8();
    display = (volatile u16 *)0x04000000;
    *display &= 0xF0FF;
    bg0 = (volatile u16 *)0x04000008;
    *bg0 = 0x500;
    bg1 = (volatile u16 *)0x0400000A;
    *bg1 = 0x1901;
    bg2 = (volatile u16 *)0x0400000C;
    *bg2 = 0x1A02;
    bg3 = (volatile u16 *)0x0400000E;
    *bg3 = 0x1B03;
    LeDecompress((const u8 *)0x084EEA64, (void *)0x06004000);
    LeDecompress((const u8 *)0x084C58F4, (void *)0x06006000);
    LeDecompress((const u8 *)0x084C3BF8, (void *)0x06006800);
    LeDecompress((const u8 *)0x084C55CC, (void *)0x06006E00);
    LeDecompress((const u8 *)0x084C3F0C, (void *)0x06007200);
    LeDecompress((const u8 *)0x084C58D8, (void *)0x06007480);
    LeDecompress((const u8 *)0x084C88B8, (void *)0x06017E00);
    LoadLeTilemap(0, 0, (const u8 *)0x084F0B7C, *bg0, 512);
    LoadLeTilemap(0, 0, (const u8 *)0x084F16C8, *bg1, 512);
    LoadLeTilemap(0, 0, (const u8 *)0x084F22C4, *bg2, 512);
    LoadLeTilemap(0, 0, (const u8 *)0x084F35FC, *bg3, 512);
    CpuFastSet((const void *)0x084F4D80, (void *)0x05000000, 112);
    CpuFastSet((const void *)0x0850F498, (void *)0x05000200, 64);
    palette = gUnknown_0850F2B8 + 64;
    CpuFastSet(palette, (void *)0x05000380, 8);
    CpuFastSet(palette + 64, (void *)0x050003A0, 8);
    palette -= 64;
    CpuFastSet(palette, (void *)0x050003E0, 8);
    CpuFastSet((const void *)0x084E43F8, (void *)0x050003C0, 8);
    fill = 0;
    CpuFastSet(&fill, gFrameObjects, 0x01000800);
    *display |= 0x1F40;
    record = (u8 *)0x0300047C;
    sub_0803F624(record, 20, 0);
    record[10] = 1;
    sub_08017A14(0, 0);
    sub_08017B24();
    sub_08017BD0();
    sub_08017D14();
    sub_08017D50();
    sub_08017D90();
    sub_08017E00();
    sub_08017EA8();
    sub_08017F9C();
    index = *record++ * 3;
    index += *record;
    part = (u8 *)0x03001864;
    sub_08015838(index, part);
    sub_08018074(part[0], part[1], part[2], part[3]);
    sub_08018098();
    sub_0801830C();
    sub_08043240(0, 8);
    sub_08042698(2, 2, 11, 2, *bg1, 0x63C0);
    sub_0804253C(5, 63, 32);
    gUnknown_0300137C++;
}

void sub_08017994(u32 arg0, u32 arg1, u32 arg2) {
    s32 var_r6;
    u32 var_r1;
    u32 var_sb;

    if (arg0 <= 2U) {
        var_r1 = arg0;
        var_sb = 0;
    } else {
        var_r1 = arg0 - 3;
        var_sb = 1;
    }
    if (var_r1 == gState0TypedWork.bytes[0x3D]) {
        var_r6 = 0;
        goto block_7;
    }
    if (var_r1 == gState0TypedWork.bytes[0x46]) {
        var_r6 = 1;
block_7:
        sub_08015838(arg0, gUnknown_03001864);
        sub_08042E58((u32) gUnknown_03001864[0], (u32) gUnknown_03001864[1], (u32) gUnknown_03001864[2], (u32) gUnknown_03001864[3], arg0, (var_r6 * 4), arg1, arg2, var_sb, 2U, (var_r6 * 4));
    }
}

void sub_08047878(u32 first, u32 second) {
    switch(first) {
    case 0x20: {
        gContinuedWork_030057E0.mode = 1;
        gMainState = 0;
        gMainSubstate = 6;
        gUnknown_0300137C = 0;
        break;
    }
    case 0x21: {
        gContinuedWork_030057E0.mode = 0;
        gMainState = 0;
        gMainSubstate = 6;
        gUnknown_0300137C = 0;
        break;
    }
    case 0x40: {
        gMainState = 0;
        gMainSubstate = 1;
        gUnknown_0300137C = 16;
        break;
    }
    case 0x41: {
        gMainState = 1;
        gMainSubstate = 1;
        gUnknown_0300137C = 24;
        break;
    }
    case 0x42: {
        gMainState = 1;
        gMainSubstate = 1;
        gUnknown_0300137C = 28;
        break;
    }
    case 0x43: {
        gMainState = 1;
        gMainSubstate = 1;
        gUnknown_0300137C = 40;
        break;
    }
    case 0x0: {
        gUnknown_03000584 = 0;
        gMainState = 2;
        gMainSubstate = 18;
        gUnknown_0300137C = 0;
        break;
    }
    case 0x1: {
        gUnknown_03000584 = 1;
        gMainState = 2;
        gMainSubstate = 18;
        gUnknown_0300137C = 0;
        break;
    }
    case 0x2: {
        gUnknown_03000584 = 2;
        gMainState = 2;
        gMainSubstate = 18;
        gUnknown_0300137C = 0;
        break;
    }
    case 0x3: {
        gUnknown_03002420 = second;
        gMainState = 2;
        gMainSubstate = 11;
        gUnknown_0300137C = 0;
        break;
    }
    case 0x4: {
        gMainState = 2;
        gMainSubstate = 21;
        gUnknown_0300137C = 0;
        break;
    }
    case 0x5: {
        gUnknown_03000588 = 0;
        gMainState = 2;
        gMainSubstate = 20;
        gUnknown_0300137C = 0;
        break;
    }
    case 0x6: {
        gMainState = 2;
        gMainSubstate = 23;
        gUnknown_0300137C = 0;
        break;
    }
    case 0x8: {
        gMainState = 2;
        gMainSubstate = 22;
        gUnknown_0300137C = 0;
        break;
    }
    case 0x10: {
        gMainState = 3;
        gMainSubstate = 4;
        gUnknown_0300137C = 0;
        break;
    }
    case 0x11: {
        gMainState = 3;
        gMainSubstate = 5;
        gUnknown_0300137C = 0;
        break;
    }
    case 0x12: {
        gMainState = 3;
        gMainSubstate = 3;
        gUnknown_0300137C = 0;
        break;
    }
    case 0x13: {
        gMainState = 3;
        gMainSubstate = 6;
        gUnknown_0300137C = 0;
        break;
    }
    }
}
