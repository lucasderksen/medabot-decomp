/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "state0_work.h"


void sub_08027EDC(void);

void sub_08027EDC(void) {
    u8 *setup = gSetupBuffer_03000590;
    u8 *work = gState0TransferWork.bytes;
    u32 slot = work[0x87] << 8;
    u32 kind = *(u8 *) (slot + (u32) setup + 0xA8);
    switch (kind - 4) {
    case 0: work[0xA6] = 0x4A; break;
    case 1: work[0xA6] = 0x61; break;
    case 2: work[0xA6] = 0x4B; break;
    case 3: work[0xA6] = 0x62; break;
    case 4: work[0xA6] = 0x4C; break;
    default: work[0xA6] = 0x63; break;
    }
    work[0xAA]++;
}
