/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "audio.h"
#include "continued_late_graphics.h"
#include "frame.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

extern u8 gFamilyKeyBytes49558_0300058C;
extern void sub_0803E894(void);
extern void sub_0803EA18(void);

void sub_0803DEF0(void);

void sub_0803DEF0(void) {

    u8 mode;
    u16 word;

    sub_0803E894();
    mode = gState0TypedWork.bytes[0x9C];
    if (mode == 1) {
        sub_0803EA18();
        sub_0803EA38();
        if (1 & gFamilyKeyBytes49558_0300058C) {
            sub_08074DE0(4);
            gMainSerialOutgoingWork.word06 = gCounter6ED08_03001800.value1A0 + 0x8000;
            gState0TypedWork.widths.word86 = 0;
            gUnknown_0300137C++;
        }
    } else {
        word = gMainSerialOutgoingWork.words[1 ^ gUnknown_03000B90][1];
        if (word & 0x8000) {
            sub_08074DE0(4);
            gCounter6ED08_03001800.value1A0 = word;
            gState0TypedWork.bytes[0x1B] = 0;
            gState0TypedWork.widths.word86 = 0;
            gUnknown_0300137C++;
        }
    }
}
