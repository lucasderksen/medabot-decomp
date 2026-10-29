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
#include "coordinate_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct ContinuedSetupRecordBB { u8 pad00[0xBB]; u8 valueBB; u8 padBC[0x44]; };
struct ContinuedFrame9B9C4 {u8 prefix[0x240];struct FrameObject frame;};
struct ContinuedFramePairAB {u8 prefix[0x280];struct FrameObject first,second;};
struct ContinuedFrameCopyRoot {
    u8 pad00[0x842]; s16 x842; s16 y844; u8 pad846[0x3C];
    s16 x882; s16 y884; u8 pad886[2]; u8 scaleX888; u8 scaleY889;
};
struct ContinuedPhaseAA { u8 pad00[0xAA]; u8 phaseAA; };
struct Setup62FB4Work { u8 pad00[0x31]; u8 selection; u8 pad32; u8 row; u8 pad34[2]; u16 tileLast; u8 pad38[2]; u16 timer; u8 pad3C[0x14]; u8 blend[0x14]; };
struct Setup646C4Work { u8 pad00[0x3A]; u16 timer; u8 pad3C[0x14]; u8 blend[0x14]; };
struct LocalSceneFillWork { u16 mode0; s16 selection2; u8 pad4[4]; s32 counter8; u8 byteC; u8 byteD; u8 byteE; u8 padF[0x39]; };
struct LocalSceneFillDma { const void *volatile source; void *volatile destination; volatile u32 control; };

extern const u8 *const gState0NextCommands_083B6100[0x19];
extern const u8 gUnknown_084CC0F8[];
extern const u8 gUnknown_084CC578[];
extern const u8 gUnknown_084CC90C[];
extern const u8 gUnknown_084CCC24[];
extern const u8 gUnknown_0850F318[0x20];
extern const u8 gUnknown_0850F778[32];
extern const u8 gUnknown_0850F798[32];
extern const u8 gUnknown_0850F7B8[32];
extern const u8 gUnknown_0850F7D8[32];
extern const u8 gUnknown_0879D890[0x200];
extern const u8 gUnknown_0879DA90[];
extern const u8 gUnknown_0879EFC0[];
extern const u8 gUnknown_0879F138[];
extern const u8 gUnknown_0879F3D0[];
extern const u8 gUnknown_087A1540[0x120];
extern const u8 gUnknown_087A1660[];
extern const u8 gUnknown_087A2278[];
extern const u8 gUnknown_087A9AC0[];
extern const u8 gUnknown_087AA4C8[];
extern s32 sub_08062C98(void);
extern s32 sub_08074CE0(void);
extern struct ContinuedFrameCopyRoot gUnknown_03002C30;
extern struct ContinuedPhaseAA gUnknown_03001800;
extern struct ContinuedSetupRecordBB gUnknown_03000590[];
extern struct LocalSceneFillWork gGraphicsTransferCounter;
extern u32 sub_08015924(u32);
extern u8 gUnknown_0202F9A0[0x20];
extern u8 gUnknown_02030000[0x4480];
extern u8 gUnknown_02030040[0x4440];
extern u8 gUnknown_02031000[0x3480];
extern u8 gUnknown_02031040[0x3440];
extern void sub_08037424(s32);
extern void sub_0805BAA0(u32, s32, s32);
extern void sub_08062A10(u32);
extern void sub_08062B48(u8, u8, u32);
extern void sub_08062BEC(u32, u32);
s32 sub_08068460(s32, s32, s32);

void sub_08019544(u32 selected);
void sub_0801B9C4(void);
void sub_0801F800(void);
void sub_0802549C(void);
void sub_08062FB4(void);
void sub_080646C4(void);
void sub_0806B764(void);

void sub_08019544(u32 selected) {

    if (0x200 & gFrameObjects[(selected * 4u) + 0x5B].flags) {
        gFrameObjects[(selected * 4u) + 0x5D].unknown23[1] = ((s32) (0x20 - gUnknown_03000590[selected].valueBB) >> 1) + 1;
        sub_080432A0((selected * 4u) + 0x5A, selected, sub_08015924(selected));
        return;
    }
    sub_08043240((selected * 4u) + 0x5A, ((s32) (0x20 - gUnknown_03000590[selected].valueBB) >> 1) + 1);
}

void sub_0801B9C4(void) {
    struct FrameObject *temp_r0;
    struct ContinuedFrame9B9C4 *frames=(struct ContinuedFrame9B9C4 *)gFrameObjects;

    if (0x8000 & frames->frame.flags) {
        sub_08040BD8(gState0NextCommands_083B6100[0x18], 9U);
        if (frames->frame.unknown23[1] != 0) {
            frames->frame.unknown23[4] += 1;
            temp_r0 = (struct FrameObject *)((u32)gFrameObjects+((((frames->frame.unknown23[2]-1)*4)+frames->frame.unknown23[1]+0x59)<<6));
            temp_r0->flags |= 0x220;
            if (frames->frame.unknown23[3] == 0) {
                gFrameObjects[((frames->frame.unknown23[2] - 1) * 4) + frames->frame.unknown23[1] + 0x59].scaleX = (frames->frame.unknown23[4] * 2) + 0x40;
                gFrameObjects[((frames->frame.unknown23[2] - 1) * 4) + frames->frame.unknown23[1] + 0x59].scaleY = (frames->frame.unknown23[4] * 2) + 0x40;
            } else {
                gFrameObjects[((frames->frame.unknown23[2] - 1) * 4) + frames->frame.unknown23[1] + 0x59].scaleX = 0x60 - (frames->frame.unknown23[4] * 2);
                gFrameObjects[((frames->frame.unknown23[2] - 1) * 4) + frames->frame.unknown23[1] + 0x59].scaleY = 0x60 - (frames->frame.unknown23[4] * 2);
            }
            if ((u32) gFrameObjects[9].unknown23[4] > 0x10U) {
                gFrameObjects[9].unknown23[3] ^= 1;
                gFrameObjects[9].unknown23[4] = 0;
            }
        }
    }
}

void sub_0801F800(void) {
    s16 temp_r3;
    s16 temp_r4;
    u16 *var_r0;
    u16 temp_r5;
    u16 var_r4;
    struct ContinuedFramePairAB *frames;

    if (!(2 & gState0TransferWork.bytes[0xF8])) {
        var_r4 = *(u16 *)(gState0TransferWork.bytes+0x158) - 4;
        var_r0 = (u16 *)(gState0TransferWork.bytes + 0x15A);
    } else {
        var_r4 = *(u16 *)(gState0TransferWork.bytes+0x154) + 4;
        var_r0 = (u16 *)(gState0TransferWork.bytes + 0x156);
    }
    temp_r5 = *var_r0;
    switch (gState0TransferWork.bytes[0x51]) { /* irregular */
    case 0:
        LeDecompress(gUnknown_084CC0F8, (void *)0x06010000);
        CpuFastSet(gUnknown_0850F778,(void *)0x050003C0,8U);
        break;
    case 1:
        LeDecompress(gUnknown_084CC578, (void *)0x06010000);
        CpuFastSet(gUnknown_0850F798,(void *)0x050003C0,8U);
        break;
    case 2:
        LeDecompress(gUnknown_084CC90C, (void *)0x06010000);
        CpuFastSet(gUnknown_0850F7B8,(void *)0x050003C0,8U);
        break;
    case 3:
        LeDecompress(gUnknown_084CCC24, (void *)0x06010000);
        CpuFastSet(gUnknown_0850F7D8, (void *)0x050003C0, 8U);
        break;
    }
    frames=(struct ContinuedFramePairAB *)gFrameObjects;
    frames->first.flags = 0xC404;
    frames->first.tableSelector = 0;
    temp_r4 = (s16) var_r4;
    frames->first.screenX = temp_r4 - 0x10;
    temp_r3 = (s16) temp_r5;
    frames->first.screenY = temp_r3 - 8;
    frames->first.palette = 0xE;
    frames->first.priority = 0x80;
    frames->first.frameAndGroup = 0x1700;
    frames->second.flags = 0xC404;
    frames->second.tableSelector = 0;
    frames->second.screenX = temp_r4 + 0x10;
    frames->second.screenY = temp_r3 + 8;
    frames->second.palette = 0xE;
    frames->second.priority = 0x80;
    frames->second.frameAndGroup = 0x1701;
    gState0TransferWork.bytes[0xAA] = (u8) (gState0TransferWork.bytes[0xAA] + 1);
}

void sub_0802549C(void) {
    struct ContinuedFrameCopyRoot *frames;
    sub_08037424(0x21u);
    frames = &gUnknown_03002C30;
    if (frames->scaleX888 == 0x40) {
        frames->x882 = frames->x842;
        frames->y884 = frames->y844;
        gUnknown_03001800.phaseAA += 1;
    } else {
        frames->scaleX888 += 1;
        frames->scaleY889 += 1;
    }
}

void sub_08062FB4(void) {
    s32 sp10;
    volatile u16 *temp_r1_2;
    u32 temp_r0;
    struct Setup62FB4Work *work;

    if (sub_08074CE0() != 0x18) {
        sub_08074B88(0x18U);
    }
    sp10 = 0;
    CpuFastSet(&sp10, (void *)0x06000000, 0x01006000U);
    sub_080415BC();
    sub_08040CD0(0U, 0x80U);
    *(volatile u16 *)0x04000000 = 0x60U;
    *(volatile u16 *)0x04000050 = 0x2FF;
    *(volatile u16 *)0x04000054 = 0x10;
    temp_r1_2 = (volatile u16 *)0x0400000A;
    *temp_r1_2 = 0x1E05;
    *(volatile u16 *)0x0400000C = 0x1B06;
    *(volatile u16 *)0x0400000E = 0x3C07;
    sub_0805BA34(gUnknown_0879EFC0, (u32) *temp_r1_2);
    sub_0805BA34(gUnknown_0879F138, (u32) *(volatile u16 *)0x0400000C);
    sub_0805BA34(gUnknown_0879F3D0, (u32) *(volatile u16 *)0x0400000E);
    *(volatile u16 *)0x0400000C = 0x1D06;
    temp_r0 = sub_08044D0C(gUnknown_0879DA90, gUnknown_02030000);
    CpuSet(gUnknown_02030000, (void *)0x06004000, (u32) (temp_r0 << 0xA) >> 0xB);
    LeDecompress(gMain2AdditionalTiles_08785EC0, (void *)(temp_r0 + 0x06004000));
    ((struct Setup62FB4Work *)gMainContextPointer_03006F74)->tileLast = (s16) ((temp_r0 >> 5) - 1);
    CpuFastSet(gUnknown_0879D890, (void *)0x05000000, 0x80U);
    CpuFastSet(gUnknown_0850F318, (void *)0x050003A0, 8U);
    CpuFastSet(gUnknown_0850F318, &gUnknown_0202F9A0, 8U);
    LeDecompress(gMain2ObjectTiles_08785FB4, (void *)0x06010000);
    LeDecompress(gMain2SharedObjectTiles_084C8034, (void *)0x06011E00);
    work = gMainContextPointer_03006F74;
    work->timer = 0x280;
    sub_08062BEC((((struct Setup62FB4Work *)gMainContextPointer_03006F74)->selection * 4) + ((struct Setup62FB4Work *)gMainContextPointer_03006F74)->row, 0);
    sub_08041020(gDebugMenuTextBuffer, 0U, 0, 0xA, 0x10U, 0xDU, 0U, 1U);
    sub_08062A10(0);
    sub_08062B48(((struct Setup62FB4Work *)gMainContextPointer_03006F74)->selection, ((struct Setup62FB4Work *)gMainContextPointer_03006F74)->row, 0);
    sub_08062C98();
    sub_080656DC(((struct Setup62FB4Work *)gMainContextPointer_03006F74)->blend, 0x10U, 0U, -1U, 0xC0U);
    gFrameObjects[0x21].flags = 0x8000;
    gFrameObjects[0x21].tableSelector = 2;
    gFrameObjects[0x21].screenX = 0x28;
    gFrameObjects[0x21].screenY = 0x40;
    gFrameObjects[0x21].palette = 8;
    gFrameObjects[0x21].frameAndGroup = 0x2A;
    *(volatile u16 *)0x04000000 = (u16) (*(volatile u16 *)0x04000000 | 0x200);
    *(volatile u16 *)0x04000000 = (u16) (*(volatile u16 *)0x04000000 | 0x400);
    *(volatile u16 *)0x04000000 = (u16) (*(volatile u16 *)0x04000000 | 0x800);
    *(volatile u16 *)0x04000000 = (u16) (*(volatile u16 *)0x04000000 | 0x1000);
    gUnknown_0300137C += 1;
}

void sub_080646C4(void) {
 u8 *source, *source2, *source3, *source4;
 u8 *destination;
 s32 count;
 u32 firstLength, secondLength;
 struct Setup646C4Work *work;
 sub_08040CD0(0U, 0x80U);
 sub_080415BC();
 *(volatile u16 *)0x04000000 = 0x2060;
 *(volatile u16 *)0x0400000C = 0xDB06;
 *(volatile u16 *)0x0400000E = 0x1F07;
 sub_08044D0C(gUnknown_087A9AC0, gUnknown_02030000);
 source = gUnknown_02030000;
 destination = (u8 *)0x0600D800;
 count = 31;
 do { CpuFastSet(source, destination, 0x10U); destination += 0x40; source += 0x80; --count; } while (count >= 0);
 source2 = gUnknown_02030040;
 count = 31;
 do { CpuFastSet(source2, destination, 0x10U); destination += 0x40; source2 += 0x80; --count; } while (count >= 0);
 source3 = gUnknown_02031000;
 count = 31;
 do { CpuFastSet(source3, destination, 0x10U); destination += 0x40; source3 += 0x80; --count; } while (count >= 0);
 source4 = gUnknown_02031040;
 count = 31;
 do { CpuFastSet(source4, destination, 0x10U); destination += 0x40; source4 += 0x80; --count; } while (count >= 0);
 sub_0805BA34(gUnknown_087A2278, *(volatile u16 *)0x0400000E);
 firstLength = sub_08044D0C(gUnknown_087AA4C8, gUnknown_02030000);
 CpuSet(gUnknown_02030000, (void *)0x06004000, (firstLength >> 1) & 0x1FFFFF);
 secondLength = sub_08044D0C(gUnknown_087A1660, gUnknown_02030000);
 CpuSet(gUnknown_02030000, (void *)(firstLength + 0x06004000), (secondLength >> 1) & 0x1FFFFF);
 sub_0805BAA0(firstLength >> 5, 0, 0x1F);
 CpuFastSet(gUnknown_087A1540, (void *)0x05000000, 0x48U);
 *(volatile u16 *)0x04000000 |= 0x400;
 *(volatile u16 *)0x04000000 |= 0x800;
 *(volatile u16 *)0x04000040 = 0xF0;
 *(volatile u16 *)0x04000044 = 0x4858;
 *(volatile u16 *)0x04000048 = 0x3F3F;
 *(volatile u16 *)0x0400004A = 0x3B3B;
 gBgScroll2.y = 0x58;
 work = gMainContextPointer_03006F74;
 work->timer = 0;
 sub_080656DC(work->blend, 0x10U, 0U, -1U, 0xC0U);
 ++gUnknown_0300137C;
}

void sub_0806B764(void) {
    s32 sp0;
    struct LocalSceneFillDma *dma;

    sp0 = 0;
    dma = (struct LocalSceneFillDma *)0x040000D4;
    dma->source = &sp0;
    dma->destination = (void *)0x06000000;
    dma->control = 0x85006000;
    (void)dma->control;
    *(volatile u16 *)0x04000000 = 0x60;
    sp0 = 0;
    dma->source = &sp0;
    dma->destination = gFrameObjects;
    dma->control = 0x85000800;
    (void)dma->control;
    sp0 = 0;
    dma->source = &sp0;
    dma->destination = &gGraphicsTransferCounter;
    dma->control = 0x85000012;
    (void)dma->control;
    gGraphicsTransferCounter.mode0 = 3;
    gGraphicsTransferCounter.selection2 = 5;
    gGraphicsTransferCounter.counter8 = 0;
    gGraphicsTransferCounter.byteD = 0xC;
    gGraphicsTransferCounter.byteC = 0x32;
    gGraphicsTransferCounter.byteE = 0;
    sub_08074B88(0U);
    sub_08068460(3, 2, 0);
    gBgScroll0.x = 0;
    gBgScroll0.y = 0;
    gBgScroll1.x = 0;
    gBgScroll1.y = 0;
    gBgScroll2.x = 0;
    gBgScroll2.y = 0;
    gBgScroll3.x = 0;
    gBgScroll3.y = 0;
    gUnknown_0300137C += 1;
}
