/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "record_helpers.h"
#include "state0_work.h"

struct Work29354
{
    u8 unknown00[0x51];
    u8 mode51;
    u8 unknown52[0xE];
    u8 base60;
    u8 unknown61[0x49];
    u8 counterAA;
    u8 unknownAB[0x27];
    u8 activeD2[3];
};
struct Setup29354 { u8 unknown00[0xC9]; u8 kindC9; u8 unknownCA[5]; u8 flagsCF; u8 unknownD0[0x30]; };

extern struct Setup29354 gSetup29354[] asm("gSetupBuffer_03000590");
extern struct Work29354 gWork29354 asm("gCounter6ED08_03001800");

void sub_08029354(void);

void sub_08029354(void) {

    u32 i;

    for (i = 0; i < 3; i++) {
        if (gWork29354.activeD2[i] != 0) {
            switch (gWork29354.mode51) {
            case 0:
                gSetup29354[gWork29354.base60 + i].flagsCF |= 1;
                if (gSetup29354[gWork29354.base60 + i].kindC9 == 0xD)
                    sub_08038394(gWork29354.base60 + i, 1);
                else if (gSetup29354[gWork29354.base60 + i].kindC9 == 0xE)
                    sub_08038394(gWork29354.base60 + i, 1);
                break;
            case 1:
                gSetup29354[gWork29354.base60 + i].flagsCF |= 8;
                if (gSetup29354[gWork29354.base60 + i].kindC9 == 0xF)
                    sub_08038394(gWork29354.base60 + i, 1);
                else if (gSetup29354[gWork29354.base60 + i].kindC9 == 0x10)
                    sub_08038394(gWork29354.base60 + i, 1);
                break;
            case 2:
                gSetup29354[gWork29354.base60 + i].flagsCF |= 2;
                if (gSetup29354[gWork29354.base60 + i].kindC9 == 0x11)
                    sub_08038394(gWork29354.base60 + i, 1);
                else if (gSetup29354[gWork29354.base60 + i].kindC9 == 0x12)
                    sub_08038394(gWork29354.base60 + i, 1);
                break;
            case 3:
                gSetup29354[gWork29354.base60 + i].flagsCF |= 4;
                if (gSetup29354[gWork29354.base60 + i].kindC9 == 0x13)
                    goto call3;
                if (gSetup29354[gWork29354.base60 + i].kindC9 == 0x14) {
                call3:
                    sub_08038394(gWork29354.base60 + i, 1);
                }
                break;
            }
        }
    }
    gWork29354.counterAA++;
}
