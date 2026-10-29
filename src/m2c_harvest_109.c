/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"

extern u32 sub_08074F74(u32);
extern void *gUnknown_03007014;
extern void sub_080750AC(u32);

u32 sub_08074FA4(u32 mode);
void sub_080750F0(u32 arg0);

u32 sub_08074FA4(u32 mode) {
    void **root;
    u16 temp_r0;
    u16 temp_r1;
    u32 temp_r2;

    root=(void **)0x03007014;
    temp_r1 = (*(u16 *)((u8 *)(*root) + 0x730));
    if ((u32) temp_r1 <= 0xFFFEU) {
        (*(u16 *)((u8 *)(*root) + 0x730)) = (u16) (temp_r1 + 1);
    }
    temp_r2 = sub_08074F74(mode);
    temp_r0 = (*(u16 *)((u8 *)(*root) + 0x730));
    if (temp_r0 != 0) {
        (*(u16 *)((u8 *)(*root) + 0x730)) = (u16) (temp_r0 - 1);
    }
    return temp_r2;
}

void sub_080750F0(u32 arg0) {
    void **root;
    u16 temp_r0;
    u16 temp_r1;

    root=(void **)0x03007014;
    temp_r1 = (*(u16 *)((u8 *)(*root) + 0x730));
    if ((u32) temp_r1 <= 0xFFFEU) {
        (*(u16 *)((u8 *)(*root) + 0x730)) = (u16) (temp_r1 + 1);
    }
    sub_080750AC(arg0);
    temp_r0 = (*(u16 *)((u8 *)(*root) + 0x730));
    if (temp_r0 != 0) {
        (*(u16 *)((u8 *)(*root) + 0x730)) = (u16) (temp_r0 - 1);
    }
}
