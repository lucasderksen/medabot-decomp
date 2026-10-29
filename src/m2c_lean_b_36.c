/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "continued_late_graphics.h"
#include "effect_work.h"
#include "frame.h"
#include "gba.h"
#include "link_menu.h"
#include "main.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "serial.h"
#include "sound_voice.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct LinkContext65B0C { u8 pad00[8]; s32 state08; u8 pad0C[0x2E]; u16 timer3A; u8 pad3C[0xD]; u8 ready49; };
struct DmaRegs68CC8 { u32 source, destination, control; };

extern s32 gTransferStep03000000;
extern s32 sub_0807CD2C(s32, s32);
extern s32 sub_0807CDF8(s32, s32);
extern struct LinkContext65B0C *gLinkContext65B0C asm("gMainContextPointer_03006F74");
extern u16 *gUnknown_0300002C;
extern u16 gUnknown_0202FC00[];
extern u16 gUnknown_03000028;
extern u8 gTransferDivisor03000005;
extern void sub_0805BB0C(void);

void sub_08065B0C(void);
s32 sub_08068CC8(void);
void sub_0806C084(void);

void sub_08065B0C(void) {

    u16 tag = 0xFF40;
    s16 timer;

    if (!(gMainSerialOutgoingWork.polledBits & 0xF00) && !(gFrameCounter & 0xF))
        sub_080020C8();
    sub_08002190();
    sub_0805BB0C();
    gMainSerialOutgoingWork.word06 = gLinkContext65B0C->ready49 | tag;
    if (gMainSerialOutgoingWork.words[gUnknown_03000B90][1] == (tag | 1)) {
        if (gMainSerialOutgoingWork.words[gUnknown_03000B90 == 0][1] == (tag | 1)) {
            if (gUnknown_03000B90 <= 1) {
                gUnknown_0300137C++;
                gLinkContext65B0C->timer3A = 0;
                gMainFlag_03005030 = -1;
                return;
            }
            sub_0803FB0C();
            gLinkContext65B0C->state08 = 1;
            gUnknown_0300137C--;
            gMainSerialOutgoingWork.word06 = 0;
        }
    } else if ((gMainSerialOutgoingWork.polledBits & 3) == 3) {
        if (gMainSerialOutgoingWork.words[gUnknown_03000B90 == 0][1] == tag
            || gMainSerialOutgoingWork.words[gUnknown_03000B90 == 0][1] == (tag | 1)) {
            gMainSerialOutgoingWork.word06 = tag | 1;
            gLinkContext65B0C->ready49 = 1;
            return;
        }
    }
    timer = ++gLinkContext65B0C->timer3A;
    if (timer > 0x12C) {
        do {
            sub_0803FB0C();
            gLinkContext65B0C->state08 = 1;
        } while (0);
        gUnknown_0300137C--;
        gMainSerialOutgoingWork.word06 = 0;
        return;
    }
    if (timer > 0x10C) {
        if (gMainSerialOutgoingWork.words[gUnknown_03000B90 == 0][1] == tag) {
            gLinkContext65B0C->timer3A = 0;
            return;
        }
        gMainSerialOutgoingWork.word06 = 0;
    }
}

s32 sub_08068CC8(void) {

    s32 w, i;
    u32 inv;
    s32 step;
    u8 div;
    if (gTransferStep03000000 == gTransferDivisor03000005 << 5)
        return 1;
    step = gTransferStep03000000;
    div = gTransferDivisor03000005;
    if (sub_0807CDF8(step, div) == 0) {
        w = sub_0807CD2C(step, div);
        inv = 0x20 - w;
        if (w <= 0) {
            volatile struct DmaRegs68CC8 *dma = (void *)0x040000D4;
            dma->source = 0x05000000;
            dma->destination = (u32)gUnknown_0300002C;
            dma->control = 0x84000100;
            (void)dma->control;
        } else {
            for (i = 0; i <= 0x1FF; i++) {
                gUnknown_0202FC00[i] = (((0x1F & gUnknown_0300002C[i]) * (s32)inv + (0x1F & gUnknown_03000028) * w) >> 5)
                    + ((((0x3E0 & gUnknown_0300002C[i]) * (s32)inv + (0x3E0 & gUnknown_03000028) * w) >> 5) & 0x3E0)
                    + ((((0x7C00 & gUnknown_0300002C[i]) * (s32)inv + (0x7C00 & gUnknown_03000028) * w) >> 5) & 0x7C00);
            }
            {
                volatile struct DmaRegs68CC8 *dma = (void *)0x040000D4;
                dma->source = (u32)gUnknown_0202FC00;
                dma->destination = 0x05000000;
                dma->control = 0x84000100;
                (void)dma->control;
            }
        }
    }
    return 0;
}

void sub_0806C084(void) {

    u32 root = (u32)gFrameObjects;
    u8 *delay = &((struct FrameObject *)root)[0x20].commandDelay;

    switch (*delay) {
    case 0:
        break;
    case 3:
        if (++gFrameObjects[0x20].unknown1A == 0x14) {
            gFrameObjects[0x20].commandDelay = 0;
            gFrameObjects[0x20].commandOffset = 0;
            gFrameObjects[0x20].unknown1A = 0;
            gFrameObjects[0x1F].screenY = 0xC8;
        }
        break;
    case 1:
        if (gFrameObjects[0x1E].commandOffset != 0)
            goto next;
        gFrameObjects[0x1F].screenX = gFrameObjects[0x20].screenX;
        gFrameObjects[0x1F].screenY = 0x18;
        break;
    case 2:
        if (gFrameObjects[0x20].unknown1A++ > 7)
            goto next;
        switch (gFrameObjects[0x20].commandOffset) {
        case 0:
            gFrameObjects[0x20].screenX -= 2;
            if (gFrameObjects[0x20].screenX <= 0x6B)
                gFrameObjects[0x20].screenX = 0x6C;
            gFrameObjects[0x1F].screenX = gFrameObjects[0x20].screenX - gFrameObjects[0x20].unknown1A - 2;
            break;
        case 1:
            if (gFrameObjects[0x20].screenX <= 0x77) {
                gFrameObjects[0x20].screenX += 2;
                if (gFrameObjects[0x20].screenX > 0x78)
                    gFrameObjects[0x20].screenX = 0x78;
            } else if (gFrameObjects[0x20].screenX > 0x78) {
                gFrameObjects[0x20].screenX -= 2;
                if (gFrameObjects[0x20].screenX <= 0x77)
                    gFrameObjects[0x20].screenX = 0x78;
            }
            gFrameObjects[0x1F].screenX = gFrameObjects[0x20].screenX;
            break;
        case 2:
            gFrameObjects[0x20].screenX += 2;
            if (gFrameObjects[0x20].screenX > 0x84)
                gFrameObjects[0x20].screenX = 0x84;
            gFrameObjects[0x1F].screenX = gFrameObjects[0x20].screenX + gFrameObjects[0x20].unknown1A + 2;
            break;
        }
        gFrameObjects[0x1F].screenY = gFrameObjects[0x20].unknown1A <= 3 ? 0x12 : 0xA;
        break;
    next:
        *delay = 3;
        break;
    }
}
