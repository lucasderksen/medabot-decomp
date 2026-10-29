/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"

struct Setup8130 { u8 pad00[0xD5]; u8 byteD5; u8 padD6[0x2A]; };

extern struct Setup8130 gSetup8130[] asm("gSetupBuffer_03000590");
extern void sub_08035740(u8 *, s32, u32);

void sub_08028130(void);

void sub_08028130(void) {

    if (gCounter6ED08_03001800.records28[gCounter6ED08_03001800.byte8A].pad1[1] != 0 && gCounter6ED08_03001800.records28[gCounter6ED08_03001800.byte8A].kind3 == 0x5A) {
        gCounter6ED08_03001800.frame53 = 1;
        sub_08035740(&gCounter6ED08_03001800.records28[gCounter6ED08_03001800.byte8A].value4, gCounter6ED08_03001800.valueE8 >> 1, 0xFF);
        sub_08035740(gCounter6ED08_03001800.records28[gCounter6ED08_03001800.byte8A].pad5, (gCounter6ED08_03001800.valueEC + gSetup8130[gCounter6ED08_03001800.slot87].byteD5) >> 1, 0xFF);
        gCounter6ED08_03001800.counterAA++;
    } else {
        gCounter6ED08_03001800.frame53 = 0;
        gCounter6ED08_03001800.records28[gCounter6ED08_03001800.byte8A].pad1[1] = 1;
        gCounter6ED08_03001800.records28[gCounter6ED08_03001800.byte8A].kind3 = 0x5A;
        gCounter6ED08_03001800.records28[gCounter6ED08_03001800.byte8A].value4 = 0;
        gCounter6ED08_03001800.records28[gCounter6ED08_03001800.byte8A].pad5[0] = 0;
        sub_08035740(&gCounter6ED08_03001800.records28[gCounter6ED08_03001800.byte8A].value4, gCounter6ED08_03001800.valueE8, 0xFF);
        sub_08035740(gCounter6ED08_03001800.records28[gCounter6ED08_03001800.byte8A].pad5, gCounter6ED08_03001800.valueEC + gSetup8130[gCounter6ED08_03001800.slot87].byteD5, 0xFF);
        gCounter6ED08_03001800.counterAA++;
    }
}
