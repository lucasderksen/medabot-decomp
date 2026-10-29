/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "compression.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "gba.h"
#include "record_helpers.h"
#include "state0_work.h"

struct ContinuedScaleFrame21 {
 u8 prefix[0x840];u16 flags;s16 screenX,screenY;u16 frameAndGroup;u8 scaleX,scaleY,palette,priority;
 u8 gapC[0xC];u16 angle,unknown1A;u8 tableSelector,affineIndex;u8 gap1E[5];u8 progress;u8 kind;u8 gap25[0xB];u16 savedX;s16 savedY;u8 gap34[0xC];
};

extern const u8 gUnknown_084D804C[];
extern const u8 gUnknown_0850FE58[64];

void sub_08025230(void);

void sub_08025230(void) {
 u8 *work;struct ContinuedScaleFrame21 *frames;u32 zero;u16 zeroHalf;
    LeDecompress(gUnknown_084D804C, (void *)0x06014800);
    CpuFastSet(gUnknown_0850FE58, (void *)0x050002C0, 0x10U);
    frames=(struct ContinuedScaleFrame21 *)gFrameObjects;
    frames->flags |= 0x220;
    frames->scaleX = (zero=0,zeroHalf=0,0x40);
    frames->scaleY = 0x40;
    frames->angle = zeroHalf;
    frames->palette = 6;
    frames->frameAndGroup = 0x5000;
    work=gState0TransferWork.bytes;
    frames->savedX = (u16) (u16)gFrameObjects[work[0x88]*4+0x5D].screenX;
    frames->savedY = (s16) ((u16)gFrameObjects[work[0x88]*4+0x5D].screenY - 4);
    frames->kind = 3;
    frames->progress = zero;
    gState0TypedWork.widths.word86 = 0x3C;
    work[0xAA]++;
}
