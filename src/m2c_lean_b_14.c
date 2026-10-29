/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "frame.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct SetupPart {
    u8 pad0[2];
    u8 byte2;
    u8 pad3;
    u8 byte4;
    u8 pad5[0xC];
    u8 byte11;
    u8 pad12[6];
};
struct SetupRecord {
    u8 pad0[0x40];
    u8 byte40;
    u8 pad41[7];
    struct SetupPart parts[3];
    u8 byte90;
    u8 byte91;
    u8 pad92[0x16];
    u8 byteA8;
    u8 padA9[0x13];
    u8 flagsBC;
    u8 flagsBD;
    u8 padBE[0xB];
    u8 kindC9;
    u8 byteCA;
    u8 byteCB;
    u8 byteCC;
    u8 padCD[0x33];
};
extern struct SetupRecord gSetupRecords[] asm("gSetupBuffer_03000590");

void sub_0802D5BC(void);

void sub_0802D5BC(void) {

    s32 emptied = 0;
    u32 i;

    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            sub_08035164(gCounter6ED08_03001800.base60 + i, 0, gCounter6ED08_03001800.valuesD6[i]);
            if (gSetupRecords[gCounter6ED08_03001800.base60 + i].parts[0].byte11 == 0) {
                sub_08035234(gCounter6ED08_03001800.base60 + i);
                gCounter6ED08_03001800.activeD2[i] = 0x80;
                emptied = 1;
            } else if (!(gSetupRecords[gCounter6ED08_03001800.base60 + i].flagsBD & 4)) {
                gSetupRecords[gCounter6ED08_03001800.base60 + i].flagsBD |= 1;
            }
        }
    }
    if (emptied)
        gCounter6ED08_03001800.counterAA = 0x10;
    else
        gCounter6ED08_03001800.counterAA++;
}
