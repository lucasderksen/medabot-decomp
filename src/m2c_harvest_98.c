/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "state0_work.h"

struct FadeBacking { u32 prefix[2]; s32 counter; };


s32 sub_0806E484(void);

s32 sub_0806E484(void) {
    struct FadeBacking *work = (void *)&gState0TransferWork;
    struct FadeBacking *saved;
    u8 temp_r1;
    u8 temp_r2;

    s32 flag = work->counter & 3;
    saved = work;
    if (!flag) {
        temp_r2 = 0x10 - ((s32) work->counter >> 2);
        temp_r1 = 0x10 - temp_r2;
        *(s16 *)0x04000052 = (temp_r1 << 8) | temp_r2;
        if (temp_r1 == 0x10) {
            return 1;
        }
    }
    saved->counter = saved->counter + 1;
    return 0;
}
