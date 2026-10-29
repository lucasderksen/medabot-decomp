/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "compression.h"
#include "continued_late_graphics.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "gba.h"
#include "graphics.h"
#include "object_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_part_markers.h"
#include "state0_work.h"
#include "tile_text.h"

extern const u8 gUnknown_084C3E64[];
extern const u8 gUnknown_084C4B4C[];
extern const u8 gUnknown_084C4BDC[];
extern const u8 gUnknown_084C4FBC[];
extern const u8 gUnknown_084C4FFC[];
extern const u8 gUnknown_084C53C8[];
extern const u8 gUnknown_084EE0DC[];
extern const u8 gUnknown_084F0B44[];
extern const u8 gUnknown_084F1608[];
extern const u8 gUnknown_084F2244[];
extern const u8 gUnknown_084F3468[];
extern const u8 gUnknown_084F4BC0[];
extern const u8 gUnknown_0850F378[];
extern u8 gCopy6280C0202F800[];
extern u8 gCopy6280C0202F9C0[];
extern u8 gUnknown_0202F980[32];
extern u8 gUnknown_0202F9A0[32];

void sub_0800E020(void);

void sub_0800E020(void) {

    s32 sp4;

    sub_08043CA8();
    if ((gState0TypedWork.bytes[0x3C] == 0) || (gState0TypedWork.bytes[0x3C] == 4)) {
        sub_0800F440();
    }
    *(volatile u16 *)0x04000000 &= 0xF0FF;
    *(volatile u16 *)0x04000008 = 0x500;
    *(volatile u16 *)0x0400000A = 0x1801;
    *(volatile u16 *)0x0400000C = 0x1902;
    *(volatile u16 *)0x0400000E = 0x1A03;
    LeDecompress(gUnknown_084EE0DC, (void *)0x06004000);
    LeDecompress(gUnknown_084C4BDC, (void *)0x06006000);
    LeDecompress(gUnknown_084C4FBC, (void *)0x06007080);
    LeDecompress(gUnknown_084C4B4C, (void *)0x06007100);
    LeDecompress(gUnknown_084C4FFC, (void *)0x06007200);
    LeDecompress(gUnknown_084C53C8, (void *)0x06007300);
    LeDecompress(gUnknown_084C3E64, (void *)0x06007880);
    LeDecompress(gUnknownBytes_084C88B8, (void *)0x06017E00);
    LoadLeTilemap(0U, 0U, gUnknown_084F0B44, (u32) *(volatile u16 *)0x04000008, 0x200U);
    LoadLeTilemap(0U, 0U, gUnknown_084F1608, (u32) *(volatile u16 *)0x0400000A, 0x200U);
    LoadLeTilemap(0U, 0U, gUnknown_084F2244, (u32) *(volatile u16 *)0x0400000C, 0x200U);
    LoadLeTilemap(0U, 0U, gUnknown_084F3468, (u32) *(volatile u16 *)0x0400000E, 0x200U);
    if ((gState0TypedWork.bytes[0x3C] == 0) || (gState0TypedWork.bytes[0x3C] == 4)) {
        CpuFastSet(gUnknown_084F4BC0, gEquipmentPaletteShadow, 0x70U);
        CpuFastSet((void *)0x05000200, gCopy6280C0202F800, 0x80U);
        CpuFastSet(gUnknown_0850F378, gUnknown_0202F980, 8U);
        CpuFastSet((const u8 *)((u32)gUnknown_0850F378 - 0x60U), gUnknown_0202F9A0, 8U);
        CpuFastSet(gUnknownWords_084E43F8, gCopy6280C0202F9C0, 8U);
        gState0TypedWork.bytes[0x84] = 0;
    } else {
        CpuFastSet(gUnknown_084F4BC0, (void *)0x05000000, 0x70U);
        CpuFastSet(gUnknown_0850F378, (void *)0x05000380, 8U);
        CpuFastSet((const u8 *)((u32)gUnknown_0850F378 - 0x60U), (void *)0x050003A0, 8U);
        CpuFastSet(gUnknownWords_084E43F8, (void *)0x050003C0, 8U);
        sub_0800F60C();
        sub_0800F300();
        sub_0804253C(5U, 0x3FU, 0x20U);
    }
    sp4 = 0;
    CpuFastSet(&sp4, gFrameObjects, 0x01000800U);
    *(volatile u16 *)0x04000000 = (u16) (*(volatile u16 *)0x04000000 | 0x1F60);
    sub_08042B58((u32) gState0TypedWork.bytes[0x3D], (u32) gState0TypedWork.bytes[0x3E], &gState0TypedWork.bytes[0xEE]);
    sub_0800F6E4();
    sub_0800F77C();
    sub_0800F7D0();
    sub_0800F844();
    sub_0800F8A0();
    sub_0800F8D8();
    sub_0800FA7C();
    sub_0800FC60();
    sub_0800FCF0();
    gState0TypedWork.bytes[0x42] = 1;
    gUnknown_0300137C=(u32)gUnknown_0300137C+1U;
}
