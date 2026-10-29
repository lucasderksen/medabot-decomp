/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "battle_work.h"
#include "continued_late_graphics.h"
#include "frame.h"
#include "frame_command_data.h"
#include "pose_channels.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct PostDispatchBytes { u32 word; u8 bytes[8]; };

extern struct PostDispatchBytes gPostDispatchBytes asm("gPostDispatchWord_03002B70");

void sub_0803E680(void);

void sub_0803E680(void) {

    u16 word;

    gMainSerialOutgoingWork.word06 = gPostDispatchBytes.bytes[gCounter6ED08_03001800.frame51]
        + (u16)(((gCounter6ED08_03001800.toggle1AF << 8) & 0x100) + 0x8000);
    gState0TypedWork.widths.word86++;
    if (!(gState0TypedWork.widths.word86 & 1)) {
        gCounter6ED08_03001800.toggle1AF ^= 1;
        gCounter6ED08_03001800.frame51++;
    }
    word = gMainSerialOutgoingWork.words[gUnknown_03000B90 ^ 1][1];
    if ((0x8000 & word) && ((u16)(0x100 & word) >> 8) != gCounter6ED08_03001800.toggle1B0) {
        gCounter6ED08_03001800.toggle1B0 ^= 1;
        gCounter6ED08_03001800.received18A[gCounter6ED08_03001800.count52] = word;
        if (++gCounter6ED08_03001800.count52 > 10) {
            gState0TypedWork.widths.word86 = 0;
            gUnknown_0300137C++;
        }
    }
}
