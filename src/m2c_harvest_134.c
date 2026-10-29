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
#include "main_callbacks.h"
#include "object_numeric_helpers.h"
#include "record_helpers.h"
#include "render_work.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct ContinuedSetupBacking { struct FrameObject preceding[0x21]; struct FrameObject frame; };
struct LocalTransferDispatch { u8 pad00[4]; s16 previousState; u8 pad06[2]; s32 counter; };

extern const u8 *const gState0NextCommands_083B6100[57];
extern const u8 gUnknown_08485BB4[];
extern const u8 gUnknown_084D667C[];
extern const u8 gUnknown_084D66DC[];
extern const u8 gUnknown_0850FBF8[32];
extern const u8 gUnknown_0850FC18[32];
extern const void *const gUnknown_08486D78[];
extern s32 sub_08071DDC(void);
extern struct LocalTransferDispatch gGraphicsTransferCounter;
extern void sub_08068684(s32, s32, s32);

void sub_08020DF8(void);
void sub_08025FC8(void);
void sub_0802F058(void);
void sub_08071304(void);

void sub_08020DF8(void) {
    struct ContinuedSetupBacking *objects;
    struct FrameObject *frames;
    struct FrameObject *source;
    u8 *work;
    u32 index;
    u32 byteZero;
    u16 wordZero;
    LeDecompress(gUnknown_084D667C, (void *)0x06015800);
    CpuFastSet(gUnknown_0850FBF8,(void *)0x050002E0,8);
    objects=(struct ContinuedSetupBacking *)gFrameObjects;
    objects->frame.flags=0xC604;
    objects->frame.tableSelector=(byteZero=0);
    wordZero=0;
    work=gState0TransferWork.bytes;
    index=work[0x87]*4+0x5D;
    frames=(struct FrameObject *)objects;
    source=&frames[index];
    objects->frame.screenX=source->screenX;
    index=work[0x87]*4+0x5D;
    frames=(struct FrameObject *)objects;
    source=&frames[index];
    objects->frame.screenY=source->screenY - 4;
    objects->frame.palette=7;
    objects->frame.priority=0xF0;
    objects->frame.scaleX=0x40;
    objects->frame.scaleY=0x40;
    objects->frame.angle=wordZero;
    objects->frame.frameAndGroup=0x4100;
    objects->frame.unknown23[0]=byteZero;
    objects->frame.unknown23[4]=byteZero;
    sub_08074DE0(0x29);
    work[0xAA]++;
}

void sub_08025FC8(void) {
    s16 screenX;
    struct FrameObject *frame,*frameBase;
    u32 count;
    u32 frameIndex;const u8 *const *commands;

    LeDecompress(gUnknown_084D66DC, (void *)0x06014800);
    CpuFastSet(gUnknown_0850FC18, (void *)0x050002E0, 8U);
    count = 0;
    do {
        frameBase=gFrameObjects;
        frameIndex = count + 0x21;
        frame = &frameBase[frameIndex];
        frame->flags = 0xC404;
        frame->tableSelector = 0;
        frame->screenY = 0x58 - count*0x18;
        frame->palette = 7;
        frame->priority = 0xF0;
        commands=gState0NextCommands_083B6100;sub_08040B90(commands[0x38],frameIndex);
        if (!(1 & gState0TransferWork.bytes[0xF8])) {
            screenX = 0x88;
        } else {
            frame->flags |= 0x1000;
            screenX = 0x68;
        }
        frame->screenX = screenX;
        count += 1;
    } while (count <= 2U);
    sub_08074DE0(0x52U);
    gState0TransferWork.bytes[0xAA] = (u8) (gState0TransferWork.bytes[0xAA] + 1);
}

void sub_0802F058(void) {
    struct ContinuedSetupBacking *objects;
    struct FrameObject *frames;
    struct FrameObject *source;
    u8 *work;
    u32 index;
    u32 byteZero;
    u16 wordZero;
    LeDecompress(gUnknown_084D667C, (void *)0x06015800);
    CpuFastSet(gUnknown_0850FBF8,(void *)0x050002E0,8);
    objects=(struct ContinuedSetupBacking *)gFrameObjects;
    objects->frame.flags=0xC624;
    objects->frame.tableSelector=(byteZero=0);
    wordZero=0;
    work=gState0TransferWork.bytes;
    index=work[0x87]*4+0x5D;
    frames=(struct FrameObject *)objects;
    source=&frames[index];
    objects->frame.screenX=source->screenX;
    index=work[0x87]*4+0x5D;
    frames=(struct FrameObject *)objects;
    source=&frames[index];
    objects->frame.screenY=source->screenY - 4;
    objects->frame.palette=7;
    objects->frame.priority=0xF0;
    objects->frame.scaleX=0x40;
    objects->frame.scaleY=0x40;
    objects->frame.angle=wordZero;
    objects->frame.frameAndGroup=0x4100;
    objects->frame.unknown23[0]=byteZero;
    objects->frame.unknown23[4]=byteZero;
    sub_08074DE0(0x29);
    work[0xAA]++;
}

void sub_08071304(void) {
    struct LocalTransferDispatch *work;
    struct LocalTransferDispatch *scriptWork;
    u32 phase;
    work = &gGraphicsTransferCounter;
    phase = work->counter;
    scriptWork = work;
    switch (phase) {
    case 0:
        sub_0803FAA0(1U, 0U, 0U);
        gGraphicsTransferCounter.counter += 1;
        break;
    case 4: case 8: case 12: case 16: case 20: case 24:
        sub_0803FB0C();
        gGraphicsTransferCounter.counter += 1;
        break;
    case 1: case 5: case 9: case 13: case 17: case 21:
        if (sub_0803FB3C(gUnknown_08486D78[(scriptWork->counter >> 2) + 8]) != 0) {
            sub_0803FB0C();
            sub_0803FB3C(gUnknown_08485BB4);
            scriptWork->counter += 1;
        }
        break;
    case 25:
        if (sub_0803FB3C(gUnknown_08486D78[(scriptWork->counter >> 2) + 8]) != 0) {
            scriptWork->counter += 1;
        }
        break;
    case 2: case 6: case 10: case 14: case 18:
        scriptWork->counter += 1;
        break;
    case 22:
        sub_08048864(0U, 0xC800U, 0x50FU, 0U, 3U);
        gFrameObjects->screenX = 0x42;
        gFrameObjects->screenY = -8;
        gFrameObjects->priority = 0x40;
        gFrameObjects->unknown1A = 0;
        gGraphicsTransferCounter.counter += 1;
        break;
    case 3: case 7: case 11: case 15: case 19: case 23:
        if (sub_08071DDC() != 0) {
            gGraphicsTransferCounter.counter += 1;
        }
        break;
    default:
        sub_08068684(4, 2, 0);
        work->counter = 0;
        work->previousState = 0xE;
        gUnknown_0300137C = 2;
        break;
    }
}
