/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "gba.h"
#include "main_callbacks.h"

extern const u8 gUnknown_080B000E[];

void sub_080673AC(s32 arg0, s32 arg1);

void sub_080673AC(s32 arg0, s32 arg1) {

    u32 table,byteOffset,tileRoot;
    u16 sp0[32];
    u16 *destination;
    u16 overlayWord;
    s32 var_r2;
    u16 *var_r1;
    u16 var_r3;
    u8 temp_r7;

    table=(u32)gUnknown_080B000E;
    temp_r7 = *(const u8 *)(table + (*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 5)));
    if (arg1 <= 0xE) {
        CpuSet((const void *)((((u16) *(volatile u16 *)0x04000008 >> 8) & 0x1F) << 0xB) + ((temp_r7 * 2) + 0x06000000) + 0x100, &sp0[0], (0x1E - temp_r7) & 0x1FFFFF);
        CpuSet(&sp0[0], (void *)((((u16) *(volatile u16 *)0x04000008 >> 8) & 0x1F) << 0xB) + (((temp_r7 + 1) * 2) + 0x06000000) + 0x100, (0x1D - temp_r7) & 0x1FFFFF);
        return;
    }
    CpuFastSet((const void *)((((u16) *(volatile u16 *)0x0400000A >> 8) & 0x1F) << 0xB) + (((u32)arg0 << 6) + 0x06000000), &sp0[0], 0x10U);
    destination=sp0;
    overlayWord=*(volatile u16 *)0x0600DD3E;
    destination[31]=(u16)(0x800|overlayWord);
    var_r3 = 0;
    byteOffset=(u32)temp_r7 << 1;
    tileRoot=(u32)sp0;
    var_r1 = &sp0[10];
    var_r2 = 0x13;
    do {
        if (*var_r1 != 0) {
            var_r3 = *(u16 *)(tileRoot+0x3E);
        }
        *var_r1 = var_r3;
        var_r1 += 1;
        var_r2 -= 1;
    } while (var_r2 >= 0);
    CpuSet((const void *)((u32)sp0 + byteOffset), (void *)((((u16) *(volatile u16 *)0x04000008 >> 8) & 0x1F) << 0xB) + (byteOffset + 0x06000000) + 0x100, (0x1E - temp_r7) & 0x1FFFFF);
}
