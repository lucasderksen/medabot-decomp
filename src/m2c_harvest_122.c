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
#include "equipment_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "interrupts.h"
#include "main_callbacks.h"
#include "object_numeric_helpers.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct LocalTransferCounter { u8 pad[8]; s32 counter; };
struct SpecialFrameView { u8 pad[0x82]; s16 screenX; s16 screenY; u16 frameAndGroup; u8 scaleX; u8 scaleY; };

extern const u8 *gState0NextCommands_083B6100[];
extern s16 gUnknown_03000030[160];
extern s32 sub_0807CEC8(s32 numerator, s32 denominator);
extern struct LocalTransferCounter gGraphicsTransferCounter;
extern u16 gUnknown_083AF6A0[8];
extern u8 gUnknown_084DEBE8;
extern u8 gUnknown_084E4658;
extern u8 gUnknown_08510258;
extern void sub_0806D5B4(void);
extern void sub_0806E10C(s8 value, u32 slot);

void sub_080294DC(void);
void sub_08037A94(u32 arg0, u32 unused, u32 arg2);
void sub_0806DAA4(void);

void sub_080294DC(void) {
    const u8 **table;
    u32 zeroByte, command;
    u16 zeroHalf;
    u8 *commandDestination;

    LeDecompress(&gUnknown_084DEBE8, (void *)0x06014800);
    CpuFastSet(&gUnknown_08510258, (void *)0x050002E0, 8U);
    CpuFastSet(&gUnknown_084E4658, (void *)0x050002C0, 8U);
    gFrameObjects[0x21].flags = 0xC604;
    gFrameObjects[0x21].tableSelector = (zeroHalf=0,zeroByte=0);
    gFrameObjects[0x21].screenY = 0xE0;
    gFrameObjects[0x21].palette = 7;
    gFrameObjects[0x21].scaleX = 0x40;
    gFrameObjects[0x21].scaleY = 0x40;
    gFrameObjects[0x21].angle = zeroHalf;
    gFrameObjects[0x21].priority=0xF0;
    gFrameObjects[0x21].unknown23[5] = zeroByte;
    *(commandDestination = &gFrameObjects[0x21].unknown2C[2]) = (command = 0x5B);
    gFrameObjects[0x21].unknown23[6] = 6;
    gFrameObjects[0x21].byte2B = 0x20;
    gFrameObjects[0x21].unknown2C[0] = 0xC0;
    gFrameObjects[0x21].unknown2C[1] = zeroByte;
    table=gState0NextCommands_083B6100;
    sub_08040B90(table[command], 0x21U);
    if (1 & gState0TransferWork.bytes[0xF8]) {
        gFrameObjects[0x21].screenX=0xB8;
    } else {
        gFrameObjects[0x21].screenX=0x38;
    }
    gState0TransferWork.bytes[0x51] = 0;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08037A94(u32 arg0, u32 unused, u32 arg2) {
    u32 var_r2;
    struct FrameObject *temp_r6;
    struct FrameObject *temp_r7;
    s32 mode;
    struct FrameObject *frames;
    u32 temp_r0;
    u32 zero;

    var_r2 = arg2;
    mode = gState0TransferWork.bytes[0x51];
    if (mode != 1) {
        if ((s32) mode <= 1) {
            if (mode != 0) {

            } else {
                goto block_5;
            }
        } else if (mode == 2) {
            goto block_5;
        }
    } else {
block_5:
        var_r2 = 7;
    }
    frames = gFrameObjects;
    temp_r7 = &frames[arg0];
    if (!(temp_r7->unknown2C[1] & var_r2)) {
        temp_r0 = sub_08040D78((u8) (arg0 + 1), 0x14U);
        sub_08040CD0(temp_r0, 1U);
        temp_r6 = &frames[temp_r0];
        zero = 0;
        temp_r6->flags = 0xC604;
        temp_r6->tableSelector = zero;
        temp_r6->screenX = ((u16)temp_r7->screenX + gUnknown_083AF6A0[(sub_080424B8() & 3) * 2]) & 0x1FF;
        temp_r6->screenY = ((u16)temp_r7->screenY + gUnknown_083AF6A0[(sub_080424B8() & 3) * 2 + 1]) & 0xFF;
        temp_r6->scaleX = 0x40;
        temp_r6->scaleY = 0x40;
        temp_r6->palette = 6;
        temp_r6->priority = 0xE0;
        switch (gState0TransferWork.bytes[0x51]) {
        case 0:
            temp_r6->frameAndGroup = 0x7201;
            temp_r6->unknown23[6] = 0x30;
            break;
        case 1:
            temp_r6->frameAndGroup = 0x7302;
            temp_r6->unknown23[6] = 0x34;
            break;
        case 2:
            temp_r6->frameAndGroup = 0x7402;
            temp_r6->unknown23[6] = 0x34;
            break;
        }
    }
}

void sub_0806DAA4(void) {
    struct SpecialFrameView *frames;
    s16 *var_r5;
    u32 baseScale;
    s32 var_r0;
    s32 var_r4;

    if (gGraphicsTransferCounter.counter == 0) {
        sub_08074B88(2U);
        *(volatile s16 *)0x04000050 = 0x244;
        *(volatile s16 *)0x04000052 = 0x1000;
        *(volatile u16 *)0x04000000 |= 0x400;
        *(volatile u16 *)0x04000200 |= 2;
        *(volatile u16 *)0x04000004 |= 0x10;
        gUnknownCallback_03002C20 = sub_0806D5B4;
        var_r4 = 0;
        baseScale = 0x100;
        var_r5 = gUnknown_03000030;
        do {
            if (var_r4 <= 0x1F) {
                var_r0 = var_r4 * 4;
                goto block_6;
            }
            if (var_r4 > 0x7F) {
                var_r0 = (0x9F - var_r4) * 4;
block_6:
                *var_r5 = sub_0807CEC8(0x10000, baseScale - var_r0);
            } else {
                *var_r5 = baseScale;
            }
            var_r5 += 1;
            var_r4 += 1;
        } while (var_r4 <= 0x9F);
        goto block_15;
    }
    if ((s32) gGraphicsTransferCounter.counter > 0x40) {
        gFrameObjects[2].flags &= 0xFDFF;
        sub_0806E10C(5, 2);
        gGraphicsTransferCounter.counter = 0;
        gUnknown_0300137C = 8;
        return;
    }
    if (!(7 & gGraphicsTransferCounter.counter)) {
        *(volatile s16 *)0x04000052 += 1;
        if (!(gGraphicsTransferCounter.counter & 0xF)) {
            *(volatile s16 *)0x04000052 -= 0x100;
        }
    }
block_15:
    if (gGraphicsTransferCounter.counter == 0x39) {
        sub_08048864(2U, 0xC600U, 0x212U, 2U, 3U);
        frames = (struct SpecialFrameView *)gFrameObjects;
        frames->screenX = 0x78;
        frames->screenY = 0x73;
        frames->scaleX = 0x40;
        frames->scaleY = 8;
        sub_0806E10C(4, 2);
    }
    gGraphicsTransferCounter.counter = (s32) (gGraphicsTransferCounter.counter + 1);
}
