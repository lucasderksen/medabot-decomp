/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "battle_work.h"
#include "compression.h"
#include "continued_scene_records.h"
#include "display_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "input.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "utility_helpers.h"

struct FrameC864 {
    u16 flags;
    s16 screenX;
    s16 screenY;
    u16 frameAndGroup;
    u8 scaleX;
    u8 scaleY;
    u8 palette;
    u8 priority;
    u8 padC[0xC];
    u16 angle;
    u8 pad1A[2];
    u8 tableSelector;
    u8 pad1D[6];
    u8 byte23;
    u8 byte24;
    u8 pad25[0xB];
    u16 word30;
    s16 word32;
    u8 pad34[0xC];
};
struct SetupRecCB34 {
    u8 pad0[0xC4];
    u8 bytesC4[4];
    u8 padC8[0x38];
};
struct FrameE948 {
    u16 flags;
    s16 screenX;
    s16 screenY;
    u16 frameAndGroup;
    u8 scaleX;
    u8 scaleY;
    u8 palette;
    u8 priority;
    u8 padC[0xC];
    u16 angle;
    u8 pad1A[2];
    u8 tableSelector;
    u8 pad1D[6];
    u8 byte23;
    u8 byte24;
    u8 pad25[4];
    u8 byte29;
    u8 pad2A[6];
    u16 word30;
    s16 word32;
    u8 pad34[0xC];
};

extern const u8 *gState0NextCommands_083B6100[];
extern const u8 gUnknown_084CA064[];
extern const u8 gUnknown_084D7638[];
extern const u8 gUnknown_084E2AB8[];
extern const u8 gUnknown_084E45B8[];
extern const u8 gUnknown_0850FD78[];
extern const u8 gUnknown_08510478[];
extern s8 sub_08036E54(s16);
extern struct FrameC864 gFramesC864[] asm("gFrameObjects");
extern struct FrameE948 gFramesE948[] asm("gFrameObjects");
extern struct SetupRecCB34 gSetupRecCB34[] asm("gSetupBuffer_03000590");
extern u8 gUnknown_030004F2[];
extern u8 gUnknown_03000506[];
extern void sub_080356B4(u32);

void sub_0802C864(void);
void sub_0802C960(void);
void sub_0802CB34(void);
void sub_0802CE4C(void);
void sub_0802CFAC(void);
void sub_0802D270(void);
void sub_0802D4D8(void);
void sub_0802E70C(void);
void sub_0802E948(void);

void sub_0802C864(void) {

    u32 i;

    sub_08040CD0(0x21, 1);
    LeDecompress(gUnknown_084D7638, (void *)0x06014800);
    CpuFastSet(gUnknown_0850FD78, (void *)0x050002E0, 8);
    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            gFramesC864[i + 0x21].flags = 0xC624;
            gFramesC864[i + 0x21].tableSelector = 0;
            gFramesC864[i + 0x21].screenX = 0x78;
            gFramesC864[i + 0x21].screenY = 0x40;
            gFramesC864[i + 0x21].palette = 7;
            gFramesC864[i + 0x21].priority = 0xF0;
            gFramesC864[i + 0x21].scaleX = 0x40;
            gFramesC864[i + 0x21].scaleY = 0x40;
            gFramesC864[i + 0x21].angle = 0;
            gFramesC864[i + 0x21].word30 = gFramesC864[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].screenX;
            gFramesC864[i + 0x21].word32 = gFramesC864[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].screenY - 4;
            gFramesC864[i + 0x21].byte24 = 6;
            sub_08040B90(gState0NextCommands_083B6100[0x42], i + 0x21);
        }
    }
    gCounter6ED08_03001800.counterAA++;
}

void sub_0802C960(void) {

    s32 done = 0;
    s32 active = 0;
    u32 i;

    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            active++;
            sub_08040BD8(gState0NextCommands_083B6100[0x42], i + 0x21);
            if (!(1 & gCounter6ED08_03001800.flagsF8))
                gFrameObjects[i + 0x21].angle = (gFrameObjects[i + 0x21].angle - 0x40) & 0x3FF;
            else
                gFrameObjects[i + 0x21].angle = (gFrameObjects[i + 0x21].angle + 0x40) & 0x3FF;
            if (sub_080355F0(i + 0x21) != 0)
                done++;
        }
    }
    if (done == active) {
        gFrameObjects[0x21].angle = 0;
        gFrameObjects[0x22].angle = 0;
        gFrameObjects[0x23].angle = 0;
        sub_08040B90(gState0NextCommands_083B6100[0x43], 0x21);
        sub_08040B90(gState0NextCommands_083B6100[0x43], 0x22);
        sub_08040B90(gState0NextCommands_083B6100[0x43], 0x23);
        sub_08074DE0(0x4E);
        gCounter6ED08_03001800.counterAA++;
    }
}

void sub_0802CB34(void) {

    u32 i;

    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            gSetupRecCB34[gCounter6ED08_03001800.base60 + i].bytesC4[0] = 0x26;
            gSetupRecCB34[gCounter6ED08_03001800.base60 + i].bytesC4[1] = 0;
            gSetupRecCB34[gCounter6ED08_03001800.base60 + i].bytesC4[2] = sub_08036E54(gCounter6ED08_03001800.valueE8);
            gSetupRecCB34[gCounter6ED08_03001800.base60 + i].bytesC4[3] = sub_08036E54(gCounter6ED08_03001800.valueEC);
        }
    }
    gCounter6ED08_03001800.counterAA++;
}

void sub_0802CE4C(void) {

    u32 i;
    u32 j;

    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            gFrameObjects[i + 0x21].unknown23[0] = 0;
            sub_0803F63C(&gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5A], &gFrameObjects[(j = i * 4) + 0x24], 0x40);
            sub_0803F63C(&gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5B], &gFrameObjects[j + 0x25], 0x40);
            sub_0803F63C(&gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5C], &gFrameObjects[j + 0x26], 0x40);
            sub_0803F63C(&gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D], &gFrameObjects[j + 0x27], 0x40);
            sub_08040D0C(j + 0x24, 4);
            gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5A].unknown23[0] = 0;
            gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5B].unknown23[0] = 0;
            gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5C].unknown23[0] = 0;
            gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].unknown23[0] = 0;
            sub_08035694(i + (gCounter6ED08_03001800.base60 + 0x72));
        }
    }
    sub_08074DE0(0x34);
    gCounter6ED08_03001800.counterAA++;
}

void sub_0802CFAC(void) {

    s32 done = 0;
    s32 active = 0;
    u32 i;

    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            active++;
            if (gFrameObjects[i + 0x21].flags & 0x8000) {
                if (sub_08036AC4(i + 0x21, 0) != 0) {
                    sub_08040CD0(i + 0x21, 1);
                } else if (!(1 & gCounter6ED08_03001800.flagsF8)) {
                    gFrameObjects[i + 0x21].screenX--;
                    gFrameObjects[i + 0x21].angle = (gFrameObjects[i + 0x21].angle - 0x10) & 0x3FF;
                } else {
                    gFrameObjects[i + 0x21].screenX++;
                    gFrameObjects[i + 0x21].angle = (gFrameObjects[i + 0x21].angle + 0x10) & 0x3FF;
                }
            }
            sub_080353CC((gCounter6ED08_03001800.base60 + i) * 4 + 0x5A);
            sub_080353CC((gCounter6ED08_03001800.base60 + i) * 4 + 0x5B);
            sub_080353CC((gCounter6ED08_03001800.base60 + i) * 4 + 0x5C);
            done += sub_080353CC((gCounter6ED08_03001800.base60 + i) * 4 + 0x5D);
            if (gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].unknown23[0] == 0x10) {
                gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5A].screenY += 8;
                gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5B].screenY -= 8;
                gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5C].screenY -= 8;
                gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].screenY -= 8;
                gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5A].flags |= 0x2000;
                gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5B].flags |= 0x2000;
                gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5C].flags |= 0x2000;
                gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].flags |= 0x2000;
            }
            sub_080356CC((gCounter6ED08_03001800.base60 + i) * 4 + 0x5D, gCounter6ED08_03001800.base60 + 0x72 + i);
        }
    }
    if (done == active) {
        for (i = 0; i <= 2; i++) {
            if (gCounter6ED08_03001800.activeD2[i] != 0)
                sub_080356B4(i + (gCounter6ED08_03001800.base60 + 0x72));
        }
        sub_08074DE0(0x41);
        gCounter6ED08_03001800.counterAA++;
    }
}

void sub_0802D270(void) {

    u32 i;
    u32 j;
    u32 k;

    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            j = 0;
            k = i * 4 + 0x30;
        next:
            sub_0804422C(j + k);
            j++;
            if (j <= 3)
                goto next;
        }
    }
    if (gState0TypedWork.bytes[0x84] == 0x10) {
        for (i = 0; i <= 2; i++) {
            if (gCounter6ED08_03001800.activeD2[i] != 0) {
                sub_0803F63C(&gFrameObjects[i * 4 + 0x24], &gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5A], 0x40);
                sub_0803F63C(&gFrameObjects[i * 4 + 0x25], &gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5B], 0x40);
                sub_0803F63C(&gFrameObjects[i * 4 + 0x26], &gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5C], 0x40);
                sub_0803F63C(&gFrameObjects[i * 4 + 0x27], &gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D], 0x40);
                gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5A].flags |= 0x8000;
                gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5B].flags |= 0x8000;
                gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5C].flags |= 0x8000;
                gFrameObjects[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].flags |= 0x8000;
            }
        }
        sub_08040CD0(0x21, 0x1B);
        gCounter6ED08_03001800.counterAA++;
    } else {
        gState0TypedWork.bytes[0x84]++;
    }
}

void sub_0802D4D8(void) {

    u32 i;

    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            switch (i) {
            case 0:
                sub_0801A574(gDebugMenuTextBuffer, gCounter6ED08_03001800.base60 + i, 0x21);
                break;
            case 1:
                sub_0801A574(gUnknown_030004F2, gCounter6ED08_03001800.base60 + i, 0x21);
                break;
            case 2:
                sub_0801A574(gUnknown_03000506, gCounter6ED08_03001800.base60 + i, 0x21);
                break;
            }
        }
    }
    gState0TypedWork.bytes[0x84]++;
    if (gState0TypedWork.bytes[0x89] == 0 && (1 & *(u8 *)&gRepeatedKeys) && gState0TypedWork.bytes[0x84] > 0x32)
        gState0TypedWork.bytes[0x84] = 0x78;
    if (gState0TypedWork.bytes[0x84] == 0x78) {
        for (i = 0; i <= 2; i++) {
            if (gCounter6ED08_03001800.activeD2[i] != 0)
                sub_08040CD0((gCounter6ED08_03001800.base60 + i) * 4 + 0x21, 4);
        }
        gCounter6ED08_03001800.counterAA++;
    }
}

void sub_0802E70C(void) {

    s32 done = 0;
    s32 active = 0;
    u32 i;

    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            active++;
            if (gCounter6ED08_03001800.valuesD6[i] == 0) {
                done++;
            } else {
                sub_08040BD8(gState0NextCommands_083B6100[gState0TypedWork.bytes[0x84]], i + 0xA);
                if (gFrameObjects[i + 0xA].commandStopped == 0xFF)
                    done++;
            }
        }
    }
    if (done == active)
        gCounter6ED08_03001800.counterAA++;
}

void sub_0802E948(void) {

    u32 i;

    LeDecompress(gUnknown_084E2AB8, (void *)0x06017000);
    CpuFastSet(gUnknown_08510478, (void *)0x050002E0, 8);
    LeDecompress(gUnknown_084CA064, (void *)0x06014E00);
    CpuFastSet(gUnknown_084E45B8, (void *)0x050002C0, 8);
    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            gFramesE948[i + 0x21].flags = ((gCounter6ED08_03001800.byte3C + 2) << 10) | 0xC004;
            gFramesE948[i + 0x21].tableSelector = 0;
            gFramesE948[i + 0x21].screenX = gFramesE948[gCounter6ED08_03001800.slot87 * 4 + 0x5D].screenX;
            gFramesE948[i + 0x21].screenY = gFramesE948[gCounter6ED08_03001800.slot87 * 4 + 0x5D].screenY - 4;
            gFramesE948[i + 0x21].palette = 7;
            gFramesE948[i + 0x21].priority = 0x81;
            gFramesE948[i + 0x21].word30 = gFramesE948[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].screenX;
            gFramesE948[i + 0x21].word32 = gFramesE948[(gCounter6ED08_03001800.base60 + i) * 4 + 0x5D].screenY - 4;
            gFramesE948[i + 0x21].byte24 = 6;
            gFramesE948[i + 0x21].byte23 = 0;
            gFramesE948[i + 0x21].byte29 = 1;
            if (1 & gCounter6ED08_03001800.flagsF8)
                gFramesE948[i + 0x21].flags |= 0x1000;
            sub_08040B90(gState0NextCommands_083B6100[0x6A], i + 0x21);
        }
    }
    gCounter6ED08_03001800.counterAA++;
}
