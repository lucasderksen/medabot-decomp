/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"

extern void *gUnknown_03007014;
s32 sub_080736A0(void *);
s32 sub_08073718(void *);
s32 sub_08073784(void *);

void sub_080746C0(void);
void sub_080746E0(void);
void sub_08074704(void);

void sub_080746C0(void) {
    if ((*(s32 *)((u8 *)(gUnknown_03007014) + 0x1E4)) == 0) {
        sub_080736A0(gUnknown_03007014);
    }
}

void sub_080746E0(void) {
    if ((*(s32 *)((u8 *)(gUnknown_03007014) + 0x258)) == 0) {
        sub_08073718(gUnknown_03007014 + 0x74);
    }
}

void sub_08074704(void) {
    if ((*(s32 *)((u8 *)(gUnknown_03007014) + 0x2CC)) == 0) {
        sub_08073784(gUnknown_03007014 + 0xE8);
    }
}
