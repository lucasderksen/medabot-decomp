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

extern u8 gUnknown_030018D2[];

void sub_080283C0(void);
void sub_08028B58(void);
void sub_0802B388(void);
void sub_0802FE0C(void);
void sub_0803059C(void);

void sub_080283C0(void) {
    u8 *setup = gSetupBuffer_03000590;
    u8 *work = gState0TransferWork.bytes;
    s32 updated_flags;
    u32 index = work[0x87] << 8;
    u8 *record = (u8 *) (index + (u32) setup);
    record += 0xC0;
    updated_flags = *record | 2;
    *record = updated_flags;
    work[0xAA]++;
}

void sub_08028B58(void) {
    s32 found = 0;
    u32 i = 0;
    u8 *flags = gUnknown_030018D2;
    do {
        if (*(u8 *) (i + (u32) flags) != 0 && sub_08036AC4(i + 0x21, 0) != 0)
            found = 1;
        i++;
    } while (i <= 2);
    if (found != 0) {
        gState0TypedWork.widths.word86 = 0x3C;
        gState0TransferWork.bytes[0xAA]++;
    }
}

void sub_0802B388(void) {
    s32 finished = 0;
    s32 active = 0;
    u32 i = 0;
    u8 *flags = gUnknown_030018D2;
    do {
        if (*(u8 *) (i + (u32) flags) != 0) {
            active++;
            if (sub_080355F0(i + 0x21) != 0)
                finished++;
        }
        i++;
    } while (i <= 2);
    if (finished == active)
        gState0TransferWork.bytes[0xAA]++;
}

void sub_0802FE0C(void) {
    u8 *setup = gSetupBuffer_03000590;
    u8 *work = gState0TransferWork.bytes;
    s32 updated_flags;
    u32 index = work[0x87] << 8;
    u8 *record = (u8 *) (index + (u32) setup);
    record += 0xC0;
    updated_flags = *record | 1;
    *record = updated_flags;
    work[0xAA]++;
}

void sub_0803059C(void) {
    u8 *setup = gSetupBuffer_03000590;
    u8 *work = gState0TransferWork.bytes;
    s32 updated_flags;
    u32 index = work[0x87] << 8;
    u8 *record = (u8 *) (index + (u32) setup);
    record += 0xC0;
    updated_flags = *record | 4;
    *record = updated_flags;
    work[0xAA]++;
}
