/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "frame.h"
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
    u8 pad0[0x48];
    struct SetupPart parts[3];
    u8 pad90[0x2C];
    u8 flagsBC;
    u8 flagsBD;
    u8 padBE[0xB];
    u8 kindC9;
    u8 byteCA;
    u8 byteCB;
    u8 byteCC;
    u8 padCD[0x33];
};
extern s8 sub_08036E54(s16);
extern struct SetupRecord gSetupRecords[] asm("gSetupBuffer_03000590");

void sub_0802DBD8(void);

void sub_0802DBD8(void) {

    u32 i;

    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            gSetupRecords[gCounter6ED08_03001800.base60 + i].kindC9 = 0x2B;
            gSetupRecords[gCounter6ED08_03001800.base60 + i].byteCB = sub_08036E54(gCounter6ED08_03001800.valueE8);
            gSetupRecords[gCounter6ED08_03001800.base60 + i].byteCC = sub_08036E54(gCounter6ED08_03001800.valueEC);
            switch (gCounter6ED08_03001800.activeD2[i] & 0x7F) {
            case 1:
                gSetupRecords[gCounter6ED08_03001800.base60 + i].byteCA = 2;
                break;
            case 2:
                gSetupRecords[gCounter6ED08_03001800.base60 + i].byteCA = 3;
                break;
            default:
                gSetupRecords[gCounter6ED08_03001800.base60 + i].byteCA = 1;
                break;
            }
        }
    }
    gCounter6ED08_03001800.counterAA++;
}
