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
    u8 padBE[3];
    u8 byteC1;
    u8 padC2[7];
    u8 kindC9;
    u8 byteCA;
    u8 byteCB;
    u8 byteCC;
    u8 padCD[0x33];
};
extern struct SetupRecord gSetupRecords[] asm("gSetupBuffer_03000590");

void sub_0802EAD8(void);

void sub_0802EAD8(void) {

    u32 i;

    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            gSetupRecords[gCounter6ED08_03001800.base60 + i].byteC1 = 0;
            gCounter6ED08_03001800.activeD2[i] = sub_0803556C(gCounter6ED08_03001800.base60 + i);
            sub_08034F68(gCounter6ED08_03001800.base60 + i, gCounter6ED08_03001800.activeD2[i], gCounter6ED08_03001800.valuesD6[i]);
            gCounter6ED08_03001800.activeD2[i] |= gCounter6ED08_03001800.flagD1 << 7;
            gCounter6ED08_03001800.valuesD6[i] = gCounter6ED08_03001800.valueC8;
            gSetupRecords[gCounter6ED08_03001800.base60 + i].parts[gCounter6ED08_03001800.activeD2[i] & 0x7F].byte11 -= gCounter6ED08_03001800.valuesD6[i];
            sub_08035194(gCounter6ED08_03001800.base60 + i);
            if (!(gCounter6ED08_03001800.activeD2[i] & 0x7F) && gSetupRecords[gCounter6ED08_03001800.base60 + i].parts[0].byte11 == 0)
                sub_08035234(gCounter6ED08_03001800.base60 + i);
        }
    }
    gCounter6ED08_03001800.counterAA++;
}
