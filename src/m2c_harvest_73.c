/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "state0_work.h"

extern s32 sub_08036BB8(void *, u32, u32);
extern u8 gUnknown_030018C8[];
extern void sub_08036370(s32, u32);
extern void sub_080364A8(s32, u32);

void sub_0801E9FC(void);

void sub_0801E9FC(void) {
    u8 *base = gUnknown_030018C8;
    u8 *selected = base - 0x40;
    s32 result = sub_08036BB8(base, *selected, *(base - 0x3D));
    s32 mode;
    u32 bits = base[0x30] & 2;
    mode = 0;
    if (bits == 0)
        mode = 1;
    sub_08036370(mode, *selected);
    sub_080364A8(mode, *selected);
    if (result != 0) {
        gState0TypedWork.widths.word86 = 0x3C;
        (*(base - 0x1E))++;
    }
}
