/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "composite_graphics.h"
#include "compression.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "native_le_streams.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct Part9B84 {
    u8 name[13];
    u8 pad0D[3];
    u8 byte10;
    u8 data11[6];
    u8 id17;
};
struct Setup9B84 {
    u8 pad00[0x48];
    struct Part9B84 parts[4];
    u8 padA8[0x58];
};
struct Part9FE0 {
    u8 name[13];
    u8 pad0D[3];
    u8 byte10;
    u8 data11[6];
    u8 id17;
};
struct Setup9FE0 {
    u8 pad00[0x48];
    struct Part9FE0 parts[4];
    u8 padA8[0x58];
};

extern const u8 *gState0NextCommands_083B6100[];
extern s32 gUnknown_085102B8;
extern s32 sub_08033184(s32);
extern s32 sub_0803325C(s32);
extern struct Setup9B84 gSetup9B84[] asm("gSetupBuffer_03000590");
extern struct Setup9FE0 gSetup9FE0[] asm("gSetupBuffer_03000590");
extern void sub_080351E8(s32);
extern void sub_08036CCC(s32, u8, s16);
extern void sub_080372D4(s32, u8, s16);

void sub_08029A14(void);
void sub_08029B84(void);
void sub_08029FE0(void);

void sub_08029A14(void) {

    u32 i;

    LeDecompress(gNativeLeStream_084DFA5C, (void *)0x06014800);
    CpuFastSet(&gUnknown_085102B8, (void *)0x050002E0, 8);
    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            u32 index = i + 0x21;
            gFrameObjects[index].flags = 0xC404;
            gFrameObjects[index].tableSelector = 0;
            gFrameObjects[index].screenX = gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].screenX;
            gFrameObjects[index].screenY = gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].screenY - 4;
            gFrameObjects[index].palette = 7;
            gFrameObjects[index].priority = 0xF0;
            sub_08040B90(gState0NextCommands_083B6100[0x60], index);
            if (1 & gCounter6ED08_03001800.flagsF8)
                gFrameObjects[index].flags |= 0x1000;
        }
    }
    sub_08074DE0(0x2A);
    gCounter6ED08_03001800.counterAA++;
}

void sub_08029B84(void) {

    u32 i, k;
    s32 result;

    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            for (k = 0; k <= 3; k++) {
                result = sub_08033184(gCounter6ED08_03001800.base60 + i);
                if (result == 0)
                    goto next;
                gCounter6ED08_03001800.padCE[2] = result - 1;
                sub_08036CCC(gCounter6ED08_03001800.base60 + i, gCounter6ED08_03001800.padCE[2], gCounter6ED08_03001800.valueEC);
                gSetup9B84[gCounter6ED08_03001800.base60 + i].parts[gCounter6ED08_03001800.padCE[2]].data11[0] += gCounter6ED08_03001800.valueC8;
                gCounter6ED08_03001800.valuesD6[i] += gCounter6ED08_03001800.valueC8;
                if (gCounter6ED08_03001800.valueCA == 0)
                    goto next;
                gCounter6ED08_03001800.valueEC = gCounter6ED08_03001800.valueCA;
            }
        }
    next:;
    }
    gCounter6ED08_03001800.counterAA++;
}

void sub_08029FE0(void) {

    u32 i, k;
    s32 result;

    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            for (k = 0; k <= 3; k++) {
                result = sub_0803325C(gCounter6ED08_03001800.base60 + i);
                if (result == 0)
                    goto next;
                gCounter6ED08_03001800.padCE[2] = result - 1;
                sub_080372D4(gCounter6ED08_03001800.base60 + i, gCounter6ED08_03001800.padCE[2], gCounter6ED08_03001800.valueEC);
                gSetup9FE0[gCounter6ED08_03001800.base60 + i].parts[gCounter6ED08_03001800.padCE[2]].data11[0] += gCounter6ED08_03001800.valueC8;
                gCounter6ED08_03001800.valuesD6[i] += gCounter6ED08_03001800.valueC8;
                sub_080351E8(gCounter6ED08_03001800.base60 + i);
                if (gCounter6ED08_03001800.valueCA == 0)
                    goto next;
                gCounter6ED08_03001800.valueEC = gCounter6ED08_03001800.valueCA;
            }
        }
    next:;
    }
    sub_080158F8();
    sub_0801A0D0();
    gCounter6ED08_03001800.counterAA++;
}
