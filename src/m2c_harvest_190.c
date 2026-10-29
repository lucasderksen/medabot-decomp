/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "effect_work.h"
#include "main_callbacks.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct Context645A0 {u8 pad00[0x7A];s8 mode;};


void sub_080645A0(void);

void sub_080645A0(void) {
    const void *const *scripts;
    s32 var_r1;
    s32 mode;

    scripts=gMain2ScriptSlots_08485678;
    mode=((struct Context645A0 *)gMainContextPointer_03006F74)->mode;
    var_r1 = 0x6C;
    if (mode != 0) {
        var_r1 = 0x68;
    }
    if (sub_0803FB3C(*(const void *const *)((const u8 *)scripts+var_r1)) != 0) {
        gMainSerialOutgoingWork.word06 = 0xFEFF;
        if ((gMainSerialOutgoingWork.words[0][1] == 0xFEFF) && (gMainSerialOutgoingWork.words[1][1] == gMainSerialOutgoingWork.words[0][1])) {
            gUnknown_0300137C += 1;
            sub_080656DC((u8 *)gMainContextPointer_03006F74 + 0x50, 0U, 0U, 1U, 0xC0U);
        }
    }
}
