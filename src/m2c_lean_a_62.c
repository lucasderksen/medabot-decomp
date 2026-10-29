/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "continued_late_graphics.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "gba.h"
#include "record_helpers.h"
#include "serial.h"
#include "sound_samples.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct RosterMember120C8 { u8 pad0[3]; u8 id; u8 pad4[8]; };
struct Roster120C8 { u8 pad0[2]; u8 count; u8 pad3; struct RosterMember120C8 members[3]; };
struct SetupView4B34 { u8 pad00[0xDD]; u8 byteDD; u8 padDE[0x22]; };
struct Part15838 {
    u8 name[13];
    u8 pad0D[3];
    u8 byte10;
    u8 data11[6];
    u8 id17;
};
struct Setup15838 {
    u8 pad00[0x41];
    u8 byte41;
    u8 pad42[6];
    struct Part15838 parts[4];
    u8 padA8[0x58];
};

extern const u8 gUnknown_083AD06A[][2];
extern struct Roster120C8 gRoster120C8 asm("gCounter6ED08_03001800");
extern struct Setup15838 gSetup15838[] asm("gSetupBuffer_03000590");
extern struct SetupView4B34 gSetupView4B34[] asm("gSetupBuffer_03000590");

void sub_080120C8(void);
void sub_08014B34(void);
void sub_08015838(u32 index, u8 *destination);

void sub_080120C8(void) {

    u32 i;

    for (i = 0; i <= 2; i++) {
        if (gRoster120C8.count > i) {
            sub_08042B58(gRoster120C8.members[i].id, 3, gUnknown_0300052E);
            sub_080435B0(gUnknown_0300052E[1] - 0x64, gUnknown_083AD06A[i][0], gUnknown_083AD06A[i][1], *(volatile u16 *)0x04000008, 0x8300);
        } else {
            sub_080435B0(0xFF, gUnknown_083AD06A[i][0], gUnknown_083AD06A[i][1], *(volatile u16 *)0x04000008, 0x8300);
        }
    }
}

void sub_08014B34(void) {


    u16 word;

    if (gCounter6ED08_03001800.frame51 != 3) {
        gMainSerialOutgoingWork.word06 = gSetupView4B34[gCounter6ED08_03001800.frame51].byteDD
            + (u16)(((gCounter6ED08_03001800.toggle1AF << 8) & 0x100) + 0x8000);
        gState0TypedWork.widths.word86++;
        if (!(gState0TypedWork.widths.word86 & 1)) {
            gCounter6ED08_03001800.toggle1AF ^= 1;
            gCounter6ED08_03001800.frame51++;
        }
    }
    if (gCounter6ED08_03001800.frame53 != 3) {
        word = gMainSerialOutgoingWork.words[gUnknown_03000B90 ^ 1][1];
        if ((0x8000 & word) && ((u16)(0x100 & word) >> 8) != gCounter6ED08_03001800.toggle1B0) {
            gCounter6ED08_03001800.toggle1B0 ^= 1;
            gSetupView4B34[gCounter6ED08_03001800.frame53 + 3].byteDD = word;
            gCounter6ED08_03001800.frame53++;
        }
    }
    if (gCounter6ED08_03001800.frame51 == 3) if (gCounter6ED08_03001800.frame53 == 3) {
        gUnknown_0300137C++;
        gState0TypedWork.widths.word86 = 0;
    }
}

void sub_08015838(u32 index, u8 *destination) {

    if (gSetup15838[index].parts[0].data11[0] != 0)
        *destination = gSetup15838[index].parts[0].id17;
    else
        *destination = gSetup15838[index].byte41 + 0x78;
    do {
        destination++;
    } while (0);
    if (gSetup15838[index].parts[1].data11[0] != 0)
        *destination = gSetup15838[index].parts[1].id17;
    else
        *destination = gSetup15838[index].byte41 + 0x78;
    destination++;
    if (gSetup15838[index].parts[2].data11[0] != 0)
        *destination = gSetup15838[index].parts[2].id17;
    else
        *destination = gSetup15838[index].byte41 + 0x78;
    destination++;
    if (gSetup15838[index].parts[3].data11[0] != 0)
        *destination = gSetup15838[index].parts[3].id17;
    else
        *destination = gSetup15838[index].byte41 + 0x78;
}
