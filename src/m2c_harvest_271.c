/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "gba.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct Context65074 {u8 pad0[0x58];u8 text58[16];};

extern const u8 gUnknownPalette_0850F2B8[];
extern const u8 gUnknown_080AFC60[];
extern const u8 gUnknown_0879AD8C[];
extern u8 gUnknown_0202F800[];
extern u8 gUnknown_0202F940[];
extern u8 gUnknown_0202F9A0[];
extern u8 gUnknown_0202F9E0[];
extern u8 gUnknown_0202FA20[];
extern u8 gUnknown_03000584;
extern void sub_08064C6C(u8);

void sub_08065074(void);

void sub_08065074(void) {

    u32 root;
    s32 temp_r1;
    s8 temp_r0_2;
    s8 var_r2;
    u32 temp_r0_3;
    u32 var_r2_2;
    u8 temp_r0;

    *(volatile u16 *)0x04000000 |= 0x200;
    *(volatile u16 *)0x04000000 |= 0x400;
    *(volatile u16 *)0x04000000 |= 0x800;
    *(volatile u16 *)0x04000000 |= 0x1000;
    var_r2 = 0;
    do {
        root=(u32)gMainContextPointer_03006F74;
        temp_r0_2 = var_r2;
        ((struct Context65074 *)root)->text58[temp_r0_2] = 0xFE;
        temp_r0 = temp_r0_2 + 1;
        var_r2 = (s8) temp_r0;
    } while ((s32) (s8) temp_r0 <= 0xF);
    if (gUnknown_03000584 == 0) {
        var_r2_2 = 0;
        if ((*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x58)) != 0xFE) {
loop_4:
            temp_r0_3 = (var_r2_2 << 0x18) + 0x01000000;
            var_r2_2 = temp_r0_3 >> 0x18;
            temp_r1 = (s32) temp_r0_3 >> 0x18;
            if (temp_r1 <= 0xF) {
                if (((struct Context65074 *)gMainContextPointer_03006F74)->text58[temp_r1] == 0xFE) {

                } else {
                    goto loop_4;
                }
            }
        }
    } else {
        sub_08064C6C((*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x2F)));
    }
    CpuFastSet(gMain2NameTransfer_08483534, gUnknown_0202FA20, 8U);
    CpuFastSet(gUnknownWords_084E43F8, gUnknown_0202F800, 8U);
    CpuFastSet(gMain2NameTransfer_084E43D8, gUnknown_0202F9E0, 8U);
    CpuFastSet(gUnknownPalette_0850F2B8, gUnknown_0202F9A0, 8U);
    CpuFastSet(gUnknown_0879AD8C, gEquipmentPaletteShadow, 0x80U);
    CpuFastSet(gUnknown_080AFC60, gUnknown_0202F940, 8U);
    gState0TypedWork.bytes[0x84] = 0;
    gUnknown_0300137C += 1;
}
