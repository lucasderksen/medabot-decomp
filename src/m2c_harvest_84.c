/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "record_helpers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern u32 sub_0803325C(u32);
extern u8 *gUnknown_083B6280;
extern u8 gUnknown_030018D2[];
extern void sub_0803836C(void);

void sub_08029F50(void);

void sub_08029F50(void) {
    s32 found = 0;
    u8 *work;
    u8 *setup;
    u8 *flags;
    u32 i;
    do {
    sub_0803836C();
    work = gState0TransferWork.bytes;
    work[0x60] = sub_08032FC4(work[0x87]);
    } while (0);
    i = 0;
    setup = gSetupBuffer_03000590;
    flags = work + 0xD2;
    do {
        u32 slot = work[0x60] + i;
        u32 address = (slot << 8) + (u32) setup;
        if (*(u8 *) (address + 0x40) != 0 && *(u8 *) (address + 0x59) != 0 && sub_0803325C(slot) != 0) {
            found = 1;
            *(u8 *) (i + (u32) flags) = found;
        }
        i++;
    } while (i <= 2);
    if (found == 0)
        gState0TransferWork.bytes[0xAA]++;
    else
        gState0TransferWork.bytes[0xAA] += 2;
}
