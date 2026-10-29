/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "frame.h"
#include "record_helpers.h"
#include "state0_work.h"

struct LeanSetupSide { u8 bytes[0x100]; };
struct LeanCounterE8 { u8 unknown00[0x87]; u8 byte87; u8 byte88; u8 unknown89[0x21]; u8 stepAA; u8 unknownAB[0x3D]; s16 valueE8; u8 unknownEA[2]; s16 valueEC; };

extern s32 sub_08036E54(s32 value);
extern struct LeanCounterE8 gCounter6ED08_03001800;

void sub_08023FB8(void);

void sub_08023FB8(void) {

    struct LeanSetupSide *sides = (struct LeanSetupSide *)gSetupBuffer_03000590;

    sides[gCounter6ED08_03001800.byte88].bytes[0xC9] = 0x29;
    sides[gCounter6ED08_03001800.byte88].bytes[0xCA] = 0;
    sides[gCounter6ED08_03001800.byte88].bytes[0xCB] = sub_08036E54(gCounter6ED08_03001800.valueE8);
    sides[gCounter6ED08_03001800.byte88].bytes[0xCC] = sub_08036E54(gCounter6ED08_03001800.valueEC);
    sides[gCounter6ED08_03001800.byte87].bytes[0xC4] = 0x29;
    sides[gCounter6ED08_03001800.byte87].bytes[0xC5] = 0;
    sides[gCounter6ED08_03001800.byte87].bytes[0xC6] = sub_08036E54(gCounter6ED08_03001800.valueE8);
    sides[gCounter6ED08_03001800.byte87].bytes[0xC7] = sub_08036E54(gCounter6ED08_03001800.valueEC);
    gCounter6ED08_03001800.stepAA++;
}
