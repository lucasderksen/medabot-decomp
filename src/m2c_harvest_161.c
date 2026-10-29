/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "dialogue_messages.h"
#include "background_state.h"
#include "compression.h"
#include "continued_late_graphics.h"
#include "display_effects.h"
#include "effect_work.h"
#include "frame.h"
#include "gba.h"
#include "main_callbacks.h"
#include "object_numeric_helpers.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct LocalFadeExitFreshWork { u8 pad00[5]; u8 selection5; u8 observed6; };
struct LocalPaletteSetupDma { const void *volatile source; void *volatile destination; volatile u32 control; };
struct LocalHardwareDMA { const void *source; void *destination; u32 control; };
struct LocalTransferSetup { u8 pad00[8]; s32 counter; u8 pad0C[0x35]; u8 flag; };

extern const u8 gUnknown_0807C210[0x1E0];
extern const u8 gUnknown_0807C3F0[0x80];
extern const u8 gUnknown_087AB390[];
extern const u8 gUnknown_087B4D24[];
extern const u8 gUnknown_087B62A0[];
extern const u8 gUnknown_087B6408[];
extern const u8 gUnknown_087B64D8[];
extern const u8 gUnknown_087B6710[0xA0];
extern s32 gUnknown_03006F88;
extern struct LocalFadeExitFreshWork gFreshWork_03006D38;
extern struct LocalTransferSetup gGraphicsTransferCounter;
extern u8 gState0FrameBackup[0xA0];
extern u8 gUnknown_03006F84;
s32 sub_0806B0D4(void);
s32 sub_0806B4C8(void);
void sub_080605A0(void);
void sub_08060620(void);
void sub_08069DF0(void);
void sub_0806A078(u8 *, const u8 *);
void sub_0806B530(u8, u8, u8, u8);

void sub_08060B28(void);
void sub_08069E78(void);
s32 sub_0806A08C(void);
void sub_0806B820(void);

void sub_08060B28(void) {
    sub_080605A0();
    sub_08060620();
    if ((u32) gState0TypedWork.bytes[0x84] <= 8U) {
        sub_0803F684(0U, gState0TypedWork.bytes[0x84] * 4, 0xFFFFU);
        sub_0803F998(0U, gState0TypedWork.bytes[0x84] * 4, 0xFFFFU);
        gState0TypedWork.bytes[0x84] += 1;
        return;
    }
    *(volatile u16 *)0x04000000 &= 0xFDFF;
    *(volatile u16 *)0x04000000 &= 0xFEFF;
    CpuFastSet(gState0FrameBackup, (void *)0x06002800, 0x28U);
    if (gMainSubstate == 0xA) {
        gMainSubstate = 4;
        gUnknown_0300137C = 0;
        return;
    }
    if ((*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x48)) != 0) {
        gFreshWork_03006D38.selection5 = (u8) (*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x17));
        sub_080476E8(5U);
        return;
    }
    sub_080476E8(6U);
}

void sub_08069E78(void) {
    struct LocalPaletteSetupDma *dma;
    const u8 *palette;
    sub_08048864(0U, 0xC400U, 0x104U, 0xCU, 3U);
    gFrameObjects->screenX = 0x78;
    gFrameObjects->screenY = -0x10;
    gFrameObjects->unknown1A = 0;
    dma = (struct LocalPaletteSetupDma *)0x040000D4;
    palette = gUnknown_0807C3F0;
    dma->source = palette;
    dma->destination = (void *)0x05000380;
    dma->control = 0x84000008;
    (void)dma->control;
    dma->source = palette + 0x60;
    dma->destination = (void *)0x05000360;
    dma->control = 0x84000008;
    (void)dma->control;
}

s32 sub_0806A08C(void) {
    switch (gUnknown_03006F88) {                    /* irregular */
    case 0:
        sub_0803FAA0(1U, 2U, 0U);
        sub_08069DF0();
        sub_0806B530(0, 1, 0x20, 0x58);
        sub_0806A078(gDebugMenuTextBuffer, gState0MapPartLabels_083BEB68[gUnknown_03006F84]);
        gUnknown_03006F88 += 1;
        break;
    case 1:
        if ((sub_0803FB3C(gUnknown_08485F88[0]) != 0) && (gFrameObjects->commandDelay == 0)) {
            return 1;
        }
    default:
        sub_0806B0D4();
        sub_0806B4C8();
        break;
    }
    return 0;
}

void sub_0806B820(void) {
    volatile struct LocalHardwareDMA *dma;
    struct FrameObject *frames;
    u8 *var_r4;
    u8 *var_r4_2;
    s32 var_r7;
    s32 var_r7_2;
    s32 var_r5;
    u32 var_r6;
    u32 var_r6_2;

    LZ77UnCompVram(gUnknown_087B4D24, (void *)0x06004000);
    LZ77UnCompVram(gUnknown_087B62A0, (void *)0x06000800);
    LZ77UnCompVram(gUnknown_087B6408, (void *)0x06001000);
    LZ77UnCompVram(gUnknown_087B64D8, (void *)0x06001800);
    dma = (volatile struct LocalHardwareDMA *)0x040000D4;
    dma->source = gUnknown_087B6710;
    dma->destination = (void *)0x05000000;
    dma->control = 0x80000050;
    dma->control;
    *(volatile u16 *)0x0400000A = 0x105;
    *(volatile u16 *)0x0400000C = 0x206;
    *(volatile u16 *)0x0400000E = 0x307;
    LZ77UnCompVram(gUnknown_087AB390, (void *)0x06010000);
    dma->source = gUnknown_0807C210;
    dma->destination = (void *)0x05000200;
    dma->control = 0x800000F0;
    dma->control;
    sub_08048864(0x1EU, 0xCF20U, 0U, 0U, 3U);
    gFrameObjects[0x1E].screenX = 0x78;
    gFrameObjects[0x1E].screenY = 0x80;
    gFrameObjects[0x1E].scaleX = 0x40;
    gFrameObjects[0x1E].scaleY = 0x40;
    gFrameObjects[0x1E].angle = 0;
    gGraphicsTransferCounter.flag = 0;
    gFrameObjects[0x1E].commandDelay = 3;
    gFrameObjects[0x1E].commandOffset = 0;
    sub_08048864(0x20U, 0xCC00U, 7U, 1U, 3U);
    gFrameObjects[0x20].screenX = 0x78;
    gFrameObjects[0x20].screenY = 0x10;
    sub_08048864(0x1FU, 0xCC00U, 0x10U, 2U, 3U);
    gFrameObjects[0x1F].screenY = 0xC8;
    sub_08048864(0xAU, 0xC400U, 0x10U, 2U, 3U);
    gFrameObjects[0xA].screenX = 0x10;
    gFrameObjects[0xA].screenY = 0x30;
    var_r5 = 0;
    var_r4 = (u8 *)gFrameObjects + 0x2C2;
    do {
        sub_08048864((u8)(var_r5 + 0xB), 0xC400U, 0x21U, 8U, 3U);
        (*(s16 *)((u8 *)(var_r4) + 0)) = 0x18 + var_r5 * 0x10;
        (*(s16 *)((u8 *)(var_r4) + 2)) = 0x28;
        var_r4 += 0x40;
        var_r5 += 1;
    } while (var_r5 <= 1);
    sub_08048864(0x39U, 0xC800U, 0x2BU, 9U, 3U);
    gFrameObjects[0x39].screenX = 0x78;
    gFrameObjects[0x39].screenY = 0x98;
    var_r5 = 0;
    var_r4_2 = (u8 *)gFrameObjects + 0x342;
    do {
        sub_08048864((u8)(var_r5 + 0xD), 0xC400U, 0x18U, 5U, 3U);
        (*(s16 *)((u8 *)(var_r4_2) + 0)) = 8 + var_r5 * 0x10;
        (*(s16 *)((u8 *)(var_r4_2) + 2)) = 0x78;
        var_r4_2 += 0x40;
        var_r5 += 1;
    } while (var_r5 <= 2);
    sub_08048864(0x10U, 0xC400U, 0x1EU, 7U, 3U);
    gFrameObjects[0x10].screenX = 0xB8;
    gFrameObjects[0x10].screenY = 0x68;
    sub_08048864(0x11U, 0xC400U, 0x1AU, 6U, 3U);
    gFrameObjects[0x11].screenX = 0xB8;
    gFrameObjects[0x11].screenY = 0x58;
    sub_08048864(0x12U, 0xC400U, 0x1CU, 6U, 3U);
    gFrameObjects[0x12].screenX = 0xD8;
    gFrameObjects[0x12].screenY = 0x58;
    sub_08048864(0x13U, 0xC400U, 0x19U, 6U, 3U);
    gFrameObjects[0x13].screenX = 0xB8;
    gFrameObjects[0x13].screenY = 0xC8;
    *(volatile u16 *)0x04000000 |= 0x1E00;
    gUnknown_0300137C += 1;
}
