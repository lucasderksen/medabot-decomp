/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "compression.h"
#include "continued_scene_records.h"
#include "display_helpers.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "graphics.h"
#include "interrupts.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct StatePrivate_08018AB4 {
 u8 before57[87];
 u8 number;
 u8 coverageTail[345];
};
struct SceneSetupRecord {u8 before49[0x49];u8 entry49;};
struct StatePrivate_0801E09C {
 u8 before38[56];
 u8 graphics;
 u8 before87[78];
 u8 bank;
 u8 beforeA7[31];
 u8 part;
 u8 beforeAA[2];
 u8 phase;
 u8 coverageTail[262];
};

extern const u8 gUnknown_08488240[];
extern u32 sub_0807CEC8(u32,u32);
extern u32 sub_0807CF40(u32,u32);
extern void sub_0801BC5C(s32);
extern void sub_0801BCA0(void);
extern void sub_08035C3C(void);

void sub_08018AB4(u32 value);
void sub_0801E09C(void);

void sub_08018AB4(u32 value) {

 struct StatePrivate_08018AB4 *work;
    void *temp_r0;
    void *temp_r0_2;

    if (value != 0) {
        sub_0803EF8C(6U, 5U, 0xCU, 0xFU, (u32) *(volatile u16 *)0x0400000A, 0U);
        sub_08040CD0(0U, 1U);
        sub_08040CD0(1U, 2U);
        return;
    }
    LoadLeTilemap(0xCU, 0xFU, gUnknown_08488240, (u32) *(volatile u16 *)0x0400000A, 0x230U);
    gFrameObjects->flags = 0xC404;
    gFrameObjects->tableSelector = 0;
    gFrameObjects->palette = 0xA;
    gFrameObjects->priority = 0x40;
    gFrameObjects->screenX = 0x78;
    gFrameObjects->screenY = 0x84;
    gFrameObjects->frameAndGroup = 0x623;
    gFrameObjects[1].flags = 0xC404;
    gFrameObjects[1].tableSelector = 0;
    temp_r0 = (u8 *)gFrameObjects + 0x4A;
    (*(s8 *)((u8 *)(temp_r0) + 0)) = 0xA;
    (*(s8 *)((u8 *)(++temp_r0) + 0)) = 0x40;
    gFrameObjects[1].screenX = 0x70;
    gFrameObjects[1].screenY = 0x90;
    work=(struct StatePrivate_08018AB4 *)&gState0TransferWork;
    gFrameObjects[1].frameAndGroup = (u8)sub_0807CEC8(work->number, 0xA) + 0x624;
    gFrameObjects[2].flags = 0xC404;
    gFrameObjects[2].tableSelector = 0;
    temp_r0_2 = (u8 *)gFrameObjects + 0x8A;
    (*(s8 *)((u8 *)(temp_r0_2) + 0)) = 0xA;
    (*(s8 *)((u8 *)(++temp_r0_2) + 0)) = 0x40;
    gFrameObjects[2].screenX = 0x80;
    gFrameObjects[2].screenY = 0x90;
    gFrameObjects[2].frameAndGroup = (u8)sub_0807CF40(work->number, 0xA) + 0x624;
}

void sub_0801E09C(void) {


    s32 sp8;
    u32 temp_r2;
    u8 temp_r5;
    void *temp_r1;
 const u8 *setup;

    temp_r5 = gState0TypedWork.bytes[0x139];
    switch (temp_r5) {                              /* irregular */
    case 0:
        sub_08043CA8();
        *(volatile u16 *)0x04000000 = (u16) (0xE0FF & *(volatile u16 *)0x04000000);
        *(volatile u16 *)0x04000008 = 0x500;
        *(volatile u16 *)0x0400000A = 0x1801;
        *(volatile u16 *)0x0400000C = 0x590A;
        *(volatile u16 *)0x0400000E = 0x5B0B;
        LeDecompress(gMain2SharedObjectTiles_084C8034, (void *)0x06017400);
        sub_0803EF8C(0x20U, 0x20U, 0U, 0U, (u32) *(volatile u16 *)0x0400000A, (u32) temp_r5);
        sub_08043B7C((u32) ((struct StatePrivate_0801E09C *)&gState0TransferWork)->graphics, 0U);
        sp8 = (s32) temp_r5;
        CpuFastSet(&sp8, gFrameObjects, 0x01000800U);
        gState0TypedWork.bytes[0x139] += 1;
        return;
    case 1:
        *(volatile u16 *)0x04000000 |= 0x1F40;
        *(volatile u16 *)0x04000000 &= 0xFFDF;
        sub_08043DF8();
    
        setup=gSetupBuffer_03000590;
        temp_r2 = ((struct StatePrivate_0801E09C *)&gState0TransferWork)->bank << 8;
        temp_r1 = (void *)(temp_r2 + (u32)setup);
        if ((u32) (*(u8 *)((u8 *)(temp_r1) + 0xDD)) <= 3U) {
            sub_0801BC5C(((struct SceneSetupRecord *)((((struct StatePrivate_0801E09C *)&gState0TransferWork)->part * 0x18) + temp_r2 + (u32)setup))->entry49);
        } else {
            sub_0801BC5C((*(u8 *)((u8 *)(temp_r1) + 0xA8)) + 0x50);
        }
        sub_0801BCA0();
        sub_08035C3C();
        gUnknownCallback_030017F0 = sub_08043E48;
    
        gState0TypedWork.bytes[0x84] = 0;
        gState0TypedWork.bytes[0x139] = 0;
        ((struct StatePrivate_0801E09C *)&gState0TransferWork)->phase = (u8) (((struct StatePrivate_0801E09C *)&gState0TransferWork)->phase + 1);
        return;
    }
}
