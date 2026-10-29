/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "input.h"
#include "state0_work.h"

extern s32 sub_08037424(s32);

void sub_08025308(void);

void sub_08025308(void) {
    u32 rewriteKeys;
    sub_08037424(0x21);
    if (((gState0TypedWork.bytes[0x89] != 0) || !(((rewriteKeys = (*(u8 *)&gRepeatedKeys)), (rewriteKeys & 1u) & rewriteKeys))) && (gState0TypedWork.widths.word86 != 0)) {
        gState0TypedWork.widths.word86 -= 1;
        return;
    }
    gState0TransferWork.bytes[0xAA] += 1;
}
