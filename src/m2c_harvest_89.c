/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern void sub_0803836C(void);

void sub_0802F650(void);

void sub_0802F650(void) {
    u8 *work;
    u8 *setup;
    u8 *cursor;
    u16 *values;
    u32 i;
    u32 root;
    u32 final_root;
    sub_0803836C();
    work = gState0TransferWork.bytes;
    work[0x60] = sub_08032FB8(work[0x87]);
    i = 0;
    setup = gSetupBuffer_03000590;
    root = (u32) work;
    cursor = (u8 *) (root + 0x60);
    final_root = root;
    values = (u16 *) (final_root + 0xD6);
    do {
        u32 address = ((*cursor + i) << 8) + (u32) setup;
        if (*(u8 *) (address + 0x40) != 0 && *(u8 *) (address + 0x59) != 0) {
            s32 flag_address = root + 0xD2;
            *(u8 *) (i + flag_address) = 1;
            *values = setup[((*cursor + i) << 8) + 0xA1];
        }
        values++;
        i++;
    } while (i <= 2);
    (*(u8 *) (final_root + 0xAA))++;
}
