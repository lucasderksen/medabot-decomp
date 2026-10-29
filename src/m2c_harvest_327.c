/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct SelectionWork2BEEC { u8 p0[0x60]; u8 b60; u8 p61[0x87 - 0x61]; u8 b87; u8 p88[0xAA - 0x88]; u8 bAA; u8 pAB[0xD2 - 0xAB]; u8 bD2[4]; u16 hD6[3]; };

extern struct SelectionWork2BEEC gCounter6ED08_03001800;
extern void sub_0803836C(void);

void sub_0802BEEC(void);

void sub_0802BEEC(void) {

    u32 firstSlot;
    u32 secondSlot;
    u8 *firstRecord;
    u8 *secondRecord;
    u32 setupAddress;
    u16 *selectedWords;
    struct SelectionWork2BEEC *c2;
    u8 *setup;
    sub_0803836C();
    gCounter6ED08_03001800.b60 = (u8) sub_08032FC4((u32) gCounter6ED08_03001800.b87);
    firstSlot = 0;
    do {
        setup = gSetupBuffer_03000590;
        firstRecord = (u8 *)(((gCounter6ED08_03001800.b60 + firstSlot) << 8) + (u32)setup);
        if ((firstRecord[0x40] != 0) && (firstRecord[0x59] != 0)) {
            gCounter6ED08_03001800.bD2[firstSlot] = 1;
        }
        firstSlot += 1;
    } while (firstSlot <= 2U);
    gCounter6ED08_03001800.b60 = (u8) sub_08032FB8((u32) gCounter6ED08_03001800.b87);
    secondSlot = 0;
    setup = gSetupBuffer_03000590;
    setupAddress = (u32)setup;
    c2 = &gCounter6ED08_03001800;
    selectedWords = (u16 *)((u32)c2 + 0xD6);
    do {
        secondRecord = (u8 *)(((gCounter6ED08_03001800.b60 + secondSlot) << 8) + setupAddress);
        if ((secondRecord[0x40] != 0) && (secondRecord[0x59] != 0)) {
            *selectedWords = 1;
        }
        selectedWords += 1;
        secondSlot += 1;
    } while (secondSlot <= 2U);
    c2->bAA = c2->bAA + 1;
}
