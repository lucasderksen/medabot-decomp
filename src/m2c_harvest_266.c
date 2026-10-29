/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "compression.h"
#include "continued_late_graphics.h"
#include "frame.h"
#include "graphics.h"
#include "object_numeric_helpers.h"
#include "record_helpers.h"
#include "render_work.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct Counter6ED08 {u8 pad0[4];u16 field4;u8 pad6[6];u16 fieldC;};
struct Dma6ED08 {const void *volatile source;void *volatile destination;volatile u32 control;};

extern const u8 *const gUnknown_08485A58;
extern const u8 *const gUnknown_08485A60;
extern const u8 *const gUnknown_08485A68;
extern const u8 *const gUnknown_08485A78;
extern const u8 gUnknown_087BBA60[];
extern const u8 gUnknown_087BEE04[];
extern const u8 gUnknown_087BF004[];
extern const u8 gUnknown_087BF380[];
extern const u8 gUnknown_087C955C[];
extern const u8 gUnknown_087C9A0C[];
extern const u8 gUnknown_087C9A2C[];
extern s32 gGraphicsTransferCounter;
extern struct Counter6ED08 gCounter6ED08_03001800;
extern void sub_08068460(u8, u8, u16);
extern void sub_0806FBB8(const u16 *, u8, u8, u8, u8, u8, u16, u8);

void sub_0806ED08(void);

void sub_0806ED08(void) {

    struct {u16 first[120]; u16 second[400];} data;
    void *temp_r1;

    LZ77UnCompVram(gUnknown_087BBA60, (void *)0x06000000);
    LZ77UnCompVram(gUnknown_087C955C, (void *)0x06008020);
    LZ77UnCompVram(gUnknown_08485A58, (void *)0x06008C80);
    ((struct Dma6ED08 *)0x040000D4)->source = gUnknown_087BEE04;
    ((struct Dma6ED08 *)0x040000D4)->destination = (void *)0x05000000;
    ((struct Dma6ED08 *)0x040000D4)->control = 0x84000080;
    (void)((struct Dma6ED08 *)0x040000D4)->control;
    ((struct Dma6ED08 *)0x040000D4)->source = gUnknown_087C9A0C;
    ((struct Dma6ED08 *)0x040000D4)->destination = (void *)0x05000000;
    ((struct Dma6ED08 *)0x040000D4)->control = 0x84000008;
    (void)((struct Dma6ED08 *)0x040000D4)->control;
    ((struct Dma6ED08 *)0x040000D4)->source = gUnknown_08485A68;
    ((struct Dma6ED08 *)0x040000D4)->destination = (void *)0x05000020;
    ((struct Dma6ED08 *)0x040000D4)->control = 0x84000008;
    (void)((struct Dma6ED08 *)0x040000D4)->control;
    LZ77UnCompVram(gUnknown_087BF004, (void *)0x06007000);
    LZ77UnCompVram(gUnknown_087BF380, (void *)0x06007800);
    LZ77UnCompVram(gUnknown_087C9A2C, data.first);
    sub_0806FBB8(data.first, 0x1F, 0xA, 0xC, 0, 0, 1, 0);
    LZ77UnCompVram(gUnknown_08485A60, data.second);
    sub_0806FBB8(data.second, 0x1E, 0x14, 0x14, 0xA, 0, 0x64, 1);
    (*(volatile s16 *)((u8 *)((void *)0x0400000A) + 0)) = 0xE01;
    (*(volatile s16 *)((u8 *)((void *)0x0400000A) + 4)) = 0xF03;
    temp_r1 = ((void *)0x0400000A + 4) - 6;
    (*(volatile s16 *)((u8 *)(temp_r1) + 0)) = 0x1E08;
    *(volatile u16 *)0x0400000C = 0x1F0A;
    ((struct Dma6ED08 *)0x040000D4)->source = gUnknown_08485A78;
    ((struct Dma6ED08 *)0x040000D4)->destination = (void *)0x05000200;
    ((struct Dma6ED08 *)0x040000D4)->control = 0x80000050;
    (void)((struct Dma6ED08 *)0x040000D4)->control;
    sub_08048864(0U, 0xC000U, 0x30DU, 4U, 3);
    gFrameObjects->screenX = 0x90;
    gFrameObjects->screenY = 0x40;
    sub_08068460(2, 1, 0);
    gRenderMode = 0;
    gCounter6ED08_03001800.field4 = (u16) gCounter6ED08_03001800.fieldC;
    gUnknown_0300137C = 3;
}
