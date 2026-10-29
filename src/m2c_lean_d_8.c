/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "encounter_choices.h"
#include "frame.h"
#include "frame_command_data.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "sprite_layouts.h"
#include "state0_work.h"
#include "tile_text.h"

extern const u8 gUnknown_083AFC2C[];

void sub_0803BE44(void);

/* Scroll positions wrap at 512 pixels. */
static inline u16 WrapScroll9(u32 value)
{
    return value & 0x1FF;
}

/* Same wrap on a halfword sum: keeps the sum in 16 bits, which loads the
   addend before the position and the 0x1FF mask right before the AND. */
static inline u16 WrapScroll9Half(u16 value)
{
    return value & 0x1FF;
}

void sub_0803BE44(void) {

    struct FrameObject *object;
    struct FrameObject *other;
    struct FrameObject *third;
    u8 shift;
    u32 delta;
    u32 value;
    u32 value1;

    shift = gUnknown_083AFC2C[gCounter6ED08_03001800.shift38];
    {
        u32 root = (u32)gFrameObjects;
        object = (struct FrameObject *)(root + (gState0TypedWork.bytes[0x12F] << 6));
    }
    if (object->unknown2C[0] == 0) {
        gCounter6ED08_03001800.pos154[0] = WrapScroll9Half(gCounter6ED08_03001800.pos154[0] + object->byte2B);
        gFrameObjects[gState0TypedWork.bytes[0x12F]].value30 += gFrameObjects[gState0TypedWork.bytes[0x12F]].byte2B;
        other = &gFrameObjects[gState0TypedWork.bytes[0x12F]];
        if ((u16)other->value30 <= 0x78)
            return;
        if ((u16)other->value30 <= 0x188) {
            delta = (s16)gCounter6ED08_03001800.pos154[0] - 0x78;
            {
                u32 a = gCounter6ED08_03001800.pos154[0] - delta;
                u32 b = gCounter6ED08_03001800.pos154[2] - delta;
                gCounter6ED08_03001800.pos154[0] = WrapScroll9(a);
                gCounter6ED08_03001800.pos154[2] = WrapScroll9(b);
            }
            gBgScroll2.x += delta;
            gBgScroll3.x += delta >> shift;
            return;
        }
        value1 = (u16)other->value30;
        if ((s32)(value1 - 0x188) < other->byte2B) {
            delta = other->byte2B + (0x188 - value1);
            {
                u32 a = gCounter6ED08_03001800.pos154[0] - delta;
                u32 b = gCounter6ED08_03001800.pos154[2] - delta;
                gCounter6ED08_03001800.pos154[0] = WrapScroll9(a);
                gCounter6ED08_03001800.pos154[2] = WrapScroll9(b);
            }
            gBgScroll2.x += delta;
            gBgScroll3.x += delta >> shift;
            return;
        }
        if (value1 > 0x18F)
            other->unknown23[6] = 0;
        return;
    }
    gCounter6ED08_03001800.pos154[2] = WrapScroll9Half(gCounter6ED08_03001800.pos154[2] - object->byte2B);
    gFrameObjects[gState0TypedWork.bytes[0x12F]].value30 -= gFrameObjects[gState0TypedWork.bytes[0x12F]].byte2B;
    third = &gFrameObjects[gState0TypedWork.bytes[0x12F]];
    value = (u16)third->value30; value &= 0x1FF;
    if ((u16)(third->value30 - 0x78) <= 0x78)
        return;
    if (value - 0x78 > 0xEF) {
        delta = 0x78 - (s16)gCounter6ED08_03001800.pos154[2];
        {
            u32 b = gCounter6ED08_03001800.pos154[2] + delta;
            u32 a = gCounter6ED08_03001800.pos154[0] + delta;
            gCounter6ED08_03001800.pos154[0] = WrapScroll9(a);
            gCounter6ED08_03001800.pos154[2] = WrapScroll9(b);
        }
        gBgScroll2.x -= delta;
        gBgScroll3.x -= delta >> shift;
        return;
    }
    if (value <= 0x167 && 0x168 - value < third->byte2B) {
        delta = third->byte2B + (value - 0x168);
        {
            u32 b = gCounter6ED08_03001800.pos154[2] + delta;
            u32 a = gCounter6ED08_03001800.pos154[0] + delta;
            gCounter6ED08_03001800.pos154[0] = WrapScroll9(a);
            gCounter6ED08_03001800.pos154[2] = WrapScroll9(b);
        }
        gBgScroll2.x -= delta;
        gBgScroll3.x -= delta >> shift;
        return;
    }
    if (value <= 0x160)
        gFrameObjects[gState0TypedWork.bytes[0x12F]].unknown23[6] = 0;
}
