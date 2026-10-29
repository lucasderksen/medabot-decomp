/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern s32 sub_0803725C(void);
extern void sub_0803579C(u32, u32);
extern void sub_08035814(u32);
extern void sub_08037280(u32, u32);

void sub_080251B4(void);

void sub_080251B4(void) {
    u8 *work = gState0TransferWork.bytes;
    sub_0803579C(work[0x87], work[0xA7]);
    sub_08035814(work[0x87]);
    if (sub_0803725C() != 0) {
        work[0xA6] = 0x1A;
        work[0xAA]++;
    } else {
        u8 *setup = gSetupBuffer_03000590;
        u8 *address = (u8 *) ((work[0x88] << 8) + (u32) setup);
        if (address[0x58] == 0) {
            work[0xA6] = 0x34;
            work[0xAA]++;
        } else {
            sub_08036270();
            sub_08037280(work[0x87], work[0xA7]);
            work[0xAA] = 4;
        }
    }
}
