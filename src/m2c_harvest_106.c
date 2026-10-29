/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "gba.h"


s32 sub_08067524(s32 arg0, s32 arg1);

s32 sub_08067524(s32 arg0, s32 arg1) {
    s32 var_r4;
    s32 var_r5;
    s32 var_r6;
    u32 doubled;

    if (arg1 > 0xD) {
        return 1;
    }
    var_r6 = 0;
    doubled = arg0 * 2;
    arg1 = -arg1;
    arg0 += 4;
    var_r5 = doubled + arg0;
    arg1 = (u32)arg1 << 6;
    var_r4 = arg1 + 0x06000440;
    do {
        CpuSet((const void *)((var_r5 << 6) + 0x0600D800),
               (void *)(((((u16)*(volatile u16 *)0x04000008 >> 8) & 0x1F) << 11) + var_r4), 13U);
        var_r4 += 0x40;
        var_r5 += 1;
        var_r6 += 1;
    } while (var_r6 <= 2);
    return 0;
}
