/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "display_helpers.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "graphics.h"
#include "interrupts.h"
#include "record_helpers.h"
#include "render_work.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"
#include "utility_helpers.h"

struct Setup15C40 {
    u8 pad00[0xC1];
    u8 valueC1;
    u8 padC2[0x3E];
};
struct Part26678 {
    u8 name[13];
    u8 pad0D[3];
    u8 byte10;
    u8 data11[6];
    u8 id17;
};
struct Setup26678 {
    u8 pad00[0x48];
    struct Part26678 parts[4];
    u8 padA8[0x58];
};
struct Setup27544 {
    u8 pad00[0x40];
    u8 active40;
    u8 pad41[0xBF];
};

extern const u8 *gState0NextCommands_083B6100[];
extern struct Setup15C40 gSetup15C40[] asm("gSetupBuffer_03000590");
extern struct Setup26678 gSetup26678[] asm("gSetupBuffer_03000590");
extern struct Setup27544 gSetup27544[] asm("gSetupBuffer_03000590");
extern u32 sub_08037578(u32 kind, u32 selection);
extern u8 gUnknown_02021000[0x800];
extern u8 gUnknown_02021800[0x800];
extern u8 gUnknown_02022000[0x800];
extern u8 gUnknown_02028000[0x2000];

void sub_08015C40(u32 value);
void sub_0801FBC4(void);
void sub_08026678(void);
void sub_08027544(void);

void sub_08015C40(u32 value) {

    u32 x;
    u32 i;
    u32 part;
    u32 full;

    x = 0;
    if (value <= 2) {
        full = sub_08015DD0(0x40, 0x50, gSetup15C40[value].valueC1);
        part = 0xFFFF & full;
        full >>= 16;
        if (gSetup15C40[value].valueC1 != 0 && full == 0 && part == 0) {
            part = 1;
        }
        for (i = 0; i < full; i++) {
            sub_08042698(1, 1, x + 1, 0x11, *(volatile u16 *)0x0400000A, 0xD208);
            x++;
        }
        if (part != 0) {
            sub_08042698(1, 1, x + 1, 0x11, *(volatile u16 *)0x0400000A, (u16)(part + 0xD200));
            x++;
        }
        for (i = x; i <= 7; i++) {
            sub_08042698(1, 1, x + 1, 0x11, *(volatile u16 *)0x0400000A, 0xD200);
            x++;
        }
    } else {
        full = sub_08015DD0(0x40, 0x50, gSetup15C40[value].valueC1);
        part = 0xFFFF & full;
        full >>= 16;
        if (gSetup15C40[value].valueC1 != 0 && full == 0 && part == 0) {
            part = 1;
        }
        for (i = 0; i < full; i++) {
            sub_08042698(1, 1, x + 0x15, 0x11, *(volatile u16 *)0x0400000A, 0xD208);
            x++;
        }
        if (part != 0) {
            sub_08042698(1, 1, x + 0x15, 0x11, *(volatile u16 *)0x0400000A, (u16)(part + 0xD200));
            x++;
        }
        for (i = x; i <= 7; i++) {
            sub_08042698(1, 1, x + 0x15, 0x11, *(volatile u16 *)0x0400000A, 0xD200);
            x++;
        }
    }
}

void sub_0801FBC4(void) {

    switch (gState0TypedWork.bytes[0x139]) {
    case 0:
        gState0TypedWork.bytes[0x96] = 0;
        gRenderMode = 0;
        sub_08043CA8();
        sub_08043E54();
        *(volatile u16 *)0x04000000 &= 0xF0FF;
        *(volatile u16 *)0x04000008 = 0x500;
        *(volatile u16 *)0x0400000A = 0x1901;
        *(volatile u16 *)0x0400000C = 0x1A0A;
        *(volatile u16 *)0x0400000E = 0x1B0B;
        if (sub_0801A788(1) != 0) {
            gState0TypedWork.bytes[0x84] = 0;
            gState0TypedWork.bytes[0x139]++;
        }
        break;
    case 1:
        *(volatile u16 *)0x04000000 |= 0x1F40;
        sub_080158F8();
        sub_0801A0D0();
        sub_08043F9C();
        sub_080441A8(gEquipmentAssets_083B2628[gCounter6ED08_03001800.shift38 * 5 + 1]);
        gState0TypedWork.bytes[0x139]++;
        break;
    case 2:
        CpuFastSet(gUnknown_02021000, (void *)0x0600C800, 0x200);
        CpuFastSet(gUnknown_02021800, (void *)0x0600D000, 0x200);
        CpuFastSet(gUnknown_02022000, (void *)0x0600D800, 0x200);
        gState0TypedWork.bytes[0x139]++;
        break;
    case 3:
        CpuFastSet(gUnknown_02028000, gFrameObjects, 0x800);
        gState0TypedWork.bytes[0x139]++;
        break;
    case 4:
        sub_080158F8();
        sub_0801A0D0();
        gUnknownCallback_030017F0 = sub_08044100;
        gState0TypedWork.bytes[0x84] = 0;
        gCounter6ED08_03001800.flag1AE = 0;
        gCounter6ED08_03001800.counterAA++;
        gState0TypedWork.bytes[0x139] = 0;
        break;
    }
}

void sub_08026678(void) {

    sub_08040BD8(gState0NextCommands_083B6100[75], 0x21);
    sub_08040BD8(gState0NextCommands_083B6100[76], 0x22);
    gCounter6ED08_03001800.flag118 = 1;
    gCounter6ED08_03001800.part119 = gSetup26678[gCounter6ED08_03001800.slot87].parts[gCounter6ED08_03001800.partA7].name[1] - 0x37;
    gCounter6ED08_03001800.value11A = sub_08037578(gCounter6ED08_03001800.part119, gCounter6ED08_03001800.partA7);
    sub_0803F63C(&gSetup26678[gCounter6ED08_03001800.slot87].parts[gCounter6ED08_03001800.partA7], gCounter6ED08_03001800.partCopy11C, 0x18);
    sub_08042B58(gCounter6ED08_03001800.value11A, gCounter6ED08_03001800.partA7, gUnknown_0300052E);
    gSetup26678[gCounter6ED08_03001800.slot87].parts[gCounter6ED08_03001800.partA7].name[0] = gUnknown_0300052E[0];
    gSetup26678[gCounter6ED08_03001800.slot87].parts[gCounter6ED08_03001800.partA7].name[1] = gUnknown_0300052E[1];
    gSetup26678[gCounter6ED08_03001800.slot87].parts[gCounter6ED08_03001800.partA7].name[5] = gUnknown_0300052E[5];
    gSetup26678[gCounter6ED08_03001800.slot87].parts[gCounter6ED08_03001800.partA7].name[6] = gUnknown_0300052E[6];
    gSetup26678[gCounter6ED08_03001800.slot87].parts[gCounter6ED08_03001800.partA7].name[7] = gUnknown_0300052E[7];
    gSetup26678[gCounter6ED08_03001800.slot87].parts[gCounter6ED08_03001800.partA7].name[12] = gUnknown_0300052E[12];
    gSetup26678[gCounter6ED08_03001800.slot87].parts[gCounter6ED08_03001800.partA7].name[2] = 7;
    gSetup26678[gCounter6ED08_03001800.slot87].parts[gCounter6ED08_03001800.partA7].id17 = gCounter6ED08_03001800.value11A;
    sub_08031A3C(gCounter6ED08_03001800.slot87);
    sub_08015564(gCounter6ED08_03001800.slot87, gCounter6ED08_03001800.partA7 + 1);
    sub_080158F8();
    sub_0801A0D0();
    gCounter6ED08_03001800.counterAA++;
}

void sub_08027544(void) {

    u32 i;

    for (i = 0; i <= 2; i++) {
        if (gSetup27544[gCounter6ED08_03001800.base60 + i].active40 != 0) {
            switch (i) {
            case 0:
                sub_0801A28C(gDebugMenuTextBuffer, gCounter6ED08_03001800.valuesD6[i], 1);
                sub_0801A33C(gDebugMenuTextBuffer, gCounter6ED08_03001800.base60 + i, 0x21);
                break;
            case 1:
                sub_0801A28C(gDebugMenuTextBuffer + 0x14, gCounter6ED08_03001800.valuesD6[1], 1);
                sub_0801A33C(gDebugMenuTextBuffer + 0x14, gCounter6ED08_03001800.base60 + 1, 0x21);
                break;
            case 2:
                sub_0801A28C((gDebugMenuTextBuffer + 0x28), gCounter6ED08_03001800.valuesD6[2], 1);
                sub_0801A33C((gDebugMenuTextBuffer + 0x28), gCounter6ED08_03001800.base60 + 2, 0x21);
                break;
            }
        }
    }
    sub_08074DE0(0x5B);
    gState0TypedWork.bytes[0x84] = 0;
    gCounter6ED08_03001800.counterAA++;
}
