/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "compression.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "effect_work.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "render_work.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct ContinuedScaleFrame21 {
 u8 prefix[0x840];u16 flags;s16 screenX,screenY;u16 frameAndGroup;u8 scaleX,scaleY,palette,priority;
 u8 gapC[0xC];u16 angle,unknown1A;u8 tableSelector,affineIndex;u8 gap1E[6];u8 kind;u8 gap25[0xB];u16 savedX;s16 savedY;u8 gap34[0xC];
};
struct ContinuedDropFrame21 {
    u8 prefix[0x840]; u16 flags; s16 screenX,screenY; u16 frameAndGroup;
    u8 scaleX,scaleY,palette,priority; u8 gapC[0x22]; u8 commandIndex; u8 gap2F[0x11];
};

extern const u8 *const gState0NextCommands_083B6100[57];
extern const u8 gUnknown_080AFBB4[];
extern const u8 gUnknown_084D8264[];
extern const u8 gUnknown_084D83C0[];
extern const u8 gUnknown_0850FE98[64];
extern const u8 gUnknown_0850FEB8[64];
extern s32 sub_0805DDEC(s32);
extern u32 sub_08074FA4(u32);
extern void sub_0803FB0C(void);

void sub_08025858(void);
void sub_08028E84(void);
void sub_0805FA58(void);
void sub_08062B48(u8 arg0, u8 arg1, u32 arg2);

void sub_08025858(void) {
 u8 *work;struct ContinuedScaleFrame21 *frames;
    u8 *setup=gSetupBuffer_03000590;
    u8 *initialWork=gState0TransferWork.bytes;
    u32 offset;
    offset=initialWork[0xA7]*0x18;
    offset+=initialWork[0x87]<<8;
    if (setup[offset+0x49] == 0x2E) {
        LeDecompress(gUnknown_084D8264,(void *)0x06014800);
        CpuFastSet(gUnknown_0850FE98,(void *)0x050002E0,0x10);
    } else {
        LeDecompress(gUnknown_084D83C0,(void *)0x06014800);
        CpuFastSet(gUnknown_0850FEB8,(void *)0x050002E0,0x10);
    }
    frames=(struct ContinuedScaleFrame21 *)gFrameObjects;
    frames->flags |= 0x220;
    frames->scaleX = 0x40;
    frames->scaleY = 0x40;
    frames->angle = 0;
    frames->palette = 7;
    frames->frameAndGroup = 0x5200;
    work=gState0TransferWork.bytes;
    frames->savedX = (u16) (u16)gFrameObjects[work[0x88]*4+0x5D].screenX;
    frames->savedY = (s16) ((u16)gFrameObjects[work[0x88]*4+0x5D].screenY - 4);
    frames->kind = 6;
    gState0TypedWork.widths.word86 = 0x3C;
    work[0xAA]++;
}

void sub_08028E84(void) {
    struct ContinuedDropFrame21 *frames;
    const u8 *const *commands;
    u16 y;
    commands=gState0NextCommands_083B6100;
    frames=(struct ContinuedDropFrame21 *)gFrameObjects;
    sub_08040BD8(commands[frames->commandIndex],0x21);
    y=(u16)frames->screenY;
    if (frames->screenY == 0x40) {
        gState0TypedWork.widths.word86=0x3C;
        gState0TransferWork.bytes[0xAA]++;
    } else {
        u8 *work;
        frames->screenY=(y+2)&0xFF;
        work=gState0TransferWork.bytes;
        if (1 & work[0xF8]) {
            if (work[0x51] != 3) {
                struct FrameObject *frame=&gFrameObjects[gState0TypedWork.bytes[0x12F]];
                frame->angle=(frame->angle-0x10)&0x3FF;
            }
        } else {
            if (work[0x51] != 3) {
                struct FrameObject *frame=&gFrameObjects[gState0TypedWork.bytes[0x12F]];
                frame->angle=(frame->angle+0x10)&0x3FF;
            }
        }
    }
}

void sub_0805FA58(void) {
    u8 var_r0;
    s32 index;
    u16 temp_r0;
    u16 var_r5;

    temp_r0 = (*(u16 *)((u8 *)(gMainContextPointer_03006F74) + 2));
    (*(u16 *)((u8 *)(gMainContextPointer_03006F74) + 2)) = (u16) (temp_r0 + 1);
    temp_r0 = (u8)temp_r0;
    var_r5 = 0;
    if (((u32)temp_r0 > 0x1DU) && (sub_08074FA4(4U) == 0)) {
        for (var_r0 = 0; (index = (s8)var_r0) <= 3; var_r0 = (u8)(index + 1)) {
            var_r5 = (u16)sub_0805DDEC(2);
            if (var_r5 == 0) break;
        }
        if (var_r5 == 0) {
            sub_0803FB0C();
            (*(u16 *)((u8 *)(gMainContextPointer_03006F74) + 2)) = var_r5;
            gUnknown_0300137C += 1;
        } else {
            sub_0803FB0C();
            (*(u16 *)((u8 *)(gMainContextPointer_03006F74) + 2)) = 0U;
            gUnknown_0300137C = 0xC;
        }
    }
}

void sub_08062B48(u8 arg0, u8 arg1, u32 arg2) {
    s32 temp_r0;
    u8 temp_r1;
    u8 temp_r4;
    u8 temp_r5;
    u8 temp_r7;

    temp_r7 = arg0;
    temp_r5 = arg1;
    gRecordDisplayWork.data = (arg2 * 0x410) + gRecordDisplayData;
    {
        u32 base = (u32)gUnknown_080AFBB4;
        temp_r4 = *(const u8 *)(base + (temp_r0 = (temp_r5 * 2) + (arg2 * 8)));
        base++;
        temp_r1 = *(const u8 *)(base + temp_r0);
    }
    if (arg2 != 0) {
        sub_08046A60(gRenderWork->objects, &gRecordDisplayWork, (s32) temp_r7, (s32) temp_r5, (s32) temp_r1, (s32) temp_r4, 0x12BU, 4U, 6U);
        return;
    }
    sub_08046A60(gRenderWork->objects, &gRecordDisplayWork, (s32) temp_r7, (s32) temp_r5, (s32) temp_r1, (s32) temp_r4, 0x12BU, arg2, 5U);
}
