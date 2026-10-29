/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "utility_helpers.h"

struct LinkContext64A80 {
    u8 pad00[0x1C];
    u32 bits1C;
    u8 pad20[0x28];
    u8 mask48;
    u8 pad49[0x31];
    s8 flag7A;
};

extern struct LinkContext64A80 *gLinkContext64A80 asm("gMainContextPointer_03006F74");
extern u32 gUnknownMask_03002B68;

void sub_08064A80(void);

void sub_08064A80(void) {

    u16 word;
    u32 bits;
    s32 i;
    struct LinkContext64A80 *ctx;

    word = gMainSerialOutgoingWork.words[gUnknown_03000B90 == 0][1];
    ctx = gLinkContext64A80;
    if (ctx->flag7A == 0) {
        if ((word & 0xFC00) == 0xF400) {
            bits = (word >> 8) & 3;
            ctx->bits1C |= (word & 0xFF) << (bits * 8);
            ctx->mask48 |= 1 << bits;
        }
        gMainSerialOutgoingWork.word06 = gLinkContext64A80->mask48 | 0xFC00;
    } else if ((0xFF00 & word) == 0xFC00) {
        if (word == 0xFC0F) {
            gMainSerialOutgoingWork.word06 = word;
        } else {
            bits = ctx->bits1C;
            for (i = 0; i <= 3; i++) {
                if (!((word >> i) & 1)) {
                    gMainSerialOutgoingWork.word06 = bits & 0xFF;
                    gMainSerialOutgoingWork.word06 |= (i << 8) | 0xF400;
                    break;
                }
                bits >>= 8;
            }
        }
    }
    if (gMainSerialOutgoingWork.words[0][1] == 0xFC0F && gMainSerialOutgoingWork.words[1][1] == gMainSerialOutgoingWork.words[0][1]) {
        if (gLinkContext64A80->flag7A != 0) {
            gMainSubstate = 0x11;
            gUnknown_0300137C = 0;
            return;
        }
        gUnknownMask_03002B68 = gLinkContext64A80->bits1C;
        sub_08044C38(0);
    }
}
