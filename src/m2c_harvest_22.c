/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "state0_work.h"

s32 sub_08073B68(s32);
s32 sub_08073C18(void **, s32);

void sub_08035928(s32 arg0, s32 arg1);
void sub_08035944(s32 arg0, s32 arg1);
long sub_08073C3C(void **arg0, s32 arg1);

void sub_08035928(s32 arg0, s32 arg1) {
    u8 *base0 = (u8 *) gSetupBuffer_03000590;
    (*(s8 *)((u8 *)((base0 + (arg0 << 8))) + 0xE0)) = arg1;
    gState0TransferWork.bytes[0x88] = arg1 - 1;
}

void sub_08035944(s32 arg0, s32 arg1) {
    u8 *base0 = (u8 *) gSetupBuffer_03000590;
    (*(s8 *)((u8 *)((base0 + (arg0 << 8))) + 0xE1)) = arg1;
    gState0TransferWork.bytes[0x8B] = arg1 - 1;
}

long sub_08073C3C(void **arg0, s32 arg1) {
  sub_08073C18(arg0, sub_08073B68(arg1 - (*((u8 *) (((s8 *) (*arg0)) + 7)))));
}
