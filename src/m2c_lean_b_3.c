/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "state0_next_helpers.h"


void sub_08036120(s32 arg0);

void sub_08036120(s32 arg0) {

    if (arg0 == 0) {
        if (!(gCounter6ED08_03001800.flagsF8 & 1))
            sub_08015838(gCounter6ED08_03001800.slot87, gCounter6ED08_03001800.buffer64);
        else if (!(gCounter6ED08_03001800.flagsF6 & 2))
            sub_08015838(gCounter6ED08_03001800.value88, gCounter6ED08_03001800.buffer64);
        else
            sub_08015838(gCounter6ED08_03001800.value161, gCounter6ED08_03001800.buffer64);
    } else {
        if (!(gCounter6ED08_03001800.flagsF8 & 1)) {
            if (gCounter6ED08_03001800.flagsF6 & 2)
                sub_08015838(gCounter6ED08_03001800.value161, gCounter6ED08_03001800.buffer64);
            else
                sub_08015838(gCounter6ED08_03001800.value88, gCounter6ED08_03001800.buffer64);
        } else
            sub_08015838(gCounter6ED08_03001800.slot87, gCounter6ED08_03001800.buffer64);
    }
}
