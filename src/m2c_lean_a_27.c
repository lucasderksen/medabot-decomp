/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "record_helpers.h"
#include "state0_inventory.h"
#include "state0_work.h"

struct Part1BE48 { u8 unknown00[2]; u8 byte02; u8 unknown03[0x15]; };
struct Setup1BE48
{
    u8 unknown00[5];
    u8 byte05;
    u8 unknown06[0x1A];
    u8 level20[8];
    u8 exp28[8];
    u8 unknown30[0x18];
    struct Part1BE48 parts[3];
    u8 unknown90[0x19];
    u8 byteA9;
    u8 unknownAA[0x33];
    u8 byteDD;
    u8 unknownDE[0x22];
};
struct Work1BE48 { u8 unknown00[0x164]; u8 enabled164; u8 flag165; u8 slot166; u8 level167; };

extern struct Setup1BE48 gSetup1BE48[] asm("gSetupBuffer_03000590");
extern struct Work1BE48 gWork1BE48 asm("gCounter6ED08_03001800");
extern void sub_0801BF14(u32);

void sub_0801BE48(u32 index);

void sub_0801BE48(u32 index) {

    u8 slot;

    if (index > 2)
        return;
    if (gState0TypedWork.bytes[0x89] == 1)
        return;
    if (gSetup1BE48[index].byte05 == 0x64)
        return;
    if (gWork1BE48.enabled164 == 0)
        return;
    if (gSetup1BE48[index].byteDD > 3)
        slot = gSetup1BE48[index].byteA9;
    else
        slot = gSetup1BE48[index].parts[gSetup1BE48[index].byteDD - 1].byte02;
    if (gSetup1BE48[index].level20[slot] == 0x64) {
        if (gSetup1BE48[index].exp28[slot] < 7)
            gSetup1BE48[index].exp28[slot]++;
    } else if (++gSetup1BE48[index].exp28[slot] > 7) {
        gSetup1BE48[index].exp28[slot] = 0;
        gSetup1BE48[index].level20[slot]++;
        gWork1BE48.flag165 = 1;
        gWork1BE48.slot166 = slot;
        gWork1BE48.level167 = gSetup1BE48[index].level20[slot];
    }
    sub_0801BF14(index);
}
