/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "equipment_helpers.h"
#include "state0_next_helpers.h"

struct S61 { u8 pad[0x61]; u8 b61[3]; };

extern struct S61 gUnknown_03001800;

u32 sub_0803301C(void);

u32 sub_0803301C(void) {

    u32 i;
    s32 up;
    u32 n;
    struct S61 *g;
    u8 *e;
    u8 *a;
    i = sub_08033074();
    up = sub_080424B8() & 1;
    n = 0;
    a = gUnknown_03001800.b61;
    g = &gUnknown_03001800;
    do {
        if (*(u8 *)(i + (u32)a) != 0) {
            return *(u8 *)(i + (u32)a) - 1;
        }
        if (up != 0) {
            i += 1;
            if (i > 2) i = 0;
        } else if (i == 0) {
            i = 2;
        } else {
            i -= 1;
        }
        n += 1;
    } while (n <= 2);
    e = g->b61;
    return *(u8 *)(i + (u32)e);
}
