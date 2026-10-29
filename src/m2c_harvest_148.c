/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct ContinuedAngleFrame21 {u8 prefix[0x858];u16 angle;};

extern const u8 *const gState0NextCommands_083B6100[];

void sub_08023900(void);

void sub_08023900(void) {
    const u8 *const *commands=gState0NextCommands_083B6100;
    sub_08040BD8(commands[gState0TypedWork.bytes[0x84]],0x21);
    if (!(1 & gState0TransferWork.bytes[0xF8])) {
        struct ContinuedAngleFrame21 *frame=(struct ContinuedAngleFrame21 *)gFrameObjects;
        frame->angle=(frame->angle-0x40)&0x3FF;
    } else {
        struct ContinuedAngleFrame21 *frame=(struct ContinuedAngleFrame21 *)gFrameObjects;
        frame->angle=(frame->angle+0x40)&0x3FF;
    }
    if (sub_080355F0(0x21)!=0) {
        struct ContinuedAngleFrame21 *frame=(struct ContinuedAngleFrame21 *)gFrameObjects;
        frame->angle=0;
        gState0TransferWork.bytes[0xAA]++;
    }
}
