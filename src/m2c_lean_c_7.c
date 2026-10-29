/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_commands.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "graphics.h"
#include "later_graphics.h"
#include "record_helpers.h"
#include "render_work.h"
#include "sprite_layouts.h"
#include "state0_work.h"

struct ContinuedWorkCBDC {
    u8 unknown000[0xC8A];
    u16 timer;
    u16 savedTimer;
    u8 unknownC8E[6];
    u8 side;
    u8 count;
    u8 step;
    u8 unknownC97[0x25];
    s8 limits[2];
};
struct LaterEntry55A0 { u16 first; u16 second; };
struct FixedPoint24 { u32 fraction:8; u32 whole:24; };

extern struct ContinuedWorkCBDC gCbdcWork asm("gContinuedWork_030057E0");
extern struct LaterEntry55A0 gLaterEntries55A0[] asm("gLaterBuffer_030055A0");
extern u8 gContinuedBytesFC7C[] asm("gContinuedWork_030057E0");
extern void sub_0804D8CC(u32 count);

void sub_0804CBDC(void);
void sub_0804FC7C(void);

void sub_0804CBDC(void) {

    struct ContinuedWorkCBDC *work = &gCbdcWork;

    work->savedTimer = work->timer;
    sub_0804D8CC(3);
    if (gCbdcWork.side == 0) {
        if (work->limits[0] >= work->count)
            return;
    } else {
        if (work->limits[1] >= work->count)
            return;
    }
    gCbdcWork.timer = gCbdcWork.savedTimer + gCbdcWork.step;
}

void sub_0804FC7C(void) {

    u8 *objects = (u8 *)gFrameObjects;
    u8 *work = gContinuedBytesFC7C;
    u16 value;

    value = *(u16 *)(work + 0xC6E);
    ((struct FixedPoint24 *)(objects + 0xC0C))->whole = value;
    value = *(u16 *)(work + 0xC70);
    ((struct FixedPoint24 *)(objects + 0xC10))->whole = value;
    sub_080497C0(objects + 0xC00, &gFrameObjects[work[0xC94] + 0x4F], 0x40);
    gLaterEntries55A0[work[0xC94] + 0x4F].first = 0xFFFF;
    sub_080497C0(objects + 0x1680, &gFrameObjects[work[0xC94] + 0x79], 0x40);
    sub_08050290();
}
