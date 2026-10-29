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
#include "gba.h"
#include "graphics.h"
#include "link_menu.h"
#include "main_callbacks.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "scene_view.h"
#include "sound_samples.h"
#include "sound_voice.h"
#include "sound_work.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_work.h"
#include "tile_text.h"
#include "utility_helpers.h"

struct AnimRecBFB4 {
    u8 timer;
    u8 pos;
    u8 state;
    u8 tile;
    u16 base;
    u16 width;
};
struct AnimViewBFB4 { u8 pad[0x64]; struct AnimRecBFB4 recs[8]; };

extern const u8 gUnknown_083AFC2C[];
extern void sub_0803D4EC(s32 arg0, s32 arg1);

void sub_0801BFB4(const u16 *script, u32 index);
void sub_0803C0CC(void);
void sub_0803C33C(void);

void sub_0801BFB4(const u16 *script, u32 index) {

    u32 running;

    if (((struct AnimViewBFB4 *)&gState0TypedWork)->recs[index].state == 0xFF)
        return;
    running = 1;
    do {
        if (((struct AnimViewBFB4 *)&gState0TypedWork)->recs[index].timer != 0) {
            ((struct AnimViewBFB4 *)&gState0TypedWork)->recs[index].timer--;
            return;
        }
        switch (*(const u8 *)&script[((struct AnimViewBFB4 *)&gState0TypedWork)->recs[index].pos]) {
        case 0xFD:
            sub_08074DE0(script[((struct AnimViewBFB4 *)&gState0TypedWork)->recs[index].pos + 1]);
            ((struct AnimViewBFB4 *)&gState0TypedWork)->recs[index].pos += 2;
            break;
        case 0xFE:
            ((struct AnimViewBFB4 *)&gState0TypedWork)->recs[index].pos = script[((struct AnimViewBFB4 *)&gState0TypedWork)->recs[index].pos + 1] * 2;
            break;
        case 0xFF:
            ((struct AnimViewBFB4 *)&gState0TypedWork)->recs[index].state = 0xFF;
            return;
        default:
            ((struct AnimViewBFB4 *)&gState0TypedWork)->recs[index].timer = script[((struct AnimViewBFB4 *)&gState0TypedWork)->recs[index].pos];
            CpuSet((u8 *)(((struct AnimViewBFB4 *)&gState0TypedWork)->recs[index].base << 5) + (((struct AnimViewBFB4 *)&gState0TypedWork)->recs[index].width * (script[((struct AnimViewBFB4 *)&gState0TypedWork)->recs[index].pos + 1] << 5) + 0x02000000),
                (void *)((((struct AnimViewBFB4 *)&gState0TypedWork)->recs[index].tile << 5) + 0x06010000), (((struct AnimViewBFB4 *)&gState0TypedWork)->recs[index].width << 3) | 0x04000000);
            ((struct AnimViewBFB4 *)&gState0TypedWork)->recs[index].pos += 2;
            break;
        }
    } while (running);
}

void sub_0803C0CC(void) {

    struct FrameObject *object;
    struct FrameObject *third;
    struct FrameObject *other;
    u8 shift;
    u8 kind;
    u32 delta;
    u32 value;
    u32 temp;

    u32 root = (u32)gFrameObjects;
    object = (struct FrameObject *)(root + (gState0TypedWork.bytes[0x12F] << 6));
    if (object->byte2B != 0) {
        object->byte2B--;
        return;
    }
    shift = gUnknown_083AFC2C[gCounter6ED08_03001800.shift38];
    kind = object->unknown23[2];
    if ((u8)(kind - 1) <= 14) {
        delta = object->screenX;
        sub_0804422C(gState0TypedWork.bytes[0x12F]);
        delta = gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX - delta;
        gFrameObjects[gState0TypedWork.bytes[0x12F]].value30 += delta;
        other = &gFrameObjects[gState0TypedWork.bytes[0x12F]];
        if ((u16)other->value30 <= 0x78)
            return;
        if ((u16)other->value30 <= 0x188) {
            delta = other->screenX - 0x78;
            gCounter6ED08_03001800.pos154[0] = (gCounter6ED08_03001800.pos154[0] - delta) & 0x1FF;
            gCounter6ED08_03001800.pos154[2] = (gCounter6ED08_03001800.pos154[2] - delta) & 0x1FF;
            gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX = (gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX - delta) & 0x1FF;
            sub_0803D4EC(1, delta);
            gBgScroll2.x += delta;
            gBgScroll3.x += delta >> shift;
            return;
        }
        temp = (u16)other->value30;
        if (temp - 0x188 < delta) {
            delta = delta + (0x188 - temp);
            gCounter6ED08_03001800.pos154[0] = (gCounter6ED08_03001800.pos154[0] - delta) & 0x1FF;
            gCounter6ED08_03001800.pos154[2] = (gCounter6ED08_03001800.pos154[2] - delta) & 0x1FF;
            gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX = (gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX - delta) & 0x1FF;
            sub_0803D4EC(1, delta);
            gBgScroll2.x += delta;
            gBgScroll3.x += delta >> shift;
            return;
        }
        if (temp > 0x18F)
            other->unknown23[6] = 0;
        return;
    }
    if ((u8)(kind - 0x11) > 14)
        return;
    delta = object->screenX;
    sub_0804422C(gState0TypedWork.bytes[0x12F]);
    delta = delta - gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX;
    gFrameObjects[gState0TypedWork.bytes[0x12F]].value30 = (gFrameObjects[gState0TypedWork.bytes[0x12F]].value30 - delta) & 0x1FF;
    third = &gFrameObjects[gState0TypedWork.bytes[0x12F]];
    value = (u16)third->value30;
    if ((u16)(value - 0x78) <= 0x78)
        return;
    if (value - 0x78 > 0xEF) {
        delta = 0x78 - third->screenX;
        gCounter6ED08_03001800.pos154[0] = (gCounter6ED08_03001800.pos154[0] + delta) & 0x1FF;
        gCounter6ED08_03001800.pos154[2] = (gCounter6ED08_03001800.pos154[2] + delta) & 0x1FF;
        gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX = (gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX + delta) & 0x1FF;
        sub_0803D4EC(0, delta);
        gBgScroll2.x -= delta;
        gBgScroll3.x -= delta >> shift;
        return;
    }
    if (value <= 0x167 && 0x168 - value < delta) {
        delta = delta + (value - 0x168);
        gCounter6ED08_03001800.pos154[0] = (gCounter6ED08_03001800.pos154[0] + delta) & 0x1FF;
        gCounter6ED08_03001800.pos154[2] = (gCounter6ED08_03001800.pos154[2] + delta) & 0x1FF;
        temp = gState0TypedWork.bytes[0x12F];
        gFrameObjects[temp].screenX = (gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX + delta) & 0x1FF;
        sub_0803D4EC(0, delta);
        gBgScroll2.x -= delta;
        gBgScroll3.x -= delta >> shift;
        return;
    }
    if (value <= 0x160)
        gFrameObjects[gState0TypedWork.bytes[0x12F]].unknown23[6] = 0;
}

void sub_0803C33C(void) {

    struct FrameObject *object;
    struct FrameObject *third;
    struct FrameObject *other;
    u8 shift;
    u8 kind;
    u32 delta;
    u32 value;
    u32 temp;

    u32 root = (u32)gFrameObjects;
    object = (struct FrameObject *)(root + (gState0TypedWork.bytes[0x12F] << 6));
    if (object->byte2B != 0) {
        object->byte2B--;
        return;
    }
    shift = gUnknown_083AFC2C[gCounter6ED08_03001800.shift38];
    kind = object->unknown23[2];
    if ((u8)(kind - 1) <= 14) {
        delta = object->screenX;
        sub_0804422C(gState0TypedWork.bytes[0x12F]);
        delta = gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX - delta;
        gFrameObjects[gState0TypedWork.bytes[0x12F]].value30 += delta;
        other = &gFrameObjects[gState0TypedWork.bytes[0x12F]];
        if ((u16)other->value30 <= 0x78)
            return;
        if ((u16)other->value30 <= 0x188) {
            delta = other->screenX - 0x78;
            gCounter6ED08_03001800.pos154[0] = (gCounter6ED08_03001800.pos154[0] - delta) & 0x1FF;
            gCounter6ED08_03001800.pos154[2] = (gCounter6ED08_03001800.pos154[2] - delta) & 0x1FF;
            gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX = (gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX - delta) & 0x1FF;
            sub_0803D4EC(1, delta);
            gBgScroll0.x += delta;
            gBgScroll1.x += delta;
            gBgScroll2.x += delta;
            gBgScroll3.x += delta >> shift;
            return;
        }
        temp = (u16)other->value30;
        if (temp - 0x188 < delta) {
            delta = delta + (0x188 - temp);
            gCounter6ED08_03001800.pos154[0] = (gCounter6ED08_03001800.pos154[0] - delta) & 0x1FF;
            gCounter6ED08_03001800.pos154[2] = (gCounter6ED08_03001800.pos154[2] - delta) & 0x1FF;
            gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX = (gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX - delta) & 0x1FF;
            sub_0803D4EC(1, delta);
            gBgScroll0.x += delta;
            gBgScroll1.x += delta;
            gBgScroll2.x += delta;
            gBgScroll3.x += delta >> shift;
            return;
        }
        if (temp > 0x18F)
            other->unknown23[6] = 0;
        return;
    }
    if ((u8)(kind - 0x11) > 14)
        return;
    delta = object->screenX;
    sub_0804422C(gState0TypedWork.bytes[0x12F]);
    delta = delta - gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX;
    gFrameObjects[gState0TypedWork.bytes[0x12F]].value30 = (gFrameObjects[gState0TypedWork.bytes[0x12F]].value30 - delta) & 0x1FF;
    third = &gFrameObjects[gState0TypedWork.bytes[0x12F]];
    value = (u16)third->value30;
    if ((u16)(value - 0x78) <= 0x78)
        return;
    if (value - 0x78 > 0xEF) {
        delta = 0x78 - third->screenX;
        gCounter6ED08_03001800.pos154[0] = (gCounter6ED08_03001800.pos154[0] + delta) & 0x1FF;
        gCounter6ED08_03001800.pos154[2] = (gCounter6ED08_03001800.pos154[2] + delta) & 0x1FF;
        gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX = (gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX + delta) & 0x1FF;
        sub_0803D4EC(0, delta);
        gBgScroll0.x -= delta;
        gBgScroll1.x -= delta;
        gBgScroll2.x -= delta;
        gBgScroll3.x -= delta >> shift;
        return;
    }
    if (value <= 0x167 && 0x168 - value < delta) {
        delta = delta + (value - 0x168);
        gCounter6ED08_03001800.pos154[0] = (gCounter6ED08_03001800.pos154[0] + delta) & 0x1FF;
        gCounter6ED08_03001800.pos154[2] = (gCounter6ED08_03001800.pos154[2] + delta) & 0x1FF;
        temp = gState0TypedWork.bytes[0x12F];
        gFrameObjects[temp].screenX = (gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX + delta) & 0x1FF;
        sub_0803D4EC(0, delta);
        gBgScroll0.x -= delta;
        gBgScroll1.x -= delta;
        gBgScroll2.x -= delta;
        gBgScroll3.x -= delta >> shift;
        return;
    }
    if (value <= 0x160)
        gFrameObjects[gState0TypedWork.bytes[0x12F]].unknown23[6] = 0;
}
