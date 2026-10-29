/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "coordinate_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "state0_work.h"
#include "tile_text.h"

extern const u8*const gUnknown_083B6100[];

void sub_0803D15C(void);

void sub_0803D15C(void) {

    union{struct TileCoordinates coordinates;s32 word;} result;
    struct FrameObject *temp_r0_2;
    struct FrameObject *temp_r0_3;
    struct FrameObject *temp_r0_4;
    struct FrameObject *temp_r1;
    struct FrameObject *temp_r1_2;
    struct FrameObject *temp_r1_3;
    struct FrameObject *temp_r1_4;
    struct FrameObject *temp_r3;
    u8 *var_r1;
    u8 temp_r0;
    u32 frameRoot;
    u32 var_r0;

    sub_08040BD8(gUnknown_083B6100[gFrameObjects[gState0TypedWork.bytes[0x12F]].unknown2C[1]], gState0TypedWork.bytes[0x12F]);
    temp_r1 = &gFrameObjects[gState0TypedWork.bytes[0x12F]];
    if ((u32) temp_r1->byte2B <= 6U) {
        temp_r1->scaleX += 8;
        temp_r1_2 = &gFrameObjects[gState0TypedWork.bytes[0x12F]];
        temp_r1_2->scaleY += 8;
    }
    temp_r1_3 = &gFrameObjects[gState0TypedWork.bytes[0x12F]];
    if ((u32) temp_r1_3->byte2B > 0x3CU) {
        temp_r0 = temp_r1_3->scaleX;
        if (temp_r0 == 8) {
            sub_08040CD0(gState0TypedWork.bytes[0x12F], 1U);
        } else {
            temp_r1_3->scaleX = temp_r0 - 4;
            temp_r1_4 = &gFrameObjects[gState0TypedWork.bytes[0x12F]];
            temp_r1_4->scaleY -= 4;
        }
    }
    frameRoot=(u32)gFrameObjects;
    temp_r3=(struct FrameObject*)(frameRoot+((u32)gState0TypedWork.bytes[0x12F]<<6));
    if(temp_r3->unknown23[0]==0){if(!(1u&temp_r3->byte2B)){temp_r3->unknown23[4]--;}}else if(!(1u&temp_r3->byte2B)){temp_r3->unknown23[4]++;}
    temp_r0_2 = &gFrameObjects[gState0TypedWork.bytes[0x12F]];
    temp_r0_2->unknown23[3] += 4;
    temp_r0_3 = &gFrameObjects[gState0TypedWork.bytes[0x12F]];
    temp_r0_3->byte2B += 1;
    temp_r0_4 = &gFrameObjects[gState0TypedWork.bytes[0x12F]];
    result.coordinates=sub_08042BC0((u32)temp_r0_4->unknown23[3],(u32)temp_r0_4->unknown23[4],(u32)gFrameObjects[0xA].screenX,(s32)gFrameObjects[0xA].screenY);
    gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX = (s16)result.word;
    gFrameObjects[gState0TypedWork.bytes[0x12F]].screenY = (s16) (result.word >> 0x10);
}
