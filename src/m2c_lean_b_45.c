/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "main_callbacks.h"

struct BattleView6D138 { u8 pad00[0xE]; s8 byte0E; };

extern const s8 gUnknown_08485924[];
extern s32 sub_0807CD2C(s32, s32);
extern struct BattleView6D138 gBattleView6D138 asm("gCounter6ED08_03001800");

void sub_0806D138(void);

void sub_0806D138(void) {

    s32 t;

    t = gFrameObjects[0].unknown1A;
    if (gFrameObjects[0].commandDelay != 1)
        return;
    if (t > 0x2F) {
        if (t <= 0x3F) {
            gFrameObjects[0].screenY += 6;
        } else if (t <= 0x5F) {
            s32 k = 0xF & t;
            if (k == 0)
                gFrameObjects[0].commandOffset++;
            gFrameObjects[0].screenY = 0x50 - gUnknown_08485924[k * 4] / gFrameObjects[0].commandOffset;
        }
    }
    if (gBattleView6D138.byte0E > 0x23) {
        if (0x10 & t) {
            if (8 & t)
                gFrameObjects[0x20].frameAndGroup = 0xA;
        } else {
            gFrameObjects[0x20].frameAndGroup = 8;
        }
        if (0x20 & t) {
            s32 k = 0x1F & t;
            if (k <= 7)
                gFrameObjects[0x2E].screenX = gFrameObjects[0x20].screenX + 0x10;
            else if (k > 0x17)
                gFrameObjects[0x2E].screenX = gFrameObjects[0x20].screenX - 0x10;
            else
                gFrameObjects[0x2E].screenX = gFrameObjects[0x20].screenX - (s16)((((t - 8) * 2) & 0x1F) - 0x10);
            gFrameObjects[0x2E].screenY = 0x12;
            gFrameObjects[0x2F].screenX = gFrameObjects[0x20].screenX + (s16)((t & 0x1F) - 0x10);
            gFrameObjects[0x2F].screenY = 0x12 - (gUnknown_08485924[(t * 2) & 0x3F] >> 1);
        } else {
            gFrameObjects[0x2E].screenX = gFrameObjects[0x20].screenX + (s16)((t & 0x1F) - 0x10);
            gFrameObjects[0x2E].screenY = 0x12 - (gUnknown_08485924[(t * 2) & 0x3F] >> 1);
            {
            s32 k = 0x1F & t;
            if (k <= 7)
                gFrameObjects[0x2F].screenX = gFrameObjects[0x20].screenX + 0x10;
            else if (k > 0x17)
                gFrameObjects[0x2F].screenX = gFrameObjects[0x20].screenX - 0x10;
            else
                gFrameObjects[0x2F].screenX = gFrameObjects[0x20].screenX - (s16)((((t - 8) * 2) & 0x1F) - 0x10);
            }
            gFrameObjects[0x2F].screenY = 0x12;
        }
        gFrameObjects[0x36].screenX = gFrameObjects[0x2E].screenX;
        gFrameObjects[0x37].screenX = gFrameObjects[0x2F].screenX;
        return;
    }
    {
    s32 frame;
    struct FrameObject *objs;
    if (gBattleView6D138.byte0E > 0) {
        if (0x10 & t)
            gFrameObjects[0x20].screenY = 0x10 - gUnknown_08485924[(0xF & t) * 4] / 4;
        objs = gFrameObjects;
        if (!(0x10 & t))
            frame = (t & 8) ? 8 : 7;
        else
            frame = 9;
    } else {
        objs = gFrameObjects;
        if (!(8 & t))
            frame = (t & 0x10) ? 0xA : 0xC;
        else
            frame = 8;
    }
    *(u16 *)((u8 *)objs + 0x806) = frame;
    }
}
