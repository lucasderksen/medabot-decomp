/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "main.h"
#include "record_helpers.h"
#include "state0_work.h"

struct Counter6ED08 {
    u8 unknown00[0xE];
    u8 frameA;
    u8 frameB;
};

extern struct Counter6ED08 gCounter6ED08_03001800;
extern u8 gUnknown_02031000[];
extern u8 gUnknown_03007010;
extern void sub_0807178C(void);
extern void sub_08071804(void);

void sub_08066A48(s32 (*out)[4], s32 (*a)[4], s32 (*b)[4]);
void sub_08070824(void);

void sub_08066A48(s32 (*out)[4], s32 (*a)[4], s32 (*b)[4]) {

    s32 i, j, k;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            out[i][j] = 0;
            for (k = 0; k < 4; k++)
                out[i][j] += (a[i][k] * b[k][j]) >> 8;
        }
    }
}

void sub_08070824(void) {

    if ((gFrameCounter & 3) == 0) {
        if (++gCounter6ED08_03001800.frameA > 5)
            gCounter6ED08_03001800.frameA = 0;
        {
            volatile u32 *dma = (volatile u32 *)0x040000D4;
            dma[0] = (u32)&gUnknown_02031000[gCounter6ED08_03001800.frameA * 0x280];
            dma[1] = 0x06004020;
            dma[2] = 0x84000040;
            dma[2];
        }
    }
    if ((gFrameCounter & 15) == 0) {
        if (++gCounter6ED08_03001800.frameB > 5)
            gCounter6ED08_03001800.frameB = 0;
        if (gCounter6ED08_03001800.frameB <= 5) {
            volatile u32 *dma = (volatile u32 *)0x040000D4;
            dma[0] = (u32)&gUnknown_02031000[gCounter6ED08_03001800.frameB * 0x280 + 0x100];
            dma[1] = 0x06004120;
            dma[2] = 0x84000060;
            dma[2];
        }
    }
    sub_0807178C();
    if (gUnknown_03007010 != 0)
        sub_08071804();
}
