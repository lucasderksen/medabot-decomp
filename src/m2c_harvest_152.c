/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "display_effects.h"
#include "display_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct ContinuedSetup1B76C { u8 prefix[0x58]; u8 slot0; u8 unknown59[0x18]; u8 slot1; u8 unknown72[0x17]; u8 slot2; u8 unknown8A[0x3F]; u8 type; u8 ca; u8 tail[0x35]; };

extern const u8 *const gUnknown_083C4B90[];
extern u8 gDebugMenuTextBuffer[0x53]; /* Observed encompassing text and scratch bytes. */
extern void sub_0803F684(u32, u32, u32);
extern void sub_0803F998(u32, u32, u32);
s32 sub_08016E5C(u32, s32);

void sub_08017268(void);
void sub_0801B76C(void);
void sub_0803CECC(void);

void sub_08017268(void) {
    u8 *scratch;
    const void *source;
    sub_08040D0C(0x14,0x10);
    switch(gState0TransferWork.bytes[0x82]) {
    case 0:
        sub_08041D04(gUnknown_083C4B90[3],gDebugMenuTextBuffer,14);
        break;
    case 1: {
        u8 *record=gSetupBuffer_03000590;
        record+=gState0TransferWork.bytes[0x80]<<8;
        if(record[5]>9) {
            sub_08041D04(gUnknownBytes_083B7F8C+record[1]*3,scratch=gDebugMenuTextBuffer+0x50,3);
            source=gUnknownPointers_083B74B8[scratch[0]];
            scratch-=0x50;
            sub_0803F63C(source,scratch,17);
        } else sub_08042678(gDebugMenuTextBuffer,13);
        break;
    }
    case 2: {
        u8 *record=gSetupBuffer_03000590;
        record+=gState0TransferWork.bytes[0x80]<<8;
        if(record[5]>29) {
            sub_08041D04(gUnknownBytes_083B7F8C+record[1]*3,scratch=gDebugMenuTextBuffer+0x50,3);
            source=gUnknownPointers_083B74B8[scratch[1]];
            scratch-=0x50;
            sub_0803F63C(source,scratch,17);
        } else sub_08042678(gDebugMenuTextBuffer,13);
        break;
    }
    case 3: {
        u8 *record=gSetupBuffer_03000590;
        record+=gState0TransferWork.bytes[0x80]<<8;
        if(record[5]>59) {
            sub_08041D04(gUnknownBytes_083B7F8C+record[1]*3,scratch=gDebugMenuTextBuffer+0x50,3);
            source=gUnknownPointers_083B74B8[scratch[2]];
            scratch-=0x50;
            sub_0803F63C(source,scratch,17);
        } else sub_08042678(gDebugMenuTextBuffer,13);
        break;
    }
    }
    sub_08040DB8(gDebugMenuTextBuffer,20,10,17,10,13,0,0);
}

void sub_0801B76C(void) {
    u8 subtype;
    struct ContinuedSetup1B76C *setup;
    u8 *firstRecord;
    u8 *secondRecord;
    u8 *thirdRecord;

    gState0TransferWork.bytes[0x15C] = 0;
    gState0TransferWork.bytes[0x15D] = 0U;
    gState0TransferWork.bytes[0x15E] = 0;
    setup=(struct ContinuedSetup1B76C *)gSetupBuffer_03000590;
    if (setup[gState0TransferWork.bytes[0x80]].slot0 == 0) {
        gState0TransferWork.bytes[0x15C] = 4;
    }
    if (sub_08016E5C(gState0TransferWork.bytes[0x80], 0) != 0) {
        gState0TransferWork.bytes[0x15C] = 3;
    }
    firstRecord = gSetupBuffer_03000590;
    firstRecord += gState0TransferWork.bytes[0x80] << 8;
    if ((firstRecord[0xC9] == 0x2B) && (firstRecord[0xCA] == 1)) {
        gState0TransferWork.bytes[0x15C] = 2;
    }
    if (sub_08016E5C(gState0TransferWork.bytes[0x80], 1) != 0) {
        gState0TransferWork.bytes[0x15D] = 3U;
    }
    {
        u8 *recordBase=gSetupBuffer_03000590;
        u32 recordOffset=gState0TransferWork.bytes[0x80]<<8;
        secondRecord=recordOffset+recordBase;
    }
    if (secondRecord[0xC9] == 0x2B) {
        subtype = secondRecord[0xCA];
        if (subtype == 2) {
            gState0TransferWork.bytes[0x15D] = subtype;
        }
    }
    setup=(struct ContinuedSetup1B76C *)gSetupBuffer_03000590;
    if (setup[gState0TransferWork.bytes[0x80]].slot1 == 0) {
        gState0TransferWork.bytes[0x15D] = 1U;
    }
    if (sub_08016E5C(gState0TransferWork.bytes[0x80], 2) != 0) {
        gState0TransferWork.bytes[0x15E] = 3;
    }
    thirdRecord = gSetupBuffer_03000590;
    thirdRecord += gState0TransferWork.bytes[0x80] << 8;
    if ((thirdRecord[0xC9] == 0x2B) && (thirdRecord[0xCA] == 3)) {
        gState0TransferWork.bytes[0x15E] = 2;
    }
    {
        struct ContinuedSetup1B76C *lastSetup=(struct ContinuedSetup1B76C *)gSetupBuffer_03000590;
        if(lastSetup[gState0TransferWork.bytes[0x80]].slot2==0)gState0TransferWork.bytes[0x15E]=1;
    }
}

void sub_0803CECC(void) {
    struct FrameObject *frames = gFrameObjects;
    u8 *work;
    u8 *selected;
    u32 highBits;
    struct FrameObject *temp_r1;
    struct FrameObject *temp_r2;
    struct FrameObject *temp_r2_2;
    u8 temp_r0;
    u8 temp_r0_2;
    u32 rawCounter;

    work = gState0TypedWork.bytes;
    selected = work + 0x12F;
    temp_r2 = &frames[*selected];
    temp_r0 = temp_r2->byte2B;
    if (temp_r0 != 0) {
        temp_r2->byte2B = temp_r0 - 1;
        return;
    }
    highBits = (temp_r2->unknown2C[2] << 0xA) | (temp_r2->unknown2C[1] << 5);
    sub_0803F684((u16)(temp_r2->unknown2C[0] | highBits), (u32) temp_r2->unknown2C[3], 0xFDFFU);
    temp_r2_2 = &frames[*selected];
    highBits = (temp_r2_2->unknown2C[2] << 0xA) | (temp_r2_2->unknown2C[1] << 5);
    sub_0803F998((u16)(temp_r2_2->unknown2C[0] | highBits), (u32) temp_r2_2->unknown2C[3], 0xB00FU);
    temp_r1 = &frames[*selected];
    rawCounter = temp_r1->unknown2C[3];
    temp_r0_2 = rawCounter;
    if (temp_r0_2 == 0) {
        temp_r1->unknown23[6] = temp_r0_2;
        return;
    }
    temp_r1->unknown2C[3] = rawCounter - 1;
}
