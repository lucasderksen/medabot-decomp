/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "compression.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "render_work.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "utility_helpers.h"

struct ContinuedFrame21A6D4 {u8 prefix[0x840];struct FrameObject frame;};
struct LocalRenderResetWork { u8 pad00[4]; u16 phase4; u8 pad6[2]; s32 counter8; };
struct LocalRenderResetDma { const void *volatile source; void *volatile destination; volatile u32 control; };

extern const u8 *const gState0NextCommands_083B6100[0x63];
extern const u8 *const gUnknown_08485A78;
extern const u8 gUnknown_084E02BC[];
extern const u8 gUnknown_084E4658[32];
extern const u8 gUnknown_085102F8[32];
extern struct LocalRenderResetWork gGraphicsTransferCounter;
s32 sub_08068460(s32, s32, s32);

void sub_0802A6D4(void);
void sub_0806F114(void);

void sub_0802A6D4(void) {
    struct ContinuedFrame21A6D4 *frames;

    LeDecompress(gUnknown_084E02BC, (void *)0x06014800);
    CpuFastSet(gUnknown_085102F8, (void *)0x050002E0, 8U);
    CpuFastSet(gUnknown_084E4658, (void *)0x050002C0, 8U);
    frames=(struct ContinuedFrame21A6D4 *)gFrameObjects;
    frames->frame.flags = 0xC604;
    frames->frame.tableSelector = 0;
    frames->frame.screenY = (u16)gFrameObjects[gState0TransferWork.bytes[0x87]*4+0x5D].screenY - 4;
    frames->frame.palette = 7;
    frames->frame.priority = 0xF0;
    frames->frame.scaleX = 4;
    frames->frame.scaleY = 4;
    frames->frame.angle = 0;
    sub_08040B90(gState0NextCommands_083B6100[0x62], 0x21U);
    if (!(1 & gState0TransferWork.bytes[0xF8])) {
        frames->frame.screenX = 0x70;
    } else {
        frames->frame.flags |= 0x1000;
        frames->frame.screenX = 0x80;
    }
    sub_08074DE0(0x6AU);
    gState0TransferWork.bytes[0xAA] = (u8) (gState0TransferWork.bytes[0xAA] + 1);
}

void sub_0806F114(void) {
    s32 sp20;
    u32 pattern;
    struct LocalRenderResetDma *dma;

    pattern = 0x2B;
    sub_080445F4();
    sp20 = 0x200;
    dma = (struct LocalRenderResetDma *)0x040000D4;
    dma->source = &sp20;
    dma->destination = gRenderWork->objects;
    dma->control = 0x85000100;
    (void)dma->control;
    sub_080446B4(0U, pattern, pattern, pattern, pattern, 0x78U, 0x50U, 2U, 0xCU, 0U, 0U, 0U);
    dma->source = gUnknown_08485A78;
    dma->destination = (void *)0x05000200;
    dma->control = 0x80000050;
    (void)dma->control;
    sub_08068460(2, 4, 0);
    *(volatile u16 *)0x04000000 |= 0x1000;
    gGraphicsTransferCounter.phase4 = 0xF;
    gUnknown_0300137C = 1;
}
