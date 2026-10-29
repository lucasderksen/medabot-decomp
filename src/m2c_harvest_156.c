/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "compression.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "display_effects.h"
#include "effect_work.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "input.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "utility_helpers.h"

struct ContinuedTransfer1ECC0 {u8 prefix[0x87];u8 bank,target;u8 pad89[2];u8 activePart;u8 pad8C[0x1B];u8 selection;u8 padA8[0x22];u16 amount;u8 padCC[4];u8 savedPart;};
struct ContinuedScaleFrame21 {
 u8 prefix[0x840];u16 flags;s16 screenX,screenY;u16 frameAndGroup;u8 scaleX,scaleY,palette,priority;
 u8 gapC[0xC];u16 angle,unknown1A;u8 tableSelector,affineIndex;u8 gap1E[6];u8 kind;u8 gap25[0xB];u16 savedX;s16 savedY;u8 gap34[0xC];
};
struct LocalSerialContext65ED0 {
    u8 unknown00[0x3A];
    s16 phase3A;
    u8 unknown3C[0x3F];
    u8 flag7B;
    u8 flag7C;
};

extern const u8 *const gState0NextCommands_083B6100[];
extern const u8 gActionMotionPalette_0850F8D8[32];
extern void sub_08036B84(u32,u32);

void sub_0801ECC0(void);
void sub_08024890(void);
void sub_08041B1C(void);
void sub_08061468(void);
void sub_08065A94(void);
void sub_08065ED0(void);

void sub_0801ECC0(void) {
    struct ContinuedTransfer1ECC0 *work=(struct ContinuedTransfer1ECC0 *)&gState0TransferWork;
    u8 *setup;
    s32 offset;
    s32 selection;
    sub_08035528(work->bank);
    sub_080355C4(work->bank);
    work->savedPart=work->activePart;
    setup=gSetupBuffer_03000590;
    selection=work->selection*24;
    offset=work->bank<<8;
    selection+=offset;
    if(setup[selection+0x49]==0x30)sub_08036B84(work->target,work->activePart);
    else {
        if(setup[offset+0xD6]&2) work->amount+=10;
        sub_08034F68(work->target,work->activePart,work->amount);
    }
    gState0TransferWork.bytes[0xAA]++;
}

void sub_08024890(void) {
    struct ContinuedScaleFrame21 *frames;
    u8 *work;
    u16 bankIndex,partIndex; /* Byte inputs give maxima1020 and345 before their sum. */
    u32 zero;
    LeDecompress(gActionMotionAsset_084CDF48,(void *)0x06014800);
    CpuFastSet(gActionMotionPalette_0850F8D8,(void *)0x050002E0,8);
    frames=(struct ContinuedScaleFrame21 *)gFrameObjects;
    frames->flags=(zero=0,0xC004);
    frames->tableSelector=zero;
    work=gState0TransferWork.bytes;
    bankIndex=work[0x88]*4;
    partIndex=work[0xD0]+0x5A;
    frames->screenX=(u16)gFrameObjects[bankIndex+partIndex].screenX;
    bankIndex=work[0x88]*4;
    partIndex=work[0xD0]+0x5A;
    frames->screenY=(u16)gFrameObjects[bankIndex+partIndex].screenY;
    frames->palette=7;
    frames->priority=0xF0;
    sub_08040B90(gState0NextCommands_083B6100[0x22],0x21);
    work[0xAA]++;
}

void sub_08041B1C(void) {
    u8 *firstWork = gState0TypedWork.bytes;
    u8 *work;
    u32 counter;
    struct FrameObject *temp_r1;
    u8 *var_r1_2;

    counter = firstWork[0x84];
    work = firstWork;
    if (counter != 0x1E) {
        if ((counter & 4u) & counter) {
            struct FrameObject *frames = gFrameObjects;
            struct FrameObject *frame = &frames[firstWork[0x2B]];
            frame->flags &= 0xBFFF;
        } else {
            struct FrameObject *frames = gFrameObjects;
            struct FrameObject *frame = &frames[firstWork[0x2B]];
            frame->flags |= 0x4000;
        }
        var_r1_2 = work + 0x84;
    } else {
        struct FrameObject *frames = gFrameObjects;
        temp_r1 = &frames[firstWork[0x2B]];
        temp_r1->flags |= 0x4000;
        var_r1_2 = firstWork + 0x29;
    }
    *var_r1_2 += 1;
}

void sub_08061468(void) {
    if ((u32) gState0TypedWork.bytes[0x84] <= 8U) {
        sub_0803F684(0U, gState0TypedWork.bytes[0x84] * 4, 0xFFFFU);
        sub_0803F998(0U, gState0TypedWork.bytes[0x84] * 4, 0xFFFFU);
        gState0TypedWork.bytes[0x84] += 1;
        return;
    }
    *(volatile u16 *)0x04000000 &= 0xFDFF;
    *(volatile u16 *)0x04000000 &= 0xFBFF;
    *(volatile u16 *)0x04000000 &= 0xF7FF;
    sub_08040CD0(0U, 0x80U);
    sub_080476E8(3U);
}

void sub_08065A94(void) {
    s32 temp_r2;
    s32 phase;
    s32 var_r1;
    const u8 *scripts;

    scripts = (const u8 *)gMain2ScriptSlots_08485678;
    phase = (*(s32 *)((u8 *)(gMainContextPointer_03006F74) + 8));
    var_r1 = 0x10;
    if (phase != 0) {
        var_r1 = 0x14;
    }
    if (sub_0803FB3C(*(const void *const *)(scripts + var_r1)) != 0) {
        temp_r2 = (*(s32 *)((u8 *)(gMainContextPointer_03006F74) + 8));
        if (temp_r2 == 0) {
            gUnknown_0300137C += 1;
            (*(s16 *)((u8 *)(gMainContextPointer_03006F74) + 0x3A)) = (s16) temp_r2;
            return;
        }
        if (1 & *(u8 *)&gNewKeys) {
            sub_08074DE0(0xDU);
            gState0TypedWork.bytes[0x84] = 0;
            gState0TypedWork.bytes[0x1B] = 0;
            gUnknown_0300137C -= 2;
        }
    }
}

void sub_08065ED0(void) {
    if (gUnknown_03000B90 != 0) {
        switch ((u32)((struct LocalSerialContext65ED0 *)gMainContextPointer_03006F74)->phase3A) { case 0:
        if ((s32)sub_080440B4() <= 1) { ((struct LocalSerialContext65ED0 *)gMainContextPointer_03006F74)->flag7B=0; gMainSerialOutgoingWork.word06=0xFF02; }
        else { ((struct LocalSerialContext65ED0 *)gMainContextPointer_03006F74)->flag7B=0xFF; gMainSerialOutgoingWork.word06=0xFF03; }
        if (gMainSerialOutgoingWork.words[0][1] == 0xFF04) ((struct LocalSerialContext65ED0 *)gMainContextPointer_03006F74)->phase3A++;
        break;
case 1:
        gMainSerialOutgoingWork.word06=0xFF05;
        if ((u16)(gMainSerialOutgoingWork.words[0][1]+0xFE) <= 1) { ((struct LocalSerialContext65ED0 *)gMainContextPointer_03006F74)->flag7B = gMainSerialOutgoingWork.words[0][1] != 0xFF02; gMainSerialOutgoingWork.word06=0xFF04; }
        if (gMainSerialOutgoingWork.words[0][1] == 0xFF05) ((struct LocalSerialContext65ED0 *)gMainContextPointer_03006F74)->phase3A++;
        break;
case 2: gMainSerialOutgoingWork.word06=0xFF06; if (gMainSerialOutgoingWork.words[0][1] == 0xFF06) ((struct LocalSerialContext65ED0 *)gMainContextPointer_03006F74)->phase3A++; break;
case 3:
        if (sub_080440D4() != 0) { ((struct LocalSerialContext65ED0 *)gMainContextPointer_03006F74)->flag7C=0; gMainSerialOutgoingWork.word06=0xFF02; }
        else { ((struct LocalSerialContext65ED0 *)gMainContextPointer_03006F74)->flag7C=0xFF; gMainSerialOutgoingWork.word06=0xFF03; }
        if (gMainSerialOutgoingWork.words[0][1] == 0xFF04) ((struct LocalSerialContext65ED0 *)gMainContextPointer_03006F74)->phase3A++;
        break;
case 4:
        gMainSerialOutgoingWork.word06=0xFF05;
        if ((u16)(gMainSerialOutgoingWork.words[0][1]+0xFE) <= 1) { ((struct LocalSerialContext65ED0 *)gMainContextPointer_03006F74)->flag7C = gMainSerialOutgoingWork.words[0][1] != 0xFF02; gMainSerialOutgoingWork.word06=0xFF04; }
        if (gMainSerialOutgoingWork.words[0][1] == 0xFF05) ((struct LocalSerialContext65ED0 *)gMainContextPointer_03006F74)->phase3A++;
        break;
case 5: gMainSerialOutgoingWork.word06=0xFF06; if (gMainSerialOutgoingWork.words[0][1] == 0xFF06) gUnknown_0300137C++; break; }
    } else {
        switch ((u32)((struct LocalSerialContext65ED0 *)gMainContextPointer_03006F74)->phase3A) { case 0:
        if ((u16)(gMainSerialOutgoingWork.words[1][1]+0xFE) <= 1) { ((struct LocalSerialContext65ED0 *)gMainContextPointer_03006F74)->flag7B = gMainSerialOutgoingWork.words[1][1] != 0xFF02; gMainSerialOutgoingWork.word06=0xFF04; }
        if (gMainSerialOutgoingWork.words[1][1] == 0xFF05) ((struct LocalSerialContext65ED0 *)gMainContextPointer_03006F74)->phase3A++;
        break;
case 1:
        if ((s8)((struct LocalSerialContext65ED0 *)gMainContextPointer_03006F74)->flag7B == 0 || (s32)sub_080440B4() <= 1) {
            gMainSerialOutgoingWork.word06=0xFF02; ((struct LocalSerialContext65ED0 *)gMainContextPointer_03006F74)->flag7B=0;
        } else { gMainSerialOutgoingWork.word06=0xFF03; }
        if (gMainSerialOutgoingWork.words[1][1] == 0xFF04) ((struct LocalSerialContext65ED0 *)gMainContextPointer_03006F74)->phase3A++;
        break;
case 2:
        gMainSerialOutgoingWork.word06=0xFF05;
        if (gMainSerialOutgoingWork.words[0][1] == 0xFF05 && gMainSerialOutgoingWork.words[1][1] == 0xFF06) gMainSerialOutgoingWork.word06=gMainSerialOutgoingWork.words[1][1];
        if (gMainSerialOutgoingWork.words[0][1] == 0xFF06) ((struct LocalSerialContext65ED0 *)gMainContextPointer_03006F74)->phase3A++;
        break;
case 3:
        if ((u16)(gMainSerialOutgoingWork.words[1][1]+0xFE) <= 1) { ((struct LocalSerialContext65ED0 *)gMainContextPointer_03006F74)->flag7C = gMainSerialOutgoingWork.words[1][1] != 0xFF02; gMainSerialOutgoingWork.word06=0xFF04; }
        if (gMainSerialOutgoingWork.words[1][1] == 0xFF05) ((struct LocalSerialContext65ED0 *)gMainContextPointer_03006F74)->phase3A++;
        break;
case 4:
        if ((s8)((struct LocalSerialContext65ED0 *)gMainContextPointer_03006F74)->flag7C == 0 || sub_080440D4() != 0) {
            gMainSerialOutgoingWork.word06=0xFF02; ((struct LocalSerialContext65ED0 *)gMainContextPointer_03006F74)->flag7C=0;
        } else { gMainSerialOutgoingWork.word06=0xFF03; }
        if (gMainSerialOutgoingWork.words[1][1] == 0xFF04) ((struct LocalSerialContext65ED0 *)gMainContextPointer_03006F74)->phase3A++;
        break;
case 5:
        gMainSerialOutgoingWork.word06=0xFF05;
        if (gMainSerialOutgoingWork.words[0][1] == 0xFF05 && gMainSerialOutgoingWork.words[1][1] == 0xFF06) gMainSerialOutgoingWork.word06=gMainSerialOutgoingWork.words[1][1];
        if (gMainSerialOutgoingWork.words[0][1] == 0xFF06) gUnknown_0300137C++;
        break; }
    }
}
