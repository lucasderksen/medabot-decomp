/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "display_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "render_work.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct LeanCounter1800 {
    u8 unknown00[0x3C];
    u8 byte3C;
    u8 unknown3D[0x7];
    u8 byte44;
    u8 unknown45[0xC];
    u8 byte51;
    u8 unknown52[0xE];
    u8 firstObject;
    u8 unknown61[0x21];
    u8 byte82;
    u8 unknown83[4];
    u8 byte87;
    u8 byte88;
    u8 unknown89[2];
    u8 group8B;
    u8 unknown8C[0x1B];
    u8 byteA7;
    u8 unknownA8[2];
    u8 stepAA;
    u8 unknownAB[0x1D];
    u16 valueC8;
    u8 unknownCA[6];
    u8 slotD0;
    u8 unknownD1;
    u8 activeD2[4];
    u16 valuesD6[4];
    u8 unknownDE[0x1A];
    u8 flagsF8;
    u8 unknownF9[0x1F];
    u8 byte118;
    u8 byte119;
    u8 byte11A;
    u8 unknown11B;
    u8 record11C[0x18];
    u8 unknown134[0x20];
    u16 positions[4];
};

extern const u8 *gState0NextCommands_083B6100[];
extern struct LeanCounter1800 gCounter6ED08_03001800;
extern u8 gFamilyKeyBytes49558_0300058C;

void sub_080169AC(void);
void sub_08021A6C(void);

void sub_080169AC(void) {

    u8 old = gCounter6ED08_03001800.byte82;

    if (gFamilyKeyBytes49558_0300058C & 0x40)
        gCounter6ED08_03001800.byte82 = 1;
    if (gFamilyKeyBytes49558_0300058C & 0x80)
        gCounter6ED08_03001800.byte82 = 0;
    if (gFamilyKeyBytes49558_0300058C & 0x20)
        gCounter6ED08_03001800.byte82 = 2;
    if (gFamilyKeyBytes49558_0300058C & 0x10)
        gCounter6ED08_03001800.byte82 = 3;
    if (gCounter6ED08_03001800.byte82 != old) {
        sub_08074DE0(2);
        sub_0801677C();
        sub_080167BC(1);
        sub_08016804(1);
        sub_0801684C(1);
        sub_08016894(1);
        sub_08016A3C();
        sub_08016AD8();
        sub_08016D18();
        sub_08016DCC();
        sub_0801BACC();
        sub_0801B894();
    }
}

void sub_08021A6C(void) {

    struct FrameObject *objects;

    sub_08040BD8(gState0NextCommands_083B6100[0x3B], 0x21);
    objects = (struct FrameObject *)gActionTransferBuffer_03003470;
    sub_0803F63C(&objects[0], &objects[1], 0x40);
    sub_0803F63C(&objects[0], &objects[2], 0x40);
    *(s16 *)&objects[0].unknown2C[6] = 0x58;
    objects[0].unknown23[1] = 6;
    *(s16 *)&objects[1].unknown2C[6] = 0x40;
    objects[1].unknown23[1] = 6;
    *(s16 *)&objects[2].unknown2C[6] = 0x28;
    objects[2].unknown23[1] = 6;
    if (gCounter6ED08_03001800.flagsF8 & 1) {
        *(s16 *)&objects[0].unknown2C[4] = 0x88;
        *(s16 *)&objects[1].unknown2C[4] = 0x88;
        *(s16 *)&objects[2].unknown2C[4] = 0x88;
    } else {
        *(s16 *)&objects[0].unknown2C[4] = 0x68;
        *(s16 *)&objects[1].unknown2C[4] = 0x68;
        *(s16 *)&objects[2].unknown2C[4] = 0x68;
    }
    gCounter6ED08_03001800.stepAA++;
}
