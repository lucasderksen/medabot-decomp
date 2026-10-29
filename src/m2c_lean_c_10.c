/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "effect_work.h"
#include "frame.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "serial.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct LinkContext63FB0 {
    u8 pad000[0x48];
    u8 count48;
    u8 pad049[0x31];
    s8 flag7A;
    u8 pad07B[0x1B5];
    u8 buffer230[0x40];
};

extern struct LinkContext63FB0 *gLinkContext63FB0 asm("gMainContextPointer_03006F74");
extern void sub_08042028(u8 *);
extern void sub_08062C28(u8, u8);

void sub_08063FB0(void);

void sub_08063FB0(void) {

    u8 *buffer;
    u16 word;
    u8 count;
    u16 high;
    u8 *slot;
    struct LinkContext63FB0 **rootp;

    sub_0803FB3C(gMain2ScriptSlots_08485678[25]);
    rootp = &gLinkContext63FB0;
    buffer = (*rootp)->buffer230;
    word = gMainSerialOutgoingWork.words[gUnknown_03000B90 == 0][1];
    if ((*rootp)->flag7A != 0) {
        count = (*rootp)->count48;
        slot = &buffer[count];
        if ((0xF000 & word) == 0xC000 && (count & 0xF) == ((word >> 8) & 0xF)) {
            *slot = word;
            (*rootp)->count48++;
        }
        if (gLinkContext63FB0->count48 > 0x3F)
            gMainSerialOutgoingWork.word06 = 0xFF00;
        else
            gMainSerialOutgoingWork.word06 = gLinkContext63FB0->count48 | 0xFE00;
    } else {
        high = word & 0xFF00;
        if (high == 0xFF00)
            gMainSerialOutgoingWork.word06 = high;
        if (high == 0xFE00)
        {
            slot = &buffer[0xFF & word];
            gMainSerialOutgoingWork.word06 = *slot | (s16)(((word & 0xF) << 8) | 0xC000);
        }
    }
    if (gMainSerialOutgoingWork.words[0][1] == 0xFF00 && gMainSerialOutgoingWork.words[1][1] == gMainSerialOutgoingWork.words[0][1]) {
        if (gLinkContext63FB0->flag7A != 0) {
            sub_08042028(buffer);
            sub_08062C28(buffer[1], buffer[8]);
        } else {
            sub_08041FE4(buffer[1]);
        }
        gUnknown_0300137C++;
    }
}
