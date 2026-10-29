/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "state0_work.h"

struct SetupA534 {
    u8 pad0[0x50];
    u8 f50;
};
extern void sub_08035740(void *, u16, u8);
extern void sub_08037498(s32, s16);

void sub_0802A534(void);

void sub_0802A534(void) {

    u32 i;
    u8 *e;
    u16 *p;
    u8 *f;
    s32 j;

    for (i = 0; i <= 2; i++) {
        if (gCounter6ED08_03001800.activeD2[i] != 0) {
            sub_08037498(gCounter6ED08_03001800.base60 + i, gCounter6ED08_03001800.valueEC);
            p = &gCounter6ED08_03001800.valuesD6[i];
            *p = gCounter6ED08_03001800.valueC8;
            j = (gCounter6ED08_03001800.base60 + i) << 8;
            e = gSetupBuffer_03000590 + 0x48 + j;
            sub_08035740(e + 0x10, *p, ((struct SetupA534 *)(gSetupBuffer_03000590 + j))->f50);
        }
    }
    gCounter6ED08_03001800.counterAA++;
}
