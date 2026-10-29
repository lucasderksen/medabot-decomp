/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "bios_lz77.h"
#include "frame.h"
#include "scene_view.h"
#include "sound_work.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct PartC524 {
    u8 name[13];
    u8 pad0D[3];
    u8 byte10;
    u8 data11[6];
    u8 id17;
};
struct SetupC524 {
    u8 pad00[0x48];
    struct PartC524 parts[4];
    u8 padA8[0x18];
    u8 flagsC0;
    u8 padC1[0x1C];
    u8 partDD;
    u8 padDE[0x22];
};

extern struct SetupC524 gSetupC524[] asm("gSetupBuffer_03000590");

void sub_0801C524(void);

void sub_0801C524(void) {

    u32 kind;
    struct BattleWork *w;
    u8 part;
    struct SetupC524 *setup = gSetupC524;

    w = &gCounter6ED08_03001800;
    if (2 & setup[w->slot87].flagsC0)
        goto fail;
    if (sub_08034F44(w->slot87) != 0)
        goto fail;
    kind = w->records28[w->record89].kind3;
    if (kind == 0xA) {
        part = gSetupC524[w->slot87].parts[gSetupC524[w->slot87].partDD - 1].name[2];
        if (part == 0)
            goto first;
        if (part == 1) {
        first:
            w->resultA6 = 0xE;
            w->frame51 = 0;
            w->counterAA++;
            return;
        }
    } else if (kind == 0xB) {
        part = gSetupC524[w->slot87].parts[gSetupC524[w->slot87].partDD - 1].name[2];
        if (part == 2)
            goto second;
        if (part == 3) {
        second:
            w->resultA6 = 0xF;
            w->frame51 = 1;
            w->counterAA++;
            return;
        }
    } else if (kind == 0xC) {
        if (gSetupC524[w->slot87].parts[gSetupC524[w->slot87].partDD - 1].name[2] <= 3) {
            w->resultA6 = 0x10;
            w->frame51 = 2;
            w->counterAA++;
            return;
        }
    } else if (kind == 0x5A) {
        if (gSetupC524[w->slot87].parts[gSetupC524[w->slot87].partDD - 1].name[2] <= 3) {
            w->resultA6 = 0x11;
            w->frame51 = 3;
            w->counterAA++;
            return;
        }
    }
fail:
    w->counterAA = 0x2D;
}
