/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_commands.h"
#include "post_dispatch.h"

extern struct { u8 b[0x1000]; } gContinuedWork_030057E0;
extern void sub_0804D8CC(u32);

void sub_0804C3E4(void);

void sub_0804C3E4(void) {

    s32 temp_r0;
    u8 *w;
    u16 *src;
    u16 *dst;
    u16 v;

    w = gContinuedWork_030057E0.b;
    src = (u16 *)(w + 0xC8A);
    v = *src;
    dst = (u16 *)(w + 0xC8C);
    *dst = v;
    sub_0804D8CC(3U);
    temp_r0 = (u16) sub_08047D9C(w[0xC94], w[0xC95]);
    if (((((temp_r0 & 0xFFFF) >> 8) - (0xFF & temp_r0)) << 0x10) == 0) {
        *src = (u16) (*dst + w[0xC96]);
    }
}
