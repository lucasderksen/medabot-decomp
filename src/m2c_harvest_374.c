/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "record_helpers.h"
#include "sprite_layouts.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct SetupRecord21C94 {u8 prefix[0x40];u8 active;u8 tail[0xBF];};

extern const u8 *const gState0NextCommands_083B6100[];

void sub_08021C94(void);

void sub_08021C94(void) {

    u32 recordIndex;
    u32 frame0Index;
    u32 frame1Index;
    u32 frame2Index;
    u32 frame3Index;
    const u8 *const *commandSlot;
    struct BgScroll *scroll3;
    u32 frameOffset,zeroByte;
    u8 *setupBase;
    u8 *frame3Byte23;
    u32 activeAddress;
    u8 *frame0Byte23;
    u8 *frame1Byte23;
    u8 *frame2Byte23;

    gState0TypedWork.widths.word86 += 1;
    sub_080353AC((u32) gState0TypedWork.widths.word86);
    recordIndex = 0;
    frame3Index = 0x5D;
    frame2Index = 0x5C;
    frame1Index = 0x5B;
    frame0Index = 0x5A;
    do {
        setupBase=gSetupBuffer_03000590;
        if (((struct SetupRecord21C94 *)setupBase)[recordIndex].active != 0) {
            sub_08036AC4(frame0Index, 0U);
            sub_08036AC4(frame1Index, 0U);
            sub_08036AC4(frame2Index, 0U);
            sub_08036AC4(frame3Index, 0U);
        }
        frame3Index += 4;
        frame2Index += 4;
        frame1Index += 4;
        frame0Index += 4;
        recordIndex += 1;
    } while (recordIndex <= 5U);
    commandSlot=gState0NextCommands_083B6100;
    commandSlot+=0x23;
    sub_08040BD8(*commandSlot, 0x21U);
    sub_08040BD8(*commandSlot, 0x22U);
    sub_08040BD8(*commandSlot, 0x23U);
    if (gFrameObjects[0x21].commandStopped == 0xFF) {
        recordIndex = 0;
        scroll3=&gBgScroll3;
        zeroByte=0;
        frame3Byte23 = (u8 *)&gFrameObjects+0x1763;
        frameOffset=0x1723;
        frame2Byte23=(u8 *)&gFrameObjects+frameOffset;
        frameOffset-=0x40;
        frame1Byte23=(u8 *)&gFrameObjects+frameOffset;
        frameOffset-=0x40;
        frame0Byte23=(u8 *)&gFrameObjects+frameOffset;
        activeAddress = (u32)gSetupBuffer_03000590 + 0x40U;
        do {
            if (*(u8 *)activeAddress != 0) {
                *frame0Byte23 = zeroByte;
                *frame1Byte23 = zeroByte;
                *frame2Byte23 = zeroByte;
                *frame3Byte23 = zeroByte;
            }
            frame3Byte23 += 0x100;
            frame2Byte23 += 0x100;
            frame1Byte23 += 0x100;
            frame0Byte23 += 0x100;
            activeAddress += 0x100U;
            recordIndex += 1;
        } while (recordIndex <= 5U);
        scroll3->y = 0;
        sub_08040CD0(0x21U, 3U);
        gState0TransferWork.bytes[0xAA] = (u8) (gState0TransferWork.bytes[0xAA] + 1);
    }
}
