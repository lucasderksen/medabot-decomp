/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "battle_work.h"
#include "continued_late_graphics.h"
#include "coordinate_helpers.h"
#include "display_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "serial.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct Setup14404 { u8 pad00[0xBD]; u8 flagsBD; u8 padBE[0xB]; u8 kindC9; u8 padCA[0x36]; };
struct Part14F90 {
    u8 name[13];
    u8 pad0D[3];
    u8 byte10;
    u8 data11[6];
    u8 id17;
};
struct Setup14F90 {
    u8 pad00[0x43];
    u8 parts43[4];
    u8 pad47;
    struct Part14F90 parts[4];
    u8 padA8[0x10];
    u8 byteB8;
    u8 padB9;
    u8 byteBA;
    u8 padBB[0x45];
};
struct PartD5A8 {
    u8 name[13];
    u8 pad0D[3];
    u8 byte10;
    u8 data11[6];
    u8 id17;
};
struct SetupD5A8 {
    u8 pad00[0x40];
    u8 active40;
    u8 pad41[7];
    struct PartD5A8 parts[4];
    u8 padA8[0x15];
    u8 flagsBD;
    u8 padBE[2];
    u8 flagsC0;
    u8 padC1[8];
    u8 kindC9;
    u8 padCA[0x14];
    u8 partDE;
    u8 partDF;
    u8 padE0[0x20];
};

extern s32 sub_0801A6EC(u8);
extern struct Setup14404 gSetup14404s[] asm("gSetupBuffer_03000590");
extern struct Setup14F90 gSetup14F90[] asm("gSetupBuffer_03000590");
extern struct SetupD5A8 gSetupD5A8[] asm("gSetupBuffer_03000590");
extern u8 gContinuedByte_03002B64;
extern u8 gTransferReceiveBuffers[];
extern void sub_08019078(void);
extern void sub_080195C0(void);
extern void sub_0801A0D0(void);
extern void sub_0801A678(void);
extern void sub_080356B4(u32);

void sub_08004AF8(void);
void sub_0800ED10(void);
void sub_0800EDA0(void);
void sub_08014404(void);
void sub_08014F90(u32 first, u32 count);
void sub_0801D5A8(void);
void sub_0801D738(void);
void sub_0801D9DC(void);
void sub_0801DAEC(void);

void sub_08004AF8(void) {

    u8 *row;
    u16 count;
    u16 word;

    sub_08004E74();
    sub_080054C0();
    if (gCounter6ED08_03001800.frame51 != 3) {
        row = gSetupBuffer_03000590 + (gCounter6ED08_03001800.frame51 << 8);
        gMainSerialOutgoingWork.word06 = row[gCounter6ED08_03001800.count52]
            + (u16)(((gCounter6ED08_03001800.toggle1AF << 8) & 0x100) + 0x8000);
        if (++gState0TypedWork.widths.word86 == 4) {
            gState0TypedWork.widths.word86 = 0;
            gCounter6ED08_03001800.toggle1AF ^= 1;
            if (++gCounter6ED08_03001800.count52 == 0x48) {
                gCounter6ED08_03001800.frame51++;
                gCounter6ED08_03001800.count52 = 0;
            }
        }
    }
    if (gCounter6ED08_03001800.frame53 != 3) {
        word = gMainSerialOutgoingWork.words[gUnknown_03000B90 ^ 1][1];
        if ((0x8000 & word) && ((u16)(0x100 & word) >> 8) != gCounter6ED08_03001800.toggle1B0) {
            gCounter6ED08_03001800.toggle1B0 ^= 1;
            row = gTransferReceiveBuffers + (gCounter6ED08_03001800.frame53 << 8);
            row[gCounter6ED08_03001800.count54] = word;
            gCounter6ED08_03001800.sum1A8 = (gCounter6ED08_03001800.sum1A8 + (word & 0xFF)) & 0x7FFF;
            if (++gCounter6ED08_03001800.count54 == 0x48) {
                gCounter6ED08_03001800.frame53++;
                gCounter6ED08_03001800.count54 = 0;
            }
        }
    }
    if (gCounter6ED08_03001800.frame51 == 3) if (gCounter6ED08_03001800.frame53 == 3) {
        gUnknown_0300137C = 0x3A;
        gState0TypedWork.widths.word86 = 0;
    }
}

void sub_0800ED10(void) {

    u32 i;

    i = 0;
    do {
        if (gObjectHalfwordBytes[(gState0TypedWork.bytes[0x3E] * 0xF0) + (gState0TypedWork.bytes[0x3F] * 8) + (i * 2)] != 0) {
            sub_08042950(gObjectHalfwordBytes[(gState0TypedWork.bytes[0x3E] * 0xF0) + (gState0TypedWork.bytes[0x3F] * 8) + (i * 2)], 0x16, i * 2 + 5, 2, *(volatile u16 *)0x0400000A, 0x7360);
        } else {
            sub_08042950(0, 0x16, i * 2 + 5, 2, *(volatile u16 *)0x0400000A, 0x7360);
        }
        i++;
    } while (i <= 3);
}

void sub_0800EDA0(void) {

    u32 i;

    i = 0;
    do {
        if (gObjectHalfwordBytes[(gState0TypedWork.bytes[0x3E] * 0xF0) + (gState0TypedWork.bytes[0x3F] * 8) + (i * 2) + 1] != 0) {
            sub_08042950(gObjectHalfwordBytes[(gState0TypedWork.bytes[0x3E] * 0xF0) + (gState0TypedWork.bytes[0x3F] * 8) + (i * 2) + 1], 0x19, i * 2 + 5, 1, *(volatile u16 *)0x0400000A, 0x6360);
        } else {
            sub_08042950(0, 0x19, i * 2 + 5, 1, *(volatile u16 *)0x0400000A, 0x6360);
        }
        i++;
    } while (i <= 3);
}

void sub_08014404(void) {

    sub_080195C0();
    sub_08019078();
    gSetup14404s[gCounter6ED08_03001800.slot87].flagsBD ^= 4;
    sub_08015A00(gCounter6ED08_03001800.slot87,
        gFrameObjects[0x5D + gCounter6ED08_03001800.slot87 * 4].screenX,
        gFrameObjects[0x5D + gCounter6ED08_03001800.slot87 * 4].screenY - 4);
    sub_0801A678();
    sub_08031A3C(gCounter6ED08_03001800.slot87);
    if (gCounter6ED08_03001800.slot87 > 2) {
        if (gState0TypedWork.bytes[0x89] != 1) {
            sub_08015358(gCounter6ED08_03001800.slot87);
            gUnknown_0300137C = 0x45;
        } else {
            if (gSetup14404s[gCounter6ED08_03001800.slot87].kindC9 == 0x2C) {
                sub_08015358(gCounter6ED08_03001800.slot87);
            }
            gUnknown_0300137C = 0xA0;
        }
    } else if (gSetup14404s[gCounter6ED08_03001800.slot87].kindC9 == 0x2C) {
        sub_08015358(gCounter6ED08_03001800.slot87);
        sub_08018900(gCounter6ED08_03001800.slot87);
        if (gState0TypedWork.bytes[0x89] != 1) {
            gUnknown_0300137C = 0x45;
        } else {
            gUnknown_0300137C = 0xA0;
        }
    } else {
        if (sub_0801A6EC(gCounter6ED08_03001800.slot87) != 0) {
            if (!(2 & gContinuedByte_03002B64)) {
                sub_08015358(gCounter6ED08_03001800.slot87);
                sub_08018900(gCounter6ED08_03001800.slot87);
                gUnknown_0300137C = 0x45;
                return;
            }
            sub_0801A744(gCounter6ED08_03001800.slot87);
        }
        gCounter6ED08_03001800.buffer64[0x1C] = gCounter6ED08_03001800.slot87;
        gCounter6ED08_03001800.buffer64[0x1D] = 0;
        gCounter6ED08_03001800.buffer64[0x1E] = 0;
        gCounter6ED08_03001800.buffer64[0x1F] = 0;
        gCounter6ED08_03001800.buffer64[0x21] = 0;
        sub_0801A0D0();
        gUnknown_0300137C = 4;
    }
}

void sub_08014F90(u32 first, u32 count) {

    u32 i;

    i = 0;
    if (i < count) do {
        gSetup14F90[first].byteB8 = first;
        gSetup14F90[first].byteBA = 1;
        sub_08042B58(gSetup14F90[first].parts43[0], 0, gUnknown_0300052E);
        sub_0803F63C(gUnknown_0300052E, gSetup14F90[first].parts[0].name, 13);
        gSetup14F90[first].parts[0].byte10 = gSetup14F90[first].parts[0].name[8];
        gSetup14F90[first].parts[0].data11[0] = gSetup14F90[first].parts[0].name[4];
        gSetup14F90[first].parts[0].id17 = gSetup14F90[first].parts43[0];
        sub_08042B58(gSetup14F90[first].parts43[1], 1, gUnknown_0300052E);
        sub_0803F63C(gUnknown_0300052E, gSetup14F90[first].parts[1].name, 13);
        gSetup14F90[first].parts[1].data11[0] = gSetup14F90[first].parts[1].name[4];
        gSetup14F90[first].parts[1].id17 = gSetup14F90[first].parts43[1];
        sub_08042B58(gSetup14F90[first].parts43[2], 2, gUnknown_0300052E);
        sub_0803F63C(gUnknown_0300052E, gSetup14F90[first].parts[2].name, 13);
        gSetup14F90[first].parts[2].data11[0] = gSetup14F90[first].parts[2].name[4];
        gSetup14F90[first].parts[2].id17 = gSetup14F90[first].parts43[2];
        sub_08042B58(gSetup14F90[first].parts43[3], 3, gUnknown_0300052E);
        sub_0803F63C(gUnknown_0300052E, gSetup14F90[first].parts[3].name, 13);
        sub_0803F63C(&gSetup14F90[first].parts[3].name[4], gSetup14F90[first].parts[3].data11, 6);
        gSetup14F90[first].parts[3].id17 = gSetup14F90[first].parts43[3];
        first++;
    } while (++i < count);
}

void sub_0801D5A8(void) {

    u32 first;
    u32 i;

    if (4 & gSetupD5A8[gCounter6ED08_03001800.slot87].flagsC0) {
        gCounter6ED08_03001800.flagB5 = 1;
        return;
    }
    first = sub_08032FC4(gCounter6ED08_03001800.value88);
    for (i = 0; i <= 2; i++) {
        if (gSetupD5A8[first + i].active40 != 0
            && (8 & gSetupD5A8[first + i].flagsBD)
            && gCounter6ED08_03001800.value88 != first + i
            && gSetupD5A8[first + i].kindC9 != 0x2F
            && gSetupD5A8[first + i].parts[gSetupD5A8[first + i].partDE - 1].data11[0] != 0) {
            gCounter6ED08_03001800.flagDE = first + i + 1;
            gCounter6ED08_03001800.partDF = gSetupD5A8[first + i].partDF;
        }
    }
    if (gCounter6ED08_03001800.flagDE != 0) {
        gCounter6ED08_03001800.counterAA++;
    } else {
        gCounter6ED08_03001800.flagB5 = 1;
    }
}

void sub_0801D738(void) {

    sub_0803F63C(&gFrameObjects[(gCounter6ED08_03001800.flagDE - 1) * 4 + 0x5A], &gFrameObjects[0x21], 0x40);
    sub_0803F63C(&gFrameObjects[(gCounter6ED08_03001800.flagDE - 1) * 4 + 0x5B], &gFrameObjects[0x22], 0x40);
    sub_0803F63C(&gFrameObjects[(gCounter6ED08_03001800.flagDE - 1) * 4 + 0x5C], &gFrameObjects[0x23], 0x40);
    sub_0803F63C(&gFrameObjects[(gCounter6ED08_03001800.flagDE - 1) * 4 + 0x5D], &gFrameObjects[0x24], 0x40);
    sub_08040D0C(0x21, 4);
    sub_08015838(gCounter6ED08_03001800.flagDE - 1, gCounter6ED08_03001800.buffer64);
    sub_0804305C(gCounter6ED08_03001800.buffer64[0], gCounter6ED08_03001800.buffer64[1],
        gCounter6ED08_03001800.buffer64[2], gCounter6ED08_03001800.buffer64[3],
        gCounter6ED08_03001800.flagDE - 1, gCounter6ED08_03001800.flagDE * 4 + 0x56,
        gFrameObjects[0x59 + gCounter6ED08_03001800.flagDE * 4].screenX,
        gFrameObjects[0x59 + gCounter6ED08_03001800.flagDE * 4].screenY - 4,
        (1 & gCounter6ED08_03001800.flagsF8) ^ 1, gCounter6ED08_03001800.byte3C + 2,
        gCounter6ED08_03001800.flagDE * 4 + 0x56);
    sub_08043240(gCounter6ED08_03001800.flagDE * 4 + 0x56, 8);
    gState0TypedWork.bytes[0x84] = 0;
    gCounter6ED08_03001800.counterAA++;
}

void sub_0801D9DC(void) {

    s32 arrived;

    arrived = 0;
    if (!(1 & gCounter6ED08_03001800.flagsF8)) {
        gFrameObjects[0x59 + gCounter6ED08_03001800.flagDE * 4].screenX -= 2;
        if (gFrameObjects[0x59 + gCounter6ED08_03001800.flagDE * 4].screenX <= 0x78) {
            arrived = 1;
        }
    } else {
        gFrameObjects[0x59 + gCounter6ED08_03001800.flagDE * 4].screenX += 2;
        if (gFrameObjects[0x59 + gCounter6ED08_03001800.flagDE * 4].screenX > 0x77) {
            arrived = 1;
        }
    }
    sub_080432A0((gCounter6ED08_03001800.flagDE - 1) * 4 + 0x5A, gCounter6ED08_03001800.flagDE - 1, (1 & gCounter6ED08_03001800.flagsF8) ^ 1);
    if (arrived) {
        u32 root = (u32)gFrameObjects;
        ((struct FrameObject *)((gCounter6ED08_03001800.flagDE << 8) + root))[0x59].unknown23[1] = 8;
        ((struct FrameObject *)((gCounter6ED08_03001800.flagDE << 8) + root))[0x59].unknown23[2] = 0;
        gFrameObjects[0x59 + gCounter6ED08_03001800.flagDE * 4].value30 = 0;
        gFrameObjects[0x59 + gCounter6ED08_03001800.flagDE * 4].screenX = 0x78;
        gFrameObjects[gCounter6ED08_03001800.flagDE + 0x71].screenX = 0x78;
        gFrameObjects[gCounter6ED08_03001800.flagDE + 0x71].screenY = gFrameObjects[gCounter6ED08_03001800.slot87 + 0x72].screenY;
        gCounter6ED08_03001800.counterAA++;
    }
}

void sub_0801DAEC(void) {

    if (sub_0803526C(gCounter6ED08_03001800.flagDE * 4 + 0x59,
            gFrameObjects[0x5D + gCounter6ED08_03001800.slot87 * 4].screenY,
            (s16)(gFrameObjects[0x5D + gCounter6ED08_03001800.slot87 * 4].screenY + 0x10)) != 0) {
        sub_080356CC(gCounter6ED08_03001800.flagDE * 4 + 0x59, gCounter6ED08_03001800.flagDE + 0x71);
        sub_080432A0((gCounter6ED08_03001800.flagDE - 1) * 4 + 0x5A, gCounter6ED08_03001800.flagDE - 1, (1 & gCounter6ED08_03001800.flagsF8) ^ 1);
        sub_08074DE0(0x41);
        sub_08015838(gCounter6ED08_03001800.flagDE - 1, gCounter6ED08_03001800.buffer64);
        sub_0804305C(gCounter6ED08_03001800.buffer64[0], gCounter6ED08_03001800.buffer64[1],
            gCounter6ED08_03001800.buffer64[2], gCounter6ED08_03001800.buffer64[3],
            gCounter6ED08_03001800.flagDE - 1, gCounter6ED08_03001800.flagDE * 4 + 0x56,
            gFrameObjects[0x59 + gCounter6ED08_03001800.flagDE * 4].screenX,
            gFrameObjects[0x59 + gCounter6ED08_03001800.flagDE * 4].screenY - 4,
            (1 & gCounter6ED08_03001800.flagsF8) ^ 1, gCounter6ED08_03001800.byte3C + 2,
            gCounter6ED08_03001800.flagDE * 4 + 0x56);
        gFrameObjects[0x57 + gCounter6ED08_03001800.flagDE * 4].angle = 0;
        gFrameObjects[0x58 + gCounter6ED08_03001800.flagDE * 4].angle = 0;
        sub_080356B4(gCounter6ED08_03001800.flagDE + 0x71);
        gState0TypedWork.bytes[0x84] = 0;
        gCounter6ED08_03001800.counterAA++;
    } else {
        sub_080432A0((gCounter6ED08_03001800.flagDE - 1) * 4 + 0x5A, gCounter6ED08_03001800.flagDE - 1, (1 & gCounter6ED08_03001800.flagsF8) ^ 1);
        sub_080356CC(gCounter6ED08_03001800.flagDE * 4 + 0x59, gCounter6ED08_03001800.flagDE + 0x71);
    }
}
