/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "bios_lz77.h"
#include "gba.h"
#include "main_callbacks.h"
#include "scene_view.h"
#include "state0_work.h"

extern u16 gUnknown_0202FB00[];

void sub_0805BF14(u32 first);

void sub_0805BF14(u32 first) {

    u8 level = first;
    u16 buf[32];
    s32 i;
    s32 r, g, b;
    s32 r2, g2, b2;

    level = level > 0xF ? level - 0x10 : 0;
    CpuSet(gUnknown_0202FB00, buf, 0x04000010);
    for (i = 0; i <= 15; i++) {
        u16 c = buf[i];
        u16 c2 = buf[i + 16];
        r = c & 0x1F;
        g = (c >> 5) & 0x1F;
        b = (c >> 10) & 0x1F;
        r2 = c2 & 0x1F;
        g2 = (c2 >> 5) & 0x1F;
        b2 = (c2 >> 10) & 0x1F;
        r = (r - r2) * level / 32 + r2;
        g = (g - g2) * level / 32 + g2;
        b = (b - b2) * level / 32 + b2;
        buf[i] = (b << 10) | (g << 5) | r;
    }
    CpuSet(buf, (void *)0x05000140, 0x04000008);
}
