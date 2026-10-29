/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"

s32 sub_08072818(void *);
void sub_08072F7C(void *);

void sub_08073010(void *arg0);

void sub_08073010(void *arg0) {
    s32 temp_r0;

    if ((*(s32 *)((u8 *)(arg0) + 0x24)) != 0) {
        temp_r0 = (*(s32 *)((u8 *)(arg0) + 0x30));
        if (temp_r0 != 0) {
            (*(s32 *)((u8 *)(arg0) + 0x30)) = (s32) (temp_r0 - 1);
        }
loop_3:
        if ((*(s32 *)((u8 *)(arg0) + 0x30)) == 0) {
            sub_08072F7C(arg0);
            if ((*(s32 *)((u8 *)(arg0) + 0x24)) != 0) {
                goto loop_3;
            }
        }
    }
    sub_08072818(arg0);
}
