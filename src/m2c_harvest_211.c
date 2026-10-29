/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "display_effects.h"
#include "effect_work.h"
#include "main_callbacks.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct PeerWork63F08 {u8 pad0[0x48];u8 clear;u8 pad49[0x31];u8 enabled;};
struct ScriptBank63F08 {u8 pad0[0x60];const u8 *message;};


void sub_08063F08(void);

void sub_08063F08(void) {
    s32 var_r1;
    u32 role;
    struct MainSerialOutgoingWork *serial;
    u8 *selected;

    if ((s8) ((struct PeerWork63F08 *)gMainContextPointer_03006F74)->enabled != 0) {
        sub_0803FB3C(((const struct ScriptBank63F08 *)gMain2ScriptSlots_08485678)->message);
    }
    role=gUnknown_03000B90;
    var_r1 = 0;
    serial=&gMainSerialOutgoingWork;
    if (role == 0) {
        var_r1 = 4;
    }
    selected=(u8 *)serial+0xA;
    if (*(u16 *)(selected+var_r1) == 0xFEDF) {
        gMainSubstate = 0x1A;
        return;
    }
    if ((serial->words[0][1] == 0xFDEF) && (serial->words[1][1] == serial->words[0][1])) {
        gUnknown_0300137C += 1;
        ((struct PeerWork63F08 *)gMainContextPointer_03006F74)->clear = 0;
        if ((s8) ((struct PeerWork63F08 *)gMainContextPointer_03006F74)->enabled != 0) {
            sub_0803FAA0(1U, 0U, 1U);
        }
    } else {
        serial->word06 = 0xFDEF;
    }
}
