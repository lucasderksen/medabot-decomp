/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "frame.h"
#include "serial.h"
#include "state0_work.h"

struct Frame3A840 {
    u8 pad00[0x2B];
    u8 byte2B;
    u8 byte2C;
    u8 byte2D;
    u8 pad2E[2];
    u16 word30;
    u8 pad32[0xE];
};
struct Words3A840 {
    u8 pad00[0x102];
    u16 words[8];
};

extern struct Frame3A840 gFrames3A840[] asm("gFrameObjects");
extern struct Words3A840 gWords3A840 asm("gCounter6ED08_03001800");
extern void sub_0803D450(void);
extern void sub_0803D4AC(void);

void sub_0803A840(void);

void sub_0803A840(void) {


    sub_0803D450();
    if (!(2 & gCounter6ED08_03001800.flagsF8)) {
        gFrames3A840[2].byte2B = 1;
        if (2 & gCounter6ED08_03001800.flagsF6)
            gFrames3A840[2].byte2C = *(u16 *)((u8 *)&gCounter6ED08_03001800.value102 + ((gCounter6ED08_03001800.index162 + 4) << 1));
        else
            gFrames3A840[2].byte2C = *(u16 *)((u8 *)&gCounter6ED08_03001800.value102 + ((gCounter6ED08_03001800.partA7 + 4) << 1));
        gFrames3A840[2].word30 = gWords3A840.words[0];
        gFrames3A840[2].byte2D = 1;
    } else {
        gFrames3A840[1].byte2B = 1;
        if (2 & gCounter6ED08_03001800.flagsF6)
            gFrames3A840[1].byte2C = *(u16 *)((u8 *)&gCounter6ED08_03001800.value102 + ((gCounter6ED08_03001800.index162 + 1) << 1));
        else
            gFrames3A840[1].byte2C = *(u16 *)((u8 *)&gCounter6ED08_03001800.value102 + ((gCounter6ED08_03001800.partA7 + 1) << 1));
        gFrames3A840[1].word30 = gWords3A840.words[0];
        gFrames3A840[1].byte2D = 1;
    }
    sub_0803D4AC();
}
