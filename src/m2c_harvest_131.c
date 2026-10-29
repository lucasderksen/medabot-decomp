/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "compression.h"
#include "continued_float_progress.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct ContinuedFrameSetup {
    struct FrameObject preceding[0x21]; u16 flags; u8 pad1[6]; u8 scaleX; u8 scaleY;
    u8 pad2[14]; u16 angle; u8 pad3[10]; u8 kind; u8 pad4[11];
    u16 destinationX; s16 destinationY;
};
struct LocalTransferWait { u8 pad00[4]; s16 previousState; u8 pad06[2]; s32 counter; u8 pad0C[0xE2]; u8 flagEE; };

extern const s8 gUnknown_08485924[];
extern const u8 gUnknown_084D777C[];
extern const u8 gUnknown_084D78C0[];
extern const u8 gUnknown_0850FD98[32];
extern const u8 gUnknown_0850FDB8[32];
extern const void *const gState0NextCommands_083B6100[];
extern struct LocalTransferWait gGraphicsTransferCounter;
extern void sub_08068460(s32, s32, s32);
extern void sub_08068684(s32, s32, s32);

void sub_08023B44(void);
void sub_08023D44(void);
void sub_08030180(void);
void sub_080303A4(void);
s32 sub_0806B134(u32 inputIndex);
s32 sub_080701F8(void);

void sub_08023B44(void) {
    u8 *frames;
    u8 *transfer;
    u8 *typed;
    struct ContinuedFrameSetup *view;
    struct FrameObject *source;
    u32 index;
    u32 command;
    u16 clear;
    LeDecompress(gUnknown_084D777C, (void *)0x06014800);
    CpuFastSet(gUnknown_0850FD98, (void *)0x050002E0, 8);
    frames = (u8 *)gFrameObjects;
    view = (struct ContinuedFrameSetup *)frames;
    view->flags |= 0x220;
    view->scaleX = 0x40;
    view->scaleY = 0x40;
    clear=0;
    view->angle = clear;
    transfer = gState0TransferWork.bytes;
    index = (transfer[0x88] * 4) + 0x5D;
    source = &((struct FrameObject *)frames)[index];
    view->destinationX = source->screenX;
    index = (transfer[0x88] * 4) + 0x5D;
    source = &((struct FrameObject *)frames)[index];
    view->destinationY = source->screenY - 4;
    view->kind = 6;
    typed = gState0TypedWork.bytes;
    typed[0x84]=(command=0x45);
    sub_08040B90(gState0NextCommands_083B6100[command],0x21);
    *(u16 *)(typed+0x86)=0x3C;
    transfer[0xAA]++;
}

void sub_08023D44(void) {
    u8 *frames;
    u8 *transfer;
    u8 *typed;
    struct ContinuedFrameSetup *view;
    struct FrameObject *source;
    u32 index;
    u32 command;
    u16 clear;
    LeDecompress(gUnknown_084D78C0, (void *)0x06014800);
    CpuFastSet(gUnknown_0850FDB8, (void *)0x050002E0, 8);
    frames = (u8 *)gFrameObjects;
    view = (struct ContinuedFrameSetup *)frames;
    view->flags |= 0x220;
    view->scaleX = 0x40;
    view->scaleY = 0x40;
    clear=0;
    view->angle = clear;
    transfer = gState0TransferWork.bytes;
    index = (transfer[0x88] * 4) + 0x5D;
    source = &((struct FrameObject *)frames)[index];
    view->destinationX = source->screenX;
    index = (transfer[0x88] * 4) + 0x5D;
    source = &((struct FrameObject *)frames)[index];
    view->destinationY = source->screenY - 4;
    view->kind = 6;
    typed = gState0TypedWork.bytes;
    typed[0x84]=(command=0x42);
    sub_08040B90(gState0NextCommands_083B6100[command],0x21);
    *(u16 *)(typed+0x86)=0x3C;
    transfer[0xAA]++;
}

void sub_08030180(void) {

    if (gState0TypedWork.widths.word86 == 0x18) {
        gState0TypedWork.widths.word86 = 0;
        gState0TransferWork.bytes[0xAA] = (u8) (gState0TransferWork.bytes[0xAA] + 1);
        return;
    }
    gState0TypedWork.widths.word86 += 1;
    if (!(1 & gState0TransferWork.bytes[0xF8])) {
        gFrameObjects[0x21].screenX += 1;
        gFrameObjects[0x22].screenX += 1;
        gFrameObjects[0x23].screenX -= 1;
        gFrameObjects[0x24].screenX -= 1;
    } else {
        gFrameObjects[0x21].screenX -= 1;
        gFrameObjects[0x22].screenX -= 1;
        gFrameObjects[0x23].screenX += 1;
        gFrameObjects[0x24].screenX += 1;
    }
}

void sub_080303A4(void) {

    if (gState0TypedWork.widths.word86 == 0x20) {
        gState0TypedWork.widths.word86=0;
        gState0TransferWork.bytes[0xAA] = (u8) (gState0TransferWork.bytes[0xAA] + 1);
        return;
    }
    if (1 & gState0TypedWork.widths.word86) {
        if (!(1 & gState0TransferWork.bytes[0xF8])) {
            gFrameObjects[0x21].screenX = ((u16) gFrameObjects[0x21].screenX - 1) & 0x1FF;
            gFrameObjects[0x22].screenX = ((u16) gFrameObjects[0x22].screenX + 1) & 0x1FF;
            gFrameObjects[0x23].screenX = ((u16) gFrameObjects[0x23].screenX - 1) & 0x1FF;
            gFrameObjects[0x24].screenX = ((u16)gFrameObjects[0x24].screenX+1)&0x1FF;
        } else {
            gFrameObjects[0x21].screenX = ((u16) gFrameObjects[0x21].screenX + 1) & 0x1FF;
            gFrameObjects[0x22].screenX = ((u16) gFrameObjects[0x22].screenX - 1) & 0x1FF;
            gFrameObjects[0x23].screenX = ((u16) gFrameObjects[0x23].screenX + 1) & 0x1FF;
            gFrameObjects[0x24].screenX = ((u16)gFrameObjects[0x24].screenX-1)&0x1FF;
        }
    }
    gState0TypedWork.widths.word86++;
}

s32 sub_0806B134(u32 inputIndex) {
    u8 frameIndex = (u8)inputIndex;
    struct FrameObject *finalObject;
    struct FrameObject *frames;
    struct FrameObject *object;
    u16 step;
    u8 index;

    index = frameIndex;
    frames = gFrameObjects;
    object = &frames[index];
    step = object->unknown1A;
    if ((u32) step <= 0x1FU) {
        object->screenX = (u16) object->screenX + 1;
        object->screenY = (object->unknown23[0] + 3) - gUnknown_08485924[object->unknown1A + 0x20];
    } else if ((u32) step <= 0x2FU) {
        object->screenY = object->unknown23[0] + 3;
    } else {
        object->screenX = (u16) object->screenX + 2;
    }
    finalObject = &gFrameObjects[index];
    if ((s32) finalObject->commandStopped <= (s32) finalObject->screenX) {
        return 0;
    }
    return 1;
}

s32 sub_080701F8(void) {
    if (gGraphicsTransferCounter.counter != 0x3C) {
        if ((s32) gGraphicsTransferCounter.counter > 0x3C) {
            sub_08068684(2, 2, 0);
            gUnknown_0300137C = 2;
            return 1;
        }
        goto advanceTimer;
    }
    sub_08068460(4, 1, 0x7FFF);
    *(volatile u16 *)0x04000050 = 0x844;
    *(volatile u16 *)0x04000052 = 0x10;
    *(volatile u16 *)0x04000054 = 0;
    *(volatile u16 *)0x04000000 |= 0x400;
    gGraphicsTransferCounter.previousState = (s16) gUnknown_0300137C;
    gGraphicsTransferCounter.flagEE = 0x10;
    gUnknown_0300137C = 5;
advanceTimer:
    gGraphicsTransferCounter.counter = (s32) (gGraphicsTransferCounter.counter + 1);
    return 0;
}
