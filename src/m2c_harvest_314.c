/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "state0_work.h"

struct CV { u8 pad[0xC8]; s16 a; s16 b; s16 c; };

extern struct CV gUnknown_03001800;

void sub_08037498(s32 arg0, s32 arg1);

void sub_08037498(s32 arg0, s32 arg1) {

    u8 *setup = gSetupBuffer_03000590;
    u8 *rec = setup + (arg0 << 8);
    s32 d = rec[0x50] - rec[0x58];
    struct CV *g; struct CV *g2;
    if (d > arg1) {
        g = &gUnknown_03001800;
        g->a = arg1;
        g->c = arg1;
        g->b = 0;
    } else {
        g2 = &gUnknown_03001800;
        g2->a = d;
        g2->c = d;
        g2->b = arg1 - d;
    }
}
