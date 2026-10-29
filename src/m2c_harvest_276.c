/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "state0_work.h"

extern const u8 gUnknown_083ABC2C[];
extern void sub_08073AB8(u32, const void *);
extern volatile u32 *const gUnknown_08486E54[];

void sub_08073AE4(u32 arg0, u32 *arg1);

void sub_08073AE4(u32 arg0, u32 *arg1) {

    u32 *var_r3;
    volatile u32 *fifo;
    s32 temp_r0;
    u32 bits;
    const u8 *selection;
    volatile u8 *controlAddress=(volatile u8 *)0x04000083;
    const u8 *tableRoot=gUnknown_083ABC2C;
    u32 temp_r2;
    s32 var_r1;

    temp_r2=arg0-1;
    selection=(const u8 *)(temp_r2+(u32)tableRoot);
    bits=*controlAddress;
    *controlAddress=bits|*selection;
    fifo=gUnknown_08486E54[temp_r2];
    var_r3 = arg1;
    var_r1 = 7;
    do {
        temp_r0 = *var_r3;
        var_r3 += 1;
        *fifo = temp_r0;
        var_r1 -= 1;
    } while (var_r1 >= 0);
    sub_08073AB8(arg0, arg1 + 8);
}
