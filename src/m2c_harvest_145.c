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
#include "frame_objects.h"
#include "gba.h"
#include "record_helpers.h"
#include "state0_work.h"

struct ContinuedScaleFrame21 {
 u8 prefix[0x840];u16 flags;s16 screenX,screenY;u16 frameAndGroup;u8 scaleX,scaleY,palette,priority;
 u8 gapC[0xC];u16 angle,unknown1A;u8 tableSelector,affineIndex;u8 gap1E[6];u8 kind;u8 gap25[0xB];u16 savedX;s16 savedY;u8 gap34[0xC];
};

extern const u8 *const gState0NextCommands_083B6100[]; /* Observed index0x3C. */
extern const u8 gUnknown_084D6B70[];
extern const u8 gUnknown_0850FC58[32];

void sub_08021EA0(void);

void sub_08021EA0(void) {
 u8 *work;struct ContinuedScaleFrame21 *frames;
    LeDecompress(gUnknown_084D6B70, (void *)0x06014800);
    CpuFastSet(gUnknown_0850FC58, (void *)0x050002E0, 8U);
    work=gState0TransferWork.bytes;
    if (1 & work[0xF8]) {
        struct ContinuedScaleFrame21 *initial=(struct ContinuedScaleFrame21 *)gFrameObjects;
        initial->flags |= 0x1000;
    }
    frames=(struct ContinuedScaleFrame21 *)gFrameObjects;
    frames->flags |= 0x200;
    frames->scaleX = 0x40;
    frames->scaleY = 0x40;
    frames->angle = 0;
    frames->savedX = (u16) (u16)gFrameObjects[work[0x88]*4+0x5D].screenX;
    frames->savedY = (s16) ((u16)gFrameObjects[work[0x88]*4+0x5D].screenY - 4);
    frames->kind = 6;
    sub_08040B90(gState0NextCommands_083B6100[0x3C],0x21);
    gState0TypedWork.widths.word86 = 0x3C;
    work[0xAA]++;
}
